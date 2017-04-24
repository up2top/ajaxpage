<?php

/**
 * @file
 * Ajaxpage theme functions.
 */

/**
 * Display a list of AjaxPage actions for a node.
 */
function theme_ajaxpage_actions_menu($vars) {

  $items = array();

  foreach ($vars['actions'] as $name => $data) {

    // Do not render items with "menu_skip" flag.
    if (isset($data['menu_skip'])) continue;

    $link_attributes = array(
      'attributes' => array(
        'class' => 'ajaxpage__menu-link',
        'title' => $data['title']
      )
    );

    if (isset($data['link'])) {
      $path = $data['link'];
      $current_path = current_path();

      // Skip ajaxpage menu link to current page
      $realpath = 0 === strpos($path, '/') ? substr($path, 1) : $path;
      $normal_path = drupal_get_normal_path($realpath);
      if ($normal_path == $current_path) continue;

      if (isset($data['destination'])) {
        $link_attributes['query'] = array('destination' => $current_path);
      }
    } else {
      $path = '/ajaxpage/' . $name . '/node/' . $vars['nid'];
      $link_attributes['query'] = array('token' => drupal_get_token($path));
      $link_attributes['attributes']['class'] .= ' ajaxpage__ajax';
    }

    if (isset($data['confirm'])) {
      $link_attributes['attributes']['data-confirm'] = $data['confirm'];
    }

    $items[] = array(
      'data' => l($data['text'], $path, $link_attributes),
      'class' => array('ajaxpage__menu-item', 'ajaxpage__' . $name)
    );
  }

  // No actions. Return empty string.
  if (sizeof($items) == 0) return '';

  // AjaxPage menu options.
  $options = array(
    'items' => $items,
    'attributes' => array(
      'id' => 'ajaxpage-' . $vars['nid'],
      'class' => 'ajaxpage__menu'
    )
  );

  return theme('item_list', $options);
}
