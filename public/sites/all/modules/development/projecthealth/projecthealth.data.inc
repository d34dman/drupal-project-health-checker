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
  $cid = "$project->id:$snapshot->id:$snapshot_ready:$start:$end";
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
    'users_map' => projecthealth_generate_country_report($pid, $sid, $start, $end),
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

  $result = db_query('SELECT *
    FROM {projecthealth_user} as pu
    WHERE pu.pid = :pid', array(':pid' => $pid)
  );
  foreach ($result as $record) {
    $record->data = unserialize($record->data);
    $record->data->country = projecthealth_get_country_codes($record->data->field_country);
    $users[$record->uid] = $record;
    $users[$record->uid]->issueCount = '0';
    $users[$record->uid]->commentCount = '0';
  }

  $result = db_query('SELECT pu.uid, pu.name, COUNT(pi.id) as issueCount
    FROM {projecthealth_user} as pu
    LEFT JOIN {projecthealth_issue} as pi ON pu.uid = pi.uid
    WHERE pu.pid = :pid AND pi.created >= :start AND pi.created < :end
    GROUP BY pu.uid ORDER BY issueCount DESC',
    array(
      ':pid' => $pid,
      ':start' => $start,
      ':end' => $end,
    )
  );
  foreach ($result as $record) {
    $users[$record->uid]->issueCount = $record->issueCount;
  }

  $result = db_query('SELECT pu.uid, pu.name, COUNT(pc.id) as commentCount
    FROM {projecthealth_user} as pu
    LEFT JOIN {projecthealth_comment} as pc ON pu.uid = pc.uid
    WHERE pu.pid = :pid AND pc.created >= :start AND pc.created < :end
    GROUP BY pu.uid ORDER BY commentCount DESC',
    array(
      ':pid' => $pid,
      ':start' => $start,
      ':end' => $end,
    )
  );
  foreach ($result as $record) {
    if (isset($users[$record->uid])) {
      $users[$record->uid]->commentCount = $record->commentCount;
    }
  }
  return $users;
}
/**
 * Issue report.
 */
function projecthealth_generate_country_report($pid, $sid, $start, $end) {
  $stats = array();

  $result = db_query('SELECT count(pu.uid) as count, pu.country_code
    FROM {projecthealth_user} as pu
    WHERE pu.pid = :pid AND pu.country_code <> \'\'
    GROUP BY pu.country_code
    ORDER BY count DESC',
    array(
      ':pid' => $pid,
    )
  );
  $is_max = TRUE;
  foreach ($result as $record) {
    $record->fillKey = _projecthealth_get_color_key($record->count, $is_max);
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
