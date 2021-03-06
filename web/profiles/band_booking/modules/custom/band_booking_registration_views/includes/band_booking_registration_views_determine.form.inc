<?php
/**
 * @file
 * Code for the form to 
 */

function band_booking_registration_views_determine_form($form, &$form_state, $op, $rid) {
  // @TODO Idea = create automatic workflow state for band_booking, and add a textfield for icon
  $icons = array(
    'wait' => '',//'&#xe804',
    'postpone' => '',//'&#xe800',
    'accept' => '',//&#xe802
    'refuse' => '',//&#xe803
  );

  // Generate a unique key.
  $unique_key = 'determine_registration_' . $op . '_' . $rid;

  $form = [
    '#prefix' => '<div class="determine-registration" id="' . $unique_key .'">',
    '#suffix' => '</div>',
    '#attributes' => array(
      'class' => array(
        'determine-form',
        $op
      )
    ),
    'operation' => array(
      '#type' => 'value',
      '#value' => $op,
    ),
    'rid' => array(
      '#type' => 'value',
      '#value' => $rid,
    ),
    'actions' => [
      'submit' => array(
        '#type' => 'submit',
        '#value' => $icons[$op],
        '#ajax' => array(
          'wrapper' => $unique_key,
          //TODO set a custom callback to regenarate page part
          // DO not call the submit who "determine registration"
          //'callback' => 'band_booking_registration_views_determine_form_submit',
        )
      )
    ],
  ];

  return $form;
}

function band_booking_registration_views_determine_form_validate($form, &$form_state) {
  //watchdog('registration', 'band_booking_registration_views_determine_form_validate');
  //TODO check if user has right
  //only if current user has right to edit registration state

  //form_set_error('field_name', t("Password doesn't match"));
}

function band_booking_registration_views_determine_form_submit($form, &$form_state) {
  $operation = $form_state['values']['operation'];
  $rid = $form_state['values']['rid'];
  $status = '';
  $entity_type = 'registration';

  // @TODO set it to automatic generated... $status = $operation
  if ($operation == 'wait') {
    $status = 'waiting';
  } elseif ($operation == 'postpone') {
    $status = 'postponed';
  } elseif ($operation == 'accept') {
    $status = 'accepted';
  } elseif ($operation == 'refuse') {
    $status = 'refused';
  }
  $registration = entity_load_single($entity_type, $rid);
  $registration->state = $status;
  entity_save($entity_type, $registration);
}
