<?php

/**
 * @file
 * template.php
 */

/**
 * Implements hook_preprocess_node().
 */
function dcasia16_preprocess_node(&$variables, $hook) {
  $view_mode = $variables['view_mode'];
  $content_type = $variables['type'];
  $variables['theme_hook_suggestions'][] = 'node__' . $view_mode;
  $variables['theme_hook_suggestions'][] = 'node__' . $view_mode . '__' . $content_type;

  $view_mode_preprocess = 'dcasia16_preprocess_node_' . $view_mode . '_' . $content_type;
  if (function_exists($view_mode_preprocess)) {
    $view_mode_preprocess($variables, $hook);
  }

  $view_mode_preprocess = 'dcasia16_preprocess_node_' . $view_mode;
  if (function_exists($view_mode_preprocess)) {
    $view_mode_preprocess($variables, $hook);
  }
}

/**
 * Implements hook_preprocess_html().
 */
function dcasia16_preprocess_html(&$variables) {
  if (!user_is_logged_in() AND arg(0) == 'user') {
    $variables['classes_array'][] = 'login-page';
  }
}

/**
 * Implements hook_preprocess_page().
 */
function dcasia16_preprocess_page(&$vars) {
  _dcasia16_get_user_vars($vars);

  $vars['search_sidebar'] = _dcasia16_get_search_form('sidebar-form');
  $vars['search'] = drupal_get_form('search_block_form');

  if (!user_is_logged_in() AND arg(0) == 'user') {
    $vars['theme_hook_suggestions'][] = 'page__login';
  }

  $header = drupal_get_http_header('status');
  if ($header == '404 Not Found') {
    $vars['theme_hook_suggestions'][] = 'page__404';
  }
  if ($header == '403 Forbidden') {
    $vars['theme_hook_suggestions'][] = 'page__404';
  }
}

/**
 * Helper function to get modified search form block.
 */
function _dcasia16_get_search_form() {
  $form = drupal_get_form('search_block_form');
  $form['#attributes']['class'][] = 'sidebar-form';
  $form['#attributes']['id'] = drupal_html_id('sidebar-search-form');
  return $form;
}

/**
 * Helper function to populate various user related variables.
 */
function _dcasia16_get_user_vars(&$vars) {
  global $user;
  $account = $user;
  $path_to_theme = '/' . drupal_get_path('theme', 'dcasia16');
  $theme_default_user_pic = $path_to_theme . '/img/default_user.png';

  if (!empty($account->picture)) {
    if (is_numeric($account->picture)) {
      $account->picture = file_load($account->picture);
    }
    if (!empty($account->picture->uri)) {
      $filepath = file_create_url($account->picture->uri);
    }
  }
  elseif (variable_get('user_picture_default', '')) {
    $filepath = variable_get('user_picture_default', '');
  }


  $vars['profile']['uid'] = $user->uid;
  $vars['profile']['name']['#markup'] = $user->uid ? $user->name : t('Anonymous');
  $vars['profile']['member_since']['#markup'] = !empty($user->created) ? t('Member since @date', array('@date' =>date('M. Y', $user->created))) : '';
  $vars['profile']['picture'] = !empty($filepath) ? $filepath : $theme_default_user_pic;


  if (!user_is_logged_in() AND arg(0) == 'user') {
    foreach ($vars['tabs']['#primary'] as $key => $value) {
      if (!empty($value['#active'])) {
        // $value['#theme'] = 'link';
        $vars['current_active_tab'] = l($value['#link']['title'], $value['#link']['href']);
        unset($vars['tabs']['#primary'][$key]);
        break;
      }
    }
  }
}

/**
 * Implements hook_js_alter().
 */
function dcasia16_js_alter(&$js) {
  $theme_path = drupal_get_path('theme', 'bootstrap');
  $bootstrap = $theme_path . '/js/bootstrap.js';
  unset($js[$bootstrap]);
}


function dcasia16_preprocess_ctools_dropdown(&$vars) {
  $vars['dropdown_menu'] = array();
  $vars['default_link']  = array();

  $flag_first_item = TRUE;
  foreach ($vars['links'] as $key => $value) {
    $options = array();
    $href = $value['href'];
    if (isset($value['query'])) {
      $options = array(
        'query' => $value['query'],
      );
    }
    $url = !empty($href) ? check_plain(url($href, $options)) : '';

    if ($flag_first_item) {
      $vars['default_link'] = $value;
      $vars['default_link']['url'] = $url;
      $vars['default_link']['class'] = !empty($value['attributes']['class']) ? implode(' ', $value['attributes']['class']) : '';
    }
    else {
      $vars['dropdown_menu'][$key] = $value;
      $vars['dropdown_menu'][$key]['url'] = $url;
      $vars['dropdown_menu'][$key]['class'] = !empty($value['attributes']['class']) ? implode(' ', $value['attributes']['class']) : '';
    }
    $flag_first_item = FALSE;
  }
}

function dcasia16_preprocess_links__ctools_dropbutton(&$vars) {
  $vars['dropdown_menu'] = array();
  $vars['default_link']  = array();

  $flag_first_item = TRUE;
  foreach ($vars['links'] as $key => $value) {
    if (isset($value['attributes']['class'])) {
      if ($key = array_search('icon compact add', $value['attributes']['class']) !== FALSE) {
        unset($value['attributes']['class'][0]);
        $value['title'] = '<i class="fa fa-plus"></i> ' . $value['title'];
        $value['attributes']['class'][] = 'btn';
        $value['attributes']['class'][] = 'btn-default';
      }
      if ($key = array_search('icon compact rearrange', $value['attributes']['class']) !== FALSE) {
        unset($value['attributes']['class'][0]);
        $value['title'] = '<i class="fa fa-gear"></i> ' . $value['title'];
        $value['attributes']['class'][] = 'btn';
        $value['attributes']['class'][] = 'btn-default';
      }
    }

    $options = array();
    $href = $value['href'];
    if (isset($value['query'])) {
      $options = array(
        'query' => $value['query'],
      );
    }
    $url = !empty($href) ? check_plain(url($href, $options)) : '';

    if ($flag_first_item) {
      $vars['default_link'] = $value;
      $vars['default_link']['url'] = $url;
      $vars['default_link']['class'] = !empty($value['attributes']['class']) ? implode(' ', $value['attributes']['class']) : '';
    }
    else {
      $vars['dropdown_menu'][$key] = $value;
      $vars['dropdown_menu'][$key]['url'] = $url;
      $vars['dropdown_menu'][$key]['class'] = !empty($value['attributes']['class']) ? implode(' ', $value['attributes']['class']) : '';
    }
    $flag_first_item = FALSE;
  }
}

