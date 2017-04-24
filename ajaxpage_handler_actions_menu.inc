<?php

/**
 * @file
 * Definition of ajaxpage_handler_actions_menu
 */
  
/**
 * Provides actions menu views field.
 */
class ajaxpage_handler_actions_menu extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }
  
  function query() {
    // do nothing -- to override the parent query.
  }

  // Output actions menu field as a list of permissible actions on node.
  function render($data) {
    $output = '';

    // AjaxMenu for a node.
    if (isset($data->nid)) {

      // Load actions menu for current user and node.
      $node = isset($data->_field_data['nid']['entity']) ? $data->_field_data['nid']['entity'] : node_load($data->nid);
      $actions = ajaxpage_get_node_actions($node);

      // Theme actions menu.
      $output = theme('ajaxpage_actions_menu', array('nid' => $node->nid, 'actions' => $actions));
    }

    return $output;
  }
}
