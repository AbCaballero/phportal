<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the licensure section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the licensure form.
   */
  function vistaportal_licensure_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    drupal_add_library('system', 'drupal.ajax');
    drupal_add_library('system', 'jquery.form');
    //Set this to tree so we can access all dynamic form values
    $form['#tree'] = TRUE;
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));

    // This is the licensure form
    $form['licensure'] = array(
      '#type' => 'fieldset',
      '#title' => t('LICENSES'),
      '#collapsible' => FALSE,
    );

    $form['licensure']['na'] = checkbox('Not Applicable');
    $form['licensure']['na']['#required'] = FALSE;
    $form['licensure']['fcvs'] = textfield('FCVS(Federation Credentials Verification) Profile #');
    //This is the line separator
    $form['licensure']['line3'] = array(
      '#prefix' => '<div class="line-solid">',
      //'#markup' => '<hr>',
      '#attributes' => array('class' => array('line-solid')),
      '#suffix' => '</div>',
    );

    //This is the licenses form
    $form['licenses'] = array(
      '#type' => 'fieldset',
      '#title' => t('License 1'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="licenses-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    //This counter will be used to determine how many lincenses sections to add
    if (empty($form_state['licenses_num'])) {
      $form_state['licenses_num'] = 1;
    }

    for ($i = 0; $i < $form_state['licenses_num']; $i++) {
      $form['licenses'][$i]['orig_lic'] = checkbox('Original State License');
      $form['licenses'][$i]['orig_lic']['#required'] = FALSE;
      $form['licenses'][$i]['lic_type'] = lic('License Type');
      $form['licenses'][$i]['country'] = country('Country');
      $form['licenses'][$i]['state'] = state('State');
      $form['licenses'][$i]['lic_number'] = textfield('License #');
      $form['licenses'][$i]['date_issued'] = date_my('Date Issued');
      $form['licenses'][$i]['date_expired'] = date_my('Expiration Date');
    }

    $form['licenses']['add_another'] = array(
      '#type' => 'submit',
      '#value' => t('+ Add Additional License'),
      '#submit' => array('vistaportal_licenses_add'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'vistaportal_licenses_form_add_callback',
        'wrapper' => 'licenses-fieldset-wrapper',
        'method' => 'replaceWith',
        'speed' => 'fast',
      ),
    );

    //This is the line separator
    $form['medlicensure']['line'] = array(
      '#prefix' => '<div class="line-solid1">',
      //'#markup' => '<hr>',
      '#attributes' => array('class' => array('line-solid')),
      '#suffix' => '</div>',
    );

    //First license is mandatory
    if ($form_state['licenses_num'] > 1) {
      $form['licenses']['remove_license'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove Additional License'),
        '#submit' => array('vistaportal_licenses_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_licenses_form_add_callback',
          'wrapper' => 'licenses-fieldset-wrapper',
        ),
      );
    }

    //This is the DEA registration form
    $form['deareg'] = array(
      '#type' => 'fieldset',
      '#title' => t('DEA REGISTRATION'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="deareg-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    $form['deareg']['na'] = checkbox('Not Applicable');
    $form['deareg']['na']['#required'] = FALSE;
    $form['deareg']['pending'] = checkbox('Pending');
    $form['deareg']['pending']['#required'] = FALSE;

    //This counter will be used to determine how many lincenses sections to add
    if (empty($form_state['deareg_num'])) {
      $form_state['deareg_num'] = 1;
    }

    for ($i = 0; $i < $form_state['deareg_num']; $i++) {

      $form['deareg'][$i]['dea_country'] = country('Country');
      $form['deareg'][$i]['dea_lic_num'] = textfield('License #');
      $form['deareg'][$i]['dea_date_issued'] = date_my('Date Issued');
      $form['deareg'][$i]['dea_date_expired'] = date_my('Date Expired');
      $form['deareg'][$i]['schedule'] = array(
        '#prefix' => '<div class="schedule">',
        '#markup' => 'Schedule',
        '#required' => TRUE,
        '#suffix' => '</div>',
      );
      $form['deareg'][$i]['not'] = checkbox('Not Applicable');
      $form['deareg'][$i]['not']['#required'] = FALSE;
      $form['deareg'][$i]['all'] = checkbox('All');
      $form['deareg'][$i]['all']['#required'] = FALSE;
      $form['deareg'][$i]['all']['#suffix'] = '<div class="small-line"></div>';

      $form['deareg'][$i]['schedules2'] = checkbox('2');
      $form['deareg'][$i]['schedules2']['#required'] = FALSE;

      $form['deareg'][$i]['schedules3'] = checkbox('3');
      $form['deareg'][$i]['schedules3']['#required'] = FALSE;

      $form['deareg'][$i]['schedules4'] = checkbox('4');
      $form['deareg'][$i]['schedules4']['#required'] = FALSE;

      $form['deareg'][$i]['schedules2N'] = checkbox('2N');
      $form['deareg'][$i]['schedules2N']['#required'] = FALSE;

      $form['deareg'][$i]['schedules3N'] = checkbox('3N');
      $form['deareg'][$i]['schedules3N']['#required'] = FALSE;

      $form['deareg'][$i]['schedules5'] = checkbox('5');
      $form['deareg'][$i]['schedules5']['#required'] = FALSE;

      /*$form['deareg'][$i]['schedules'] = array(
       '#type' => 'checkboxes',
       '#title' => t(''),
       '#options' => drupal_map_assoc(array(
       2,
       3,
       4,

       t('2N'),
       t('3N'),
       5,
       )),
       );*/
    }

    $form['deareg']['add_another'] = array(
      '#type' => 'submit',
      '#value' => t('+ Add Additional DEA Registration'),
      '#submit' => array('vistaportal_deareg_add'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'vistaportal_deareg_form_add_callback',
        'wrapper' => 'deareg-fieldset-wrapper',
        'method' => 'replaceWith',
        'speed' => 'fast',
      ),
    );

    //First DEA registration is mandatory

    if ($form_state['deareg_num'] > 1) {
      $form['deareg']['remove_deareg'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove Additional DEA Registration'),
        '#submit' => array('vistaportal_deareg_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_deareg_form_add_callback',
          'wrapper' => 'deareg-fieldset-wrapper',
        ),
      );
    }
    //This is the line separator
    $form['deareg']['lines'] = array(
      '#prefix' => '<div class="line-solid">',
      //'#markup' => '<hr>',
      '#attributes' => array('class' => array('line-solid')),
      '#suffix' => '</div>',
    );

    $form['deareg']['language_spoken'] = textfield('In addition to English, other languages spoken
        with communication ease and/or fluency');
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
      '#submit' => array('vistaportal_licensure_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
    );
    $form['save_logout'] = button('Save & Logout');
    $form['prev'] = button('Previous');
    $form['prev']['#attributes'] = array('class' => array('prev'));

    return $form;
  }

  /*
   * This is the form submission callback for the premed form.
   */

  function vistaportal_licensure_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);

    /* Save the form values to the licensure table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the licensure status flag in
     * the drupal_flags table.
     */
    db_update('vss_drupal_flags') -> fields(array('licensure' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the licensure table.*/

    db_delete('vss_licensure') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the licensure table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */

    /*   $licensure = new stdClass();
     =======
     $licensure = new stdClass();
     >>>>>>> 8946bcadc7a780506ff46361d45d209ffd27df17
     $licensure -> uid = $user -> uid;
     $licensure -> fcvs = $form_state['values']['licensure']['fcvs'];
     $licensure -> language_spoken = $form_state['values']['licensure']['language_spoken'];

     db_insert('vss_licensure') -> fields(array(
     'uid' => $licensure -> uid,
     'fcvs' => $licensure -> fcvs,
     'language_spoken' => $licensure -> language_spoken,
     <<<<<<< HEAD
     )) -> execute();*/

    /*
     * Update the drupal_flags table by setting the licensure
     * status flag, letting us know that the form has been filled out.
     */

    db_update('vss_drupal_flags') -> fields(array('licensure' => 1, )) -> condition('uid', $user -> uid) -> execute();

    /* Save the form values to the licenses table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the licenses status flag in
     * the drupal_flags table.
     */

    db_update('vss_drupal_flags') -> fields(array('licenses' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the licenses table.*/

    db_delete('vss_licenses') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the licenses table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */

    /*   $licenses = new stdClass();
     =======
     $licenses = new stdClass();
     >>>>>>> 8946bcadc7a780506ff46361d45d209ffd27df17
     foreach ($form_state['values']['licenses'] AS $key => $value) {
     $form_state['values']['licenses'][$key]['date_issued'] = date('Y-m-d H:i:s', strtotime($form_state['values']['licenses'][$key]['date_issued']));
     $form_state['values']['licenses'][$key]['date_expired'] = date('Y-m-d H:i:s', strtotime($form_state['values']['licenses'][$key]['date_expired']));
     $licenses -> uid = $user -> uid;
     $licenses -> lic_type = $form_state['values']['licenses'][$key]['lic_type'];
     $licenses -> state = $form_state['values']['licenses'][$key]['state'];
     $licenses -> lic_number = $form_state['values']['licenses'][$key]['lic_number'];
     $licenses -> country = $form_state['values']['licenses'][$key]['country'];
     $licenses -> date_issued = $form_state['values']['licenses'][$key]['date_issued'];
     $licenses -> date_expired = $form_state['values']['licenses'][$key]['date_expired'];

     db_insert('vss_licenses') -> fields(array(
     'uid' => $licenses -> uid,
     'lic_type' => $licenses -> lic_type,
     'state' => $licenses -> state,
     'lic_number' => $licenses -> lic_number,
     'country' => $licenses -> country,
     'date_issued' => $licenses -> date_issued,
     'date_expired' => $licenses -> date_expired,
     )) -> execute();
     <<<<<<< HEAD
     }*/

    /*
     * Update the drupal_flags table by setting the deareg
     * status flag, letting us know that the form has been filled out.
     */

    db_update('vss_drupal_flags') -> fields(array('licenses' => 1, )) -> condition('uid', $user -> uid) -> execute();

    /* Save the form values to the deareg table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the deareg status flag in
     * the drupal_flags table.
     */

    db_update('vss_drupal_flags') -> fields(array('deareg' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the deareg table.*/

    db_delete('vss_deareg') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the deareg table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */

    /*   dsm($form_state, 'form state');
     $deareg = new stdClass();
     foreach ($form_state['values']['deareg'] AS $key => $value) {
     $form_state['values']['deareg'][$key]['dea_date_issued'] = date('Y-m-d H:i:s', strtotime($form_state['values']['deareg'][$key]['dea_date_issued']));
     $form_state['values']['deareg'][$key]['dea_date_expired'] = date('Y-m-d H:i:s', strtotime($form_state['values']['deareg'][$key]['dea_date_expired']));
     $deareg -> uid = $user -> uid;
     $deareg -> dea_lic_num = $form_state['values']['deareg'][$key]['dea_lic_num'];
     $deareg -> country = $form_state['values']['deareg'][$key]['country'];
     $deareg -> dea_date_issued = $form_state['values']['deareg'][$key]['dea_date_issued'];
     $deareg -> dea_date_expired = $form_state['values']['deareg'][$key]['dea_date_expired'];

     db_insert('vss_deareg') -> fields(array(
     'uid' => $deareg -> uid,
     'dea_lic_num' => $deareg -> dea_lic_num,
     'country' => $deareg -> country,
     'dea_date_issued' => $deareg -> dea_date_issued,
     'dea_date_expired' => $deareg -> dea_date_expired,
     )) -> execute();
     }*/

    /*
     * Update the drupal_flags table by setting the deareg
     * status flag, letting us know that the form has been filled out.
     */

    db_update('vss_drupal_flags') -> fields(array('deareg' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/internship' . $user -> uid);

  }

  /*
   * Ajax callback for the license form
   */

  function vistaportal_licenses_form_add_callback($form, $form_state) {
    return $form['licenses'];
  }

  /*
   * Ajax callback for the dea registration form
   */

  function vistaportal_deareg_form_add_callback($form, $form_state) {
    return $form['deareg'];
  }

  /*
   * Increment the counter when the button is pressed
   */

  function vistaportal_licenses_add($form, &$form_state) {
    $form_state['licenses_num']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the counter when the button is pressed
   */

  function vistaportal_licenses_remove($form, &$form_state) {
    if ($form_state['licenses_num'] > 1) {
      $form_state['licenses_num']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Increment the counter when the button is pressed
   */

  function vistaportal_deareg_add($form, &$form_state) {
    $form_state['deareg_num']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the counter when the button is pressed
   */

  function vistaportal_deareg_remove($form, &$form_state) {
    if ($form_state['deareg_num'] > 1) {
      $form_state['deareg_num']--;
    }
    $form_state['rebuild'] = TRUE;
  }
