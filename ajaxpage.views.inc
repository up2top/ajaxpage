<?php

/**
 * @file
 * Views definitions for AjaxPage module.
 */

/**
 * Implements hook_views_handlers() to register actions menu field handler.
 */
function ajaxpage_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'ajaxpage'),
    ),
    'handlers' => array(
      // Actions menu field handler.
      'ajaxpage_handler_actions_menu' => array(
        // The name of the handler we are extending.
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
 
/**
 * Implements hook_views_data() to describe actions menu field.
 */
function ajaxpage_views_data() {
  $data = array();
  $data['ajaxpage']['table']['group'] = t('AjaxPage');
  $data['ajaxpage']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  // Add actions menu field.
  $data['ajaxpage']['ajaxpage_actions_menu'] = array(
    'title' => t('Actions menu'),
    'help' => t('Provides a list of ajax actions for a node.'),
    'field' => array(
      'handler' => 'ajaxpage_handler_actions_menu',
    ),
  );
  return $data;
}
