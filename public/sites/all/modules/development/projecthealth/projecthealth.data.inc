<?php

/**
 * @file
 * Generate report data.
 */

/**
 * Function to generate report data for project snapshot.
 */
function projecthealth_generate_report_data($pid, $sid) {
  $project = db_query("SELECT * from {projecthealth_project} WHERE id = :pid LIMIT 1", array(":pid" => $pid))->fetchObject();
  $project->data = unserialize($project->data);
  $snapshot = db_query("SELECT * from {projecthealth_snapshot} WHERE id = :sid LIMIT 1", array(":sid" => $sid))->fetchObject();
  $data = array(
    'project' => $project,
    'snapshot' => $snapshot,
    'issue' => projecthealth_generate_issue_report($pid, $sid),
    'users' => projecthealth_generate_user_report($pid, $sid),
    'comments' => projecthealth_generate_comment_report($pid, $sid),
  );
  return $data;
}

/**
 * Issue report.
 */
function projecthealth_generate_issue_report($pid, $sid) {
  $issue = new stdClass();
  $issue->totalCount = db_query("SELECT COUNT(*) as num from {projecthealth_issue} WHERE pid = :pid", array(":pid" => $pid))->fetchField();
  $closed = array(2, 3, 4, 5, 6, 7, 16, 18);
  $issue->closedCount = db_query("SELECT COUNT(*) as num from {projecthealth_issue} WHERE pid = :pid AND status IN (:closed)", array(":pid" => $pid, ":closed" => $closed))->fetchField();
  $open = array(1, 8, 13, 14, 15);
  $issue->activeCount = db_query("SELECT COUNT(*) as num from {projecthealth_issue} WHERE pid = :pid AND status IN (:open)", array(":pid" => $pid, ":open" => $open))->fetchField();
  return $issue;
}

/**
 * Issue report.
 */
function projecthealth_generate_user_report($pid, $sid) {
  $result = db_query('SELECT pu.uid, pu.name, COUNT(pi.id) as issues
    FROM {projecthealth_user} as pu
    LEFT JOIN {projecthealth_issue} as pi ON pu.uid = pi.uid
    WHERE pu.pid = :pid
    GROUP BY pu.uid ORDER BY issues DESC', array(':pid' => $pid)
  );
  $users = array();
  foreach ($result as $record) {
    $users[] = $record;
  }
  return $users;
}

/**
 * Comment report.
 */
function projecthealth_generate_comment_report($pid, $sid) {
  $result = db_query('SELECT pu.uid, pu.name, COUNT(pc.id) as issues
    FROM {projecthealth_user} as pu
    LEFT JOIN {projecthealth_comment} as pc ON pu.uid = pc.uid
    WHERE pu.pid = :pid
    GROUP BY pu.uid ORDER BY issues DESC', array(':pid' => $pid)
  );
  $users = array();
  foreach ($result as $record) {
    $users[] = $record;
  }
  return $users;
}
