<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the certifications section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the certifications form.
   */
  function vistaportal_certifications_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    $form['#tree'] = TRUE;
    $form['certifications'] = array(
      '#type' => 'fieldset',
      '#title' => t('CERTIFICATIONS'),
      '#collapsible' => FALSE,
    );
    $form['certifications']['board'] = array(
      '#type' => 'container',
      '#prefix' => '<div id="board-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    //This counter will be used to determine how many board certifications to add

    if (empty($form_state['boardcerts_count'])) {
      $form_state['boardcerts_count'] = 1;
    }

    for ($i = 0; $i < $form_state['boardcerts_count']; $i++) {
      $j = $i + 1;
      $form['certifications']['board'][$i]['title_board' . $i] = array(
        '#type' => 'fieldset',
        '#title' => 'Board Certifications ' . $j . '',
        '#collapsible' => FALSE,
      );
      $form['certifications']['board'][$i]['not_applicable' . $i] = checkbox('Not Applicable');
      unset($form['certifications']['board'][$i]['not_applicable' . $i]['#required']);
      $form['certifications']['board'][$i]['current_board' . $i] = array(
        '#prefix' => '<div class="label-board">',
        '#markup' => t('Current Specialty Board Status'),
        '#required' => TRUE,
        '#suffix' => '</div>',
      );
      $form['certifications']['board'][$i]['board_status' . $i] = radios_board_status('');
      $form['certifications']['board'][$i]['board_sciences' . $i] = medical_specialty('American Board of Medical Sciences:');
      $form['certifications']['board'][$i]['cert_recert' . $i] = cert_recert('Was this a certification or a Recertification?');
      $form['certifications']['board'][$i]['board_exp_date' . $i] = date_my('Date');
      $form['certifications']['board'][$i]['cert_number' . $i] = textfield('Certificate #');
      $form['certifications']['board'][$i]['cert_number' . $i]['#attributes'] = array('class' => array('textfield-license'));

      $form['certifications']['board']['board_another'] = array(
        '#type' => 'submit',
        '#value' => t('+ Add Additional Board Certification'),
        '#submit' => array('vistaportal_board_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_boardcert_callback',
          'wrapper' => 'board-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );

      if ($form_state['boardcerts_count'] > 1) {

        $form['certifications']['board']['board_remove'] = array(
          '#type' => 'submit',
          '#value' => t('- Remove Board Certification'),
          '#submit' => array('vistaportal_board_remove'),
          '#limit_validation_errors' => array(),
          '#ajax' => array(
            'callback' => 'vistaportal_boardcert_callback',
            'wrapper' => 'board-fieldset-wrapper',
          ),
        );
      }
      //This is the line separator
      $form['certifications']['line'] = array(
        '#prefix' => '<div class="line-solid">',
        '#suffix' => '</div>',
      );

      //This counter will be used to determine how many other certifications to add
      if (empty($form_state['othcerts_count'])) {
        $form_state['othcerts_count'] = 1;
      }
      $form['certifications']['addCerts'] = array(
        '#type' => 'container',
        '#prefix' => '<div id="othcert-fieldset-wrapper">',
        '#suffix' => '</div>',
      );
      for ($i = 0; $i < $form_state['othcerts_count']; $i++) {
        $j = $i + 1;
        $form['certifications']['addCerts']['other'][$i]['set' . $i] = array(
          '#type' => 'fieldset',
          '#title' => 'Additional Certifications ' . $j . '',
          '#collapsible' => FALSE,
        );
        $form['certifications']['addCerts']['other'][$i]['other_certifications' . $i] = other_certifications('Type');
        $form['certifications']['addCerts']['other'][$i]['cert_name' . $i] = textfield('Certificate Name');
        $form['certifications']['addCerts']['other'][$i]['cert_num' . $i] = textfield('Certificate Number');
        $form['certifications']['addCerts']['other'][$i]['cert_num' . $i]['#attributes'] = array('class' => array('textfield-license'));
        $form['certifications']['addCerts']['other'][$i]['cert_exp_date' . $i] = date_my('Expiration Date');
      }

      $form['certifications']['addCerts']['othcert_another'] = array(
        '#type' => 'submit',
        '#value' => t('+ Add Additional Certification'),
        '#submit' => array('vistaportal_othcert_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_othcert_callback',
          'wrapper' => 'othcert-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );

      if ($form_state['othcerts_count'] > 1) {
        $form['certifications']['addCerts']['othcert_remove'] = array(
          '#type' => 'submit',
          '#value' => t('- Remove Certification'),
          '#submit' => array('vistaportal_othcert_remove'),
          '#limit_validation_errors' => array(),
          '#ajax' => array(
            'callback' => 'vistaportal_othcert_callback',
            'wrapper' => 'othcert-fieldset-wrapper',
          ),
        );
      }
      //This is the line separator
      $form['certifications']['line1'] = array(
        '#prefix' => '<div class="line-solid">',
        '#suffix' => '</div>',
      );
      $form['certifications']['ecfmg_number'] = textfield('ECFMG Certificate #');
      $form['certifications']['ecfmg_number']['#attributes'] = array('class' => array('textfield-license'));
      $form['certifications']['ecfmg_exp_date'] = date_my('Expiration Date');

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
        '#submit' => array('vistaportal_certifications_form_submit'),
        '#attributes' => array('class' => array('affiliations-submit')),
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
        '#attributes' => array('class' => array('button prev')),
        '#submit' => array('vistaportal_certifications_previous'),
      );

      $form['prev']['#attributes'] = array('class' => array('prev'));
      $form['#after_build'][] = 'vistaportal_certifications_form_afterbuild';
      return $form;
    }

    function vistaportal_certifications_form_submit($form, &$form_state) {
      global $user;
      $account = user_load($user -> uid);

      /* If the user refills this form, we need to unset the
       * internship status flag in the vss_drupal_flags table.
       */

      db_update('vss_drupal_flags') -> fields(array('certifications' => 0, )) -> condition('uid', $user -> uid) -> execute();

      $board_certification = new stdClass();
      $board_certification -> uid = $user -> uid;
      unset($form_state['values']['certifications']['board']['board_another'], $form_state['values']['certifications']['board']['board_remove']);
      foreach ($form_state['values']['certifications']['board'] AS $key => $value) {
        $form_state['values']['certifications']['board'][$key]['board_exp_date' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['certifications']['board'][$key]['board_exp_date' . $key]));
        $board_certification -> status = $form_state['values']['certifications']['board'][$key]['board_status' . $key];
        $board_certification -> board = $form_state['values']['certifications']['board'][$key]['board_sciences' . $key];
        $board_certification -> cert_recert = $form_state['values']['certifications']['board'][$key]['cert_recert' . $key];
        $board_certification -> exp_date = $form_state['values']['certifications']['board'][$key]['board_exp_date' . $key];
        $board_certification -> cert_num = $form_state['values']['certifications']['board'][$key]['cert_number' . $key];

        db_insert('vss_certifications') -> fields(array(
          'uid' => $board_certification -> uid,
          'board_status' => $board_certification -> status,
          'board' => $board_certification -> board,
          'board_exp_date' => $board_certification -> exp_date,
          'cert_num' => $board_certification -> cert_num,
          'cert_recert' => $board_certification -> cert_recert,
        )) -> execute();

      }

      /*
       * Update the vss_drupal_flags table by setting the internship
       * status flag, letting us know that the form has been filled out.
       */

      db_update('vss_drupal_flags	') -> fields(array('certifications' => 1, )) -> condition('uid', $user -> uid) -> execute();

      db_update('vss_drupal_flags') -> fields(array('additional_certifications' => 0, )) -> condition('uid', $user -> uid) -> execute();

      $additional_certification = new stdClass();
      $additional_certification -> uid = $user -> uid;
      unset($form_state['values']['certifications']['addCerts']['othcert_another'], $form_state['values']['certifications']['addCerts']['othcert_remove']);
      foreach ($form_state['values']['certifications']['addCerts']['other'] AS $key => $value) {
        $form_state['values']['certifications']['addCerts']['other'][$key]['cert_exp_date' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['certifications']['addCerts']['other'][$key]['cert_exp_date' . $key]));
        $additional_certification -> type = $form_state['values']['certifications']['addCerts']['other'][$key]['other_certifications' . $key];
        $additional_certification -> exp_date = $form_state['values']['certifications']['addCerts']['other'][$key]['cert_exp_date' . $key];
        $additional_certification -> cert_name = $form_state['values']['certifications']['addCerts']['other'][$key]['cert_name' . $key];
        $additional_certification -> cert_num = $form_state['values']['certifications']['addCerts']['other'][$key]['cert_num' . $key];

        db_insert('vss_additional_certifications') -> fields(array(
          'uid' => $additional_certification -> uid,
          'type' => $additional_certification -> type,
          'cert_name' => $additional_certification -> cert_name,
          'exp_date' => $additional_certification -> exp_date,
          'cert_num' => $additional_certification -> cert_num,
        )) -> execute();

      }

      db_update('vss_drupal_flags	') -> fields(array('additional_certifications' => 1, )) -> condition('uid', $user -> uid) -> execute();

      $user = user_load($form_state['uid']);
      drupal_goto('preapp/exams' . $user -> uid);
    }

    /*
     * Ajax callback for the premed form
     */
    function vistaportal_boardcert_callback($form, $form_state) {

      return $form['certifications']['board'];
    }

    /*
     * Increment the counter when the button is pressed
     */
    function vistaportal_board_add($form, &$form_state) {
      $form_state['boardcerts_count']++;
      $form_state['rebuild'] = TRUE;
    }

    /*
     * Decrement the counter when the button is pressed
     */
    function vistaportal_board_remove($form, &$form_state) {
      if ($form_state['boardcerts_count'] > 1) {
        $form_state['boardcerts_count']--;
      }
      $form_state['rebuild'] = TRUE;
    }

    /*
     * Ajax callback for the premed form
     */
    function vistaportal_othcert_callback($form, $form_state) {

      return $form['certifications']['addCerts'];
    }

    /*
     * Increment the counter when the button is pressed
     */
    function vistaportal_othcert_add($form, &$form_state) {
      $form_state['othcerts_count']++;
      $form_state['rebuild'] = TRUE;
    }

    /*
     * Decrement the counter when the button is pressed
     */
    function vistaportal_othcert_remove($form, &$form_state) {
      if ($form_state['othcerts_count'] > 1) {
        $form_state['othcerts_count']--;
      }
      $form_state['rebuild'] = TRUE;
    }

    /*
     * Implements the afterbuild function
     */
    function vistaportal_certifications_form_afterbuild($form, &$form_state) {
      if ($form_state['values']['certifications']['board'][0]['not_applicable0']) {
        unset($form['certifications']['board'][0]['board_status0']['#required'], $form['certifications']['board'][0]['board_sciences0']['#required'], $form['certifications']['board'][0]['cert_recert0']['#required'], $form['certifications']['board'][0]['cert_number0']['#required'], $form['certifications']['board'][0]['board_exp_date0']['#required']);
      }
      return $form;
    }

    function vistaportal_certifications_previous($form, &$form_state) {
      $user = user_load($form_state['uid']);
      drupal_goto('preapp/affiliations' . $user -> uid);
    }

  }
