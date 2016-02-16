<?php

/**
 * @file
 * Generate report data.
 */

/**
 * Function to generate report data for project snapshot.
 */
function projecthealth_generate_report_data($project, $snapshot, $start = PROJECTHEALTH_DEFAULT_START_TIME, $end = PROJECTHEALTH_DEFAULT_END_TIME, $reset = FALSE) {
  // @todo: implement caching.
  $snapshot_ready = ($snapshot->progress == 100);
  if (!$snapshot_ready) {
    return projecthealth_generate_temporary_snapshot_data($project, $snapshot);
  }
  $pid = $project->id;
  $sid = $snapshot->id;
  $cid = "$pid:$sid:$snapshot_ready:$start:$end";
  if (!$reset AND $cache = cache_get($cid)) {
    return $cache->data;
  }
  $data = array(
    'progress' => $snapshot->progress,
    'start' => $start,
    'start_date' => date('Y-m-d H:i:s', $start),
    'end' => $end,
    'end_date' => date('Y-m-d H:i:s', $end),
    'project' => $project,
    'snapshot' => $snapshot,
    'issues' => projecthealth_generate_issue_report($pid, $sid, $start, $end),
    'comments' => projecthealth_generate_comment_report($pid, $sid, $start, $end),
    'users' => projecthealth_generate_user_report($pid, $sid, $start, $end),
    'world_stats' => projecthealth_generate_country_report($pid, $sid, $start, $end),
  );
  cache_set($cid, $data);
  return $data;
}

/**
 * Send data for snapshot indexing in progress.
 */
function projecthealth_generate_temporary_snapshot_data($project, $snapshot){
  return array(
    'progress' => $snapshot->progress,
    'project' => $project,
    'snapshot' => $snapshot,
  );
}

/**
 * Issue report.
 */
function projecthealth_generate_issue_report($pid, $sid, $start, $end) {
  $issue = new stdClass();
  $issue->totalCount = db_query("SELECT COUNT(*) AS num
    FROM {projecthealth_issue}
    WHERE pid = :pid AND created >= :start AND created < :end",
    array(
      ":pid" => $pid,
      ":start" => $start,
      ":end" => $end,
    ))
    ->fetchField();
  $closed = array(2, 3, 4, 5, 6, 7, 16, 18);
  $issue->closedCount = db_query("SELECT COUNT(*) AS num
    FROM {projecthealth_issue}
    WHERE pid = :pid AND status IN (:closed) AND created >= :start AND created < :end",
    array(
      ":pid" => $pid,
      ":closed" => $closed,
      ":start" => $start,
      ":end" => $end,
    ))
    ->fetchField();
  $open = array(1, 8, 13, 14, 15);
  $issue->openCount = db_query("SELECT COUNT(*) AS num
    FROM {projecthealth_issue}
    WHERE pid = :pid AND status IN (:open) AND created >= :start AND created < :end",
    array(
      ":pid" => $pid,
      ":open" => $open,
      ":start" => $start,
      ":end" => $end,
    ))
    ->fetchField();
  return $issue;
}


/**
 * Issue report.
 */
function projecthealth_generate_comment_report($pid, $sid, $start, $end) {
  $comment = new stdClass();
  $comment->totalCount = db_query("SELECT COUNT(*) AS num
    FROM {projecthealth_comment}
    WHERE pid = :pid AND created >= :start AND created < :end",
    array(
      ":pid" => $pid,
      ":start" => $start,
      ":end" => $end,
    ))
    ->fetchField();
  return $comment;
}

/**
 * Issue report.
 */
function projecthealth_generate_user_report($pid, $sid, $start, $end) {
  $users = array();

  $result = db_query('SELECT phu.name as name, phu.country_code as country_code, phu.uid as uid, ifnull(tpi.count,0) as issues, ifnull(tpc.count,0) as comments, (ifnull(tpc.count,0) + ifnull(tpi.count,0)) as total

    FROM {projecthealth_user} as phu

    LEFT JOIN (SELECT COUNT(pi.issue_id) AS count, pi.uid as issue_uid
    FROM {projecthealth_issue} AS pi
    WHERE pi.pid = :pid
    GROUP BY pi.uid
    ) as tpi ON phu.uid = tpi.issue_uid

    LEFT JOIN (SELECT COUNT(pc.id) AS count, pc.uid as issue_uid
    FROM {projecthealth_comment} AS pc
    WHERE pc.pid = :pid
    GROUP BY pc.uid
    ) as tpc ON phu.uid = tpc.issue_uid

    WHERE phu.pid = :pid', array(':pid' => $pid)
  );
  foreach ($result as $record) {
    $record->country = projecthealth_get_country_codes($record->country_code);
    $users[$record->uid] = $record;
  }
  return $users;
}
/**
 * Issue report.
 */
function projecthealth_generate_country_report($pid, $sid, $start, $end) {
  $stats = array();

  $result = db_query('SELECT DISTINCT(pu.name), pu.country_code , SUM(userStats.comments) as commentsCount, SUM(userStats.issues) as issuesCount, SUM(userStats.total) as totalCount

    FROM {projecthealth_user} as pu

    LEFT JOIN

    (SELECT phu.name as phuname, phu.country_code, phu.uid, ifnull(tpi.count,0) as issues, ifnull(tpc.count,0) as comments, (ifnull(tpc.count,0) + ifnull(tpi.count,0)) as total FROM {projecthealth_user} as phu

    LEFT JOIN (SELECT COUNT(pi.issue_id) AS count, pi.uid as issue_uid
    FROM {projecthealth_issue} AS pi
    WHERE pi.pid = :pid
    GROUP BY pi.uid
    ) as tpi ON phu.uid = tpi.issue_uid

    LEFT JOIN (SELECT COUNT(pc.id) AS count, pc.uid as issue_uid
    FROM {projecthealth_comment} AS pc
    WHERE pc.pid = :pid
    GROUP BY pc.uid
    ) as tpc ON phu.uid = tpc.issue_uid


    WHERE phu.pid = :pid) as userStats ON pu.name = userStats.phuname
    WHERE pu.pid = :pid
    GROUP BY pu.country_code
    ORDER BY totalCount DESC',
    array(
      ':pid' => $pid,
    )
  );
  $is_max = TRUE;
  foreach ($result as $record) {
    $record->fillKey = _projecthealth_get_color_key($record->totalCount, $is_max);
    $stats[$record->country_code] = $record;
    $is_max = FALSE;
  }
  return $stats;
}

/**
 * Helper function to create color coded keys.
 */
function _projecthealth_get_color_key($value, $is_max = FALSE) {
  static $max_val;
  $max_val = $is_max ? $value : $max_val;

  $ratio = 100 * $value / $max_val;
  if ($ratio > 75) {
    return 'HIGHEST';
  }
  else if($ratio > 50){
    return 'HIGH';
  }
  else if($ratio > 25) {
    return 'LOW';
  }
  else {
    return 'LOWEST';
  }

}
