<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the internship section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the internship form.
   */
  function vistaportal_internship_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    $form['#tree'] = TRUE;
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));
    $form['internship'] = array(
      '#type' => 'fieldset',
      '#title' => t('INTERNSHIP'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="internship-fieldset-wrapper">',
      '#suffix' => '</div>',
    );
    /*This counter will be used to determine how many internship sections to add*/

    if (empty($form_state['num_ints'])) {
      $form_state['num_ints'] = 1;
    }

    for ($i = 0; $i < $form_state['num_ints']; $i++) {
      if ($i > 0) {
        $form['internship'][$i]['type']['#prefix'] = '<div class="line-solid"></div><h2>Internship ' . ($i + 1) . '</h2><br/>';
      }
      $form['internship']['na'] = array(
        '#type' => 'checkbox',
        '#title' => t('Not Applicable'),
        '#required' => FALSE,
      );
      /*---------------This adds the line each time that we add the fields------------*/

      /*if($i > 0) {
       $form['internship'][$i]['type' . $i]['#prefix'] = '<div class="line-solid"></div>';
       }*/

      $form['internship'][$i]['type' . $i] = textfield('Type');
      $form['internship'][$i]['type' . $i]['#maxlength'] = 40;
      $form['internship'][$i]['type' . $i]['#prefix'] = '<div class = "internship-type">';
      $form['internship'][$i]['type' . $i]['#suffix'] = '</div>';
      $form['internship'][$i]['institution' . $i] = textfield('Institution');
      $form['internship'][$i]['institution' . $i]['#maxlength'] = 40;
      $form['internship'][$i]['institution' . $i]['#prefix'] = '<div class = "internship-institution">';
      $form['internship'][$i]['institution' . $i]['#suffix'] = '</div>';
      $form['internship'][$i]['country' . $i] = country('Country');
      $form['internship'][$i]['country' . $i]['#prefix'] = '<div class = "internship-country">';
      $form['internship'][$i]['country' . $i]['#suffix'] = '</div>';
      $form['internship'][$i]['state' . $i] = state('State');
      $form['internship'][$i]['state' . $i]['#prefix'] = '<div class = "internship-state">';
      $form['internship'][$i]['state' . $i]['#suffix'] = '</div>';
      $form['internship'][$i]['city' . $i] = textfield('City');
      $form['internship'][$i]['city' . $i]['#maxlength'] = 20;
      $form['internship'][$i]['city' . $i]['#prefix'] = '<div class = "internship-city">';
      $form['internship'][$i]['city' . $i]['#suffix'] = '</div>';
      //This is the date
      $form['internship'][$i]['date' . $i] = array(
        '#prefix' => '<div class="date-title">',
        '#markup' => 'Dates Attended',
        '#required' => TRUE,
        '#suffix' => '</div>',
      );
      $form['internship'][$i]['date_from' . $i] = date_my('From');
      $form['internship'][$i]['date_from' . $i]['#prefix'] = '<div class = "internship-date_from">';
      $form['internship'][$i]['date_from' . $i]['#suffix'] = '</div>';
      $form['internship'][$i]['date_to' . $i] = date_my('To');
      $form['internship'][$i]['date_to' . $i]['#prefix'] = '<div class = "internship-date_to">';
      $form['internship'][$i]['date_to' . $i]['#suffix'] = '</div>';
      $form['internship'][$i]['prog_dir' . $i] = textfield('Program Director');
      $form['internship'][$i]['prog_dir' . $i]['#maxlength'] = 40;
      $form['internship'][$i]['prog_dir' . $i]['#prefix'] = '<div class = "internship-prog_dir">';
      $form['internship'][$i]['prog_dir' . $i]['#suffix'] = '</div>';

    }

    if ($form_state['num_ints'] < 3) {
      $form['internship']['add_another'] = array(
        '#type' => 'submit',
        '#value' => t('+ Add Additional Internship'),
        '#submit' => array('vistaportal_internship_form_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_internship_form_add_internship_callback',
          'wrapper' => 'internship-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );
    }

    //First school is mandatory
    if ($form_state['num_ints'] > 1) {
      $form['internship']['remove_school'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove Internship'),
        '#submit' => array('vistaportal_internship_form_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_internship_form_add_internship_callback',
          'wrapper' => 'internship-fieldset-wrapper',
        ),
      );
    }
    //this is a line at the bottom
    $form['last']['line'] = array(
      '#prefix' => '<div class="line_left">',
      //'#markup' => '<hr>',
      '#attributes' => array('class' => array('line_left')),
      '#suffix' => '</div>',
    );

    $form['last']['required_field'] = array(
      '#prefix' => '<div class="required_field2">',
      '#markup' => 'Required Field',
      '#required' => TRUE,
      '#suffix' => '</div>',
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save & Next'),
      '#name' => 'next',
      '#submit' => array('vistaportal_internship_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
    );
    $form['save_logout'] = array(
      '#type' => 'submit',
      '#value' => t('Save & Logout'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button')),
      '#submit' => array('vistaportal_save_logout'),
    );

    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button prev prev')),
      '#submit' => array('vistaportal_internship_previous'),
    );

    $form['prev']['#attributes'] = array('class' => array('prev'));
    $form['#after_build'][] = 'vistaportal_internship_form_afterbuild';
    return $form;
  }

  /*
   * This is the form submission callback for the internship form.
   */

  function vistaportal_internship_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);
    //$user_name;
    //$html_string;
    //make_pdf;
    //make_tiff;
    //save record

    /* If the user refills this form, we need to unset the
     * internship status flag in the vss_drupal_flags table.
     */
    db_update('vss_drupal_flags') -> fields(array('internship' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the internship table.*/
    db_delete('vss_internship') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the internship table.*/
    /*The ['internship'] index should fail here, but fails without it*/
    $internship = new stdClass();
    $internship -> uid = $user -> uid;

    unset($form_state['values']['internship']['add_another'], $form_state['values']['internship']['remove_school']);
    foreach ($form_state['values']['internship'] AS $key => $value) {
      $form_state['values']['internship'][$key]['date_from' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['internship'][$key]['date_from' . $key]));
      $form_state['values']['internship'][$key]['date_to' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['insternship'][$key]['date_to' . $key]));
      $internship -> type = $form_state['values']['internship'][$key]['type' . $key];
      $internship -> institution = $form_state['values']['internship'][$key]['institution' . $key];
      $internship -> city = $form_state['values']['internship'][$key]['city' . $key];
      $internship -> state = $form_state['values']['internship'][$key]['state' . $key];
      $internship -> country = $form_state['values']['internship'][$key]['country' . $key];
      $internship -> date_from = $form_state['values']['internship'][$key]['date_from' . $key];
      $internship -> date_to = $form_state['values']['internship'][$key]['date_to' . $key];
      $internship -> prog_dir = $form_state['values']['internship'][$key]['prog_dir' . $key];

      db_insert('vss_internship') -> fields(array(
        'uid' => $internship -> uid,
        'type' => $internship -> type,
        'institution' => $internship -> institution,
        'city' => $internship -> city,
        'state' => $internship -> state,
        'country' => $internship -> country,
        'date_from' => $internship -> date_from,
        'date_to' => $internship -> date_to,
        'prog_dir' => $internship -> prog_dir,
      )) -> execute();
    }
    /*
     * Update the vss_drupal_flags table by setting the internship
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags	') -> fields(array('internship' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/residency' . $user -> uid);
  }

  /*
   * Ajax callback for the internship form
   */
  function vistaportal_internship_form_add_internship_callback($form, $form_state) {
    return $form['internship'];
  }

  /*
   * Increment the internship counter when the button is pressed
   */
  function vistaportal_internship_form_add($form, &$form_state) {
    $form_state['num_ints']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the internship counter when the button is pressed
   */
  function vistaportal_internship_form_remove($form, &$form_state) {
    if ($form_state['num_ints'] > 1) {
      $form_state['num_ints']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Implements #afterbuild
   */
  function vistaportal_internship_form_afterbuild($form, &$form_state) {
    if ($form_state['values']['internship']['na']) {
      unset($form['internship'][0]['type0']['#required'], $form['internship'][0]['institution0']['#required'], $form['internship'][0]['state0']['#required'], $form['internship'][0]['city0']['#required'], $form['internship'][0]['date_from0']['#required'], $form['internship'][0]['date_to0']['#required'], $form['internship'][0]['prog_dir0']['#required']);
    }
    return $form;
  }

  function vistaportal_internship_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/education' . $user -> uid);
  }
