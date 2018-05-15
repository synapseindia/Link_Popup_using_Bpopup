<?php

/**
 * @file
 * Defines Link Popup module Configuration form and setting for the Admin.
 */

/**
 * Callback function menu_links()
 * to displayed the list of menu links and menu link add form @return output.
 */
function lpop_up_menu_links() {
  $menu_links_form = drupal_get_form('lpop_up_list_form');
  $menu_links_add_form = drupal_get_form('lpop_up_form');
  $output = '';
  // Code to add menu link form.
  $output .= '<div class="menu_form_container">';
  $output .= drupal_render($menu_links_add_form);
  $output .= '</div>';
  // Code to display list of menu items added.
  $output .= '<div class="menu_container">';
  $output .= drupal_render($menu_links_form);
  $output .= '</div>';
  return $output;
}

/**
 * Callback function lpop_up_form()
 * to add menu links on Configure page @return form.
 */
function lpop_up_form($form, &$form_state) {
  $form = array();
  $form['lpop_up_section'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menu link titles form'),
    '#weight' => 3,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['lpop_up_section']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu Title'),
    '#required' => TRUE,
  );
  $form['lpop_up_section']['link'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu Title Link'),
    '#required' => TRUE,
  );
  $form['lpop_up_section']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Configuration'),
  );
  return $form;
}

/**
 * Submit handler for lpop_up_form()
 * @return output.
 */
function lpop_up_form_submit($form, &$form_state) {
  $title = $form_state['values']['lpop_up_section']['title'];
  $link = $form_state['values']['lpop_up_section']['link'];
  db_merge('link_title')
    ->key(array('link' => $link))
    ->fields(array(
      'title' => $title,
      'link' => $link,
    ))
    ->execute();
  $output = drupal_set_message( t("Configuration has been saved.") );
  return $output;
}

/**
 * Callback function lpop_up_list_form()
 * @return form 
 * to display list of menu links on Configure page.
 */
function lpop_up_list_form($form = array(), &$form_state) {
  $form = array();
  $header = array(
    'title' => array('data' => t('Menu Title')),
    'link' => array('data' => t('Menu Link')),
  );
  //Get list of menu links to display.
  $query = db_select('link_title', 'lt')->extend('PagerDefault')->extend('TableSort');
  $result = $query
    ->fields('lt', array('id', 'title', 'link'))
    ->limit(20)
    ->execute();
  $options = array();
  foreach ($result as $row) {
    $options[$row->id] = array(
      'title' => $row->title,
      'link' => $row->link,
    );
  }
  $form['wrapper'] = array(
    '#markup' => '<div>Menu lists</div>',
  );
  $form['id'] = array(
    '#type' => 'hidden',
    '#title' => t(''),
  );
  $form['menu_list'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No menu is added.'),
  );
  $form['pager'] = array('#theme' => 'pager');
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Remove Links'),
  );
  // Check for Menu list link remove
  if ( !isset($form_state['storage']['confirm']) ) {
    return $form;
  }
  else{
    $path = current_path();
    $menus_id =  $form_state['values']['menu_list'];
    $menu_lists = array_filter($menus_id);
    if ( !empty($menu_lists) && isset($menu_lists) ) {
      $query = db_select('link_title', 'lt')
        ->fields('lt', array('title', 'link'))
        ->condition('id', $menus_id, 'IN');
      $menus = $query->execute();
      $menu_links='<div>Are you sure you wish to remove this menu links</div><ul>';
      foreach ($menus as $menu) {
        $menu_links .= '<li>' . $menu->title . '</li>';
      }
      $menu_links .= '</ul>';
      return confirm_form(
        array(),
        'Are you sure you wish to remove this menu links',
        $path,
        $menu_links,
        'Yes',
        'Cancel'
      );
    }
    else{
      drupal_set_message( t('No menu is selected to remove. Please select any menu to remove.'), 'error');
      drupal_goto($path);
    }
  }
}

/**
 * Submit handler for lpop_up_list_form()
 * @return output 
 * to remove menu links.
 */
function lpop_up_list_form_submit($form, &$form_state) {
  if (!isset($form_state['storage']['confirm']) ) {
    $form_state['storage']['confirm'] = TRUE;
    $form_state['storage']['original_form'] = $form_state['values'];
    $form_state['rebuild'] = TRUE;
  }
  elseif ( isset($form_state['storage']['original_form']['menu_list']) ) {
    $menu_lists = $form_state['storage']['original_form']['menu_list'];
      foreach ($menu_lists as $menu) {
        db_delete('link_title')
          ->condition('id', $menu)
          ->execute();
      }
    drupal_set_message(t("Menu links removed successfully."));
  }
  else{
    drupal_set_message(t('No menu is selected to remove. Please select any menu to remove.'), 'error');
  }
}

