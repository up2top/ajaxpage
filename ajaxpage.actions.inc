<?php

/**
 * @file
 * Ajaxpage default actions.
 */

/**
 * General AjaxPage action procedure.
 */
function ajaxpage_execute_action($action, $type = '', $object = NULL) {

  // AjaxPage action path.
  $path = base_path() . current_path();

  // Check if security token valid.
  if (isset($_GET['token']) && drupal_valid_token($_GET['token'], $path)) {

    // Array of AJAX commands.
    $commands = array();

    // Execute default ajaxpage actions and define hook(s) for each action type.
    switch ($type) {
      case 'node':
        ajaxpage_execute_node_action($object, $commands, $action);
        $hooks = array(
          'execute_ajaxpage_node_action',
          'execute_ajaxpage_' . $object->type . '_action'
        );
        break;

      case 'comment':
        ajaxpage_execute_comment_action($object, $commands, $action);
        $hooks = array('execute_ajaxpage_comment_action');
        break;

      default:
        $hooks = array('execute_ajaxpage_action');
    }

    // Call all modules implementing ajaxpage module hooks: execute_ajaxpage_action,
    // execute_ajaxpage_comment_action, execute_ajaxpage_node_action and
    // hook_ajaxpage_node_NODETYPE_action.
    foreach ($hooks as $hook) {
      foreach (module_implements($hook) as $module) {
        $function = $module . '_' . $hook;
        if (empty($type)) {
          $function($commands, $action);
        } else {
          $function($object, $commands, $action);
        }
      }
    }

    // Send response in JSON format.
    print ajax_render($commands);
    drupal_exit();
  }
}

/**
 * Default execute node action function.
 */
function ajaxpage_execute_node_action(&$node, &$commands, $action) {

  // jQuery selectors for AJAX commands.
  $ajaxpage_views_row = '.views-row.ajaxpage-' . $node->nid;
  $ajaxpage_link = "#ajaxpage-" . $node->nid . " .ajaxpage__" . $action . " .ajaxpage__menu-link";

  switch ($action) {

    // Publish or unpublish node.
    case 'publish':
      if ($node->status == 0) {
        $node->status = 1;
        $text = t('Unpublish');
        $title = t('Unpublish node');
        $class_action = 'removeClass';
      } else {
        $node->status = 0;
        $text = t('Publish');
        $title = t('Publish node');
        $class_action = 'addClass';
      }

      $commands[] = ajax_command_invoke($ajaxpage_views_row, $class_action, array('unpublished'));
      $commands[] = ajax_command_invoke($ajaxpage_link, "text", array($text));
      $commands[] = ajax_command_invoke($ajaxpage_link, "attr", array('title', $title));
      node_save($node);
      break;

    // Delete node.
    case 'delete':
      $commands[] = ajax_command_remove($ajaxpage_views_row);
      node_delete($node->nid);
      break;
  }
}

/**
 * Default execute comment action function.
 */
function ajaxpage_execute_comment_action(&$comment, &$commands, $action) {

  switch ($action) {

    // Delete comment.
    case 'delete':
      $commands[] = ajax_command_remove('.comment-wrapper-' . $comment->cid);
      comment_delete($comment->cid);
      break;
  }
}
