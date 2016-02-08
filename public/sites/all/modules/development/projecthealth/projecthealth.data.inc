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
  );
  return $data;
}
