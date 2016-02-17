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
    'world_stats' => projecthealth_generate_world_stats($pid),
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
function projecthealth_generate_user_report($pid) {
  $users = array(
    'age' => array(),
    'latest_activity' => array(),
  );

  $result = db_query('SELECT
      COUNT(pu.id) as users,
      YEAR(now()) - YEAR(FROM_UNIXTIME(pu.created)) as age,
      SUM(CASE WHEN pu.gender = \'male\'    THEN 1 ELSE 0 END)     AS males,
      SUM(CASE WHEN pu.gender = \'female\'    THEN 1 ELSE 0 END)   AS females,
      SUM(CASE WHEN ISNULL(pu.gender)    THEN 1 ELSE 0 END)      AS unknown
    FROM {projecthealth_user} as pu
    WHERE pu.pid = :pid
    GROUP BY YEAR(FROM_UNIXTIME(pu.created))
    ORDER BY age ASC',
    array(':pid' => $pid)
  );
  foreach ($result as $record) {
    $users['age'][$record->age] = $record;
  }

  $result = db_query('SELECT
      COUNT(pu.id) as users,
      YEAR(FROM_UNIXTIME(pu.latest_activity)) as year,
      SUM(CASE WHEN pu.gender = \'male\'    THEN 1 ELSE 0 END)     AS males,
      SUM(CASE WHEN pu.gender = \'female\'    THEN 1 ELSE 0 END)   AS females,
      SUM(CASE WHEN ISNULL(pu.gender)    THEN 1 ELSE 0 END)      AS unknown
    FROM {projecthealth_user} as pu
    WHERE pu.pid = :pid
    GROUP BY YEAR(FROM_UNIXTIME(pu.latest_activity))
    ORDER BY year ASC',
    array(':pid' => $pid)
  );
  foreach ($result as $record) {
    $users['latest_activity'][$record->year] = $record;
  }

  return $users;
}

/**
 * Generate world stats.
 */
function projecthealth_generate_world_stats($pid) {
  $stats = array();
  $result = db_query('SELECT u.country_code as country_code, ifnull(c.comments,0) as commentsCount, ifnull(i.issues,0) as issuesCount, COUNT(u.id) as usersCount, (ifnull(c.comments,0) + ifnull(i.issues,0)) as totalCount
    FROM projecthealth_user as u

    LEFT JOIN (
    SELECT COUNT(c.id) as comments, cu.country_code
    FROM projecthealth_comment as c

    LEFT JOIN projecthealth_user as cu ON cu.uid = c.uid

    WHERE c.pid = :pid AND cu.pid = :pid

    GROUP BY cu.country_code
    ) AS c ON c.country_code = u.country_code

    LEFT JOIN (
    SELECT COUNT(i.id) as issues, iu.country_code as country_code
    FROM projecthealth_issue as i

    LEFT JOIN projecthealth_user as iu ON iu.uid = i.uid

    WHERE i.pid = :pid AND iu.pid = :pid

    GROUP BY iu.country_code
    ) AS i ON i.country_code = u.country_code

    WHERE u.pid = :pid
    GROUP BY u.country_code',
      array(':pid' => $pid)
  );
  foreach ($result as $record) {
    $stats[$record->country_code] = $record;
  }
  return $stats;
}

/**
 * Issue report.
 */
function projecthealth_generate_country_report($pid, $sid, $start, $end) {
  $stats = array();

  $result = db_query('SELECT DISTINCT(pu.name), pu.country_code , SUM(userStats.comments) as commentsCount, SUM(userStats.issues) as issuesCount, SUM(userStats.total) as totalCount, userStats.totalUsers as usersCount

    FROM {projecthealth_user} as pu

    LEFT JOIN

    (SELECT phu.name as phuname, phu.country_code, phu.uid, ifnull(tpi.count,0) as issues, ifnull(tpc.count,0) as comments, (ifnull(tpc.count,0) + ifnull(tpi.count,0)) as total, tpu.totalUsers as totalUsers FROM {projecthealth_user} as phu

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

    LEFT JOIN(
    SELECT u.country_code, count(u.id) as totalUsers
    FROM projecthealth_user as u
    WHERE u.pid = 2
    GROUP BY u.country_code
    ) as tpu ON phu.country_code = tpu.country_code

    WHERE phu.pid = :pid) as userStats ON pu.name = userStats.phuname
    WHERE pu.pid = :pid
    GROUP BY pu.country_code
    ORDER BY totalCount DESC',
    array(
      ':pid' => $pid,
    )
  );
  foreach ($result as $record) {
    unset($record->name);
    $stats[$record->country_code] = $record;
  }
  return $stats;
}
