<?php
/**
 * @file
 * fe_project.features.inc
 */

/**
 * Implements hook_node_info().
 */
function fe_project_node_info() {
  $items = array(
    'project' => array(
      'name' => t('project'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
