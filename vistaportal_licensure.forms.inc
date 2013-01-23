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
    $form['licensure']['fcvs']['#attributes'] = array('class' => array('textfield-license'));

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
      if ($i > 0) {
        $form['licenses'][$i]['type']['#prefix'] = '<div class="line-solid"></div><h3>License ' . ($i + 1) . '</h3><br/>';
      }
      $form['licenses'][$i]['orig_lic' . $i] = checkbox('Original State License');
      $form['licenses'][$i]['orig_lic' . $i]['#required'] = FALSE;
      $form['licenses'][$i]['lic_type' . $i] = lic('License Type');
      $form['licenses'][$i]['country' . $i] = country('Country');
      $form['licenses'][$i]['state' . $i] = state('State');
      $form['licenses'][$i]['lic_number' . $i] = textfield('License #');
      $form['licenses'][$i]['lic_number' . $i]['#attributes'] = array('class' => array('textfield-license'));
      $form['licenses'][$i]['date_issued' . $i] = date_my('Date Issued');
      $form['licenses'][$i]['date_expired' . $i] = date_my('Expiration Date');
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
      if ($i > 0) {
        $form['deareg'][$i]['dea_type']['#prefix'] = '<div class="line-solid3"></div><h3>DEA Registration ' . ($i + 1) . '</h3><br/>';
      }
      $form['deareg'][$i]['dea_country' . $i] = country('Country');
      $form['deareg'][$i]['dea_lic_num' . $i] = textfield('License #');
      $form['deareg'][$i]['dea_lic_num' . $i]['#attributes'] = array('class' => array('textfield-license'));
      $form['deareg'][$i]['dea_date_issued' . $i] = date_my('Date Issued');
      $form['deareg'][$i]['dea_date_expired' . $i] = date_my('Date Expired');
      $form['deareg'][$i]['schedule' . $i] = array(
        '#prefix' => '<div class="schedule">',
        '#markup' => 'Schedule',
        '#required' => TRUE,
        '#suffix' => '</div>',
      );
      $form['deareg'][$i]['not' . $i] = checkbox('Not Applicable');
      $form['deareg'][$i]['not' . $i]['#required'] = FALSE;
      $form['deareg'][$i]['all' . $i] = checkbox('All');
      $form['deareg'][$i]['all' . $i]['#required'] = FALSE;
      $form['deareg'][$i]['all' . $i]['#suffix'] = '<div class="small-line"></div>';

      $form['deareg'][$i]['schedules2' . $i] = checkbox('2');
      $form['deareg'][$i]['schedules2' . $i]['#required'] = FALSE;

      $form['deareg'][$i]['schedules3' . $i] = checkbox('3');
      $form['deareg'][$i]['schedules3' . $i]['#required'] = FALSE;

      $form['deareg'][$i]['schedules4' . $i] = checkbox('4');
      $form['deareg'][$i]['schedules4' . $i]['#required'] = FALSE;

      $form['deareg'][$i]['schedules2N' . $i] = checkbox('2N');
      $form['deareg'][$i]['schedules2N' . $i]['#required'] = FALSE;

      $form['deareg'][$i]['schedules3N' . $i] = checkbox('3N');
      $form['deareg'][$i]['schedules3N' . $i]['#required'] = FALSE;

      $form['deareg'][$i]['schedules5' . $i] = checkbox('5');
      $form['deareg'][$i]['schedules5' . $i]['#required'] = FALSE;
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
    $form['deareg']['language_spoken']['#required'] = FALSE;
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
      '#value' => t('Submit'),
      '#name' => 'next',
      '#submit' => array('vistaportal_licensure_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
    );
		
		$form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button')),
      '#submit' => array('vistaportal_next'),
    );
		$form['next']['#attributes'] = array('class' => array('next'));
		
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
      '#submit' => array('vistaportal_licensure_previous'),
    );

    $form['prev']['#attributes'] = array('class' => array('prev'));
    $form['#after_build'][] = 'vistaportal_licensure_form_afterbuild';
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

    $licensure = new stdClass();
    $licensure -> uid = $user -> uid;
    $licensure -> fcvs = $form_state['values']['licensure']['fcvs'];

    db_insert('vss_licensure') -> fields(array(
      'uid' => $licensure -> uid,
      'fcvs' => $licensure -> fcvs,
    )) -> execute();

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

    $licenses = new stdClass();

    unset($form_state['values']['licenses']['add_another'], $form_state['values']['licenses']['remove_license']);
    foreach ($form_state['values']['licenses'] AS $key => $value) {
      $form_state['values']['licenses'][$key]['date_issued' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['licenses'][$key]['date_issued' . $key]));
      $form_state['values']['licenses'][$key]['date_expired' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['licenses'][$key]['date_expired' . $key]));
      $licenses -> uid = $user -> uid;
      $licenses -> lic_type = $form_state['values']['licenses'][$key]['lic_type' . $key];
      $licenses -> state = $form_state['values']['licenses'][$key]['state' . $key];
      $licenses -> lic_number = $form_state['values']['licenses'][$key]['lic_number' . $key];
      $licenses -> country = $form_state['values']['licenses'][$key]['country' . $key];
      $licenses -> date_issued = $form_state['values']['licenses'][$key]['date_issued' . $key];
      $licenses -> date_expired = $form_state['values']['licenses'][$key]['date_expired' . $key];

      db_insert('vss_licenses') -> fields(array(
        'uid' => $licenses -> uid,
        'lic_type' => $licenses -> lic_type,
        'state' => $licenses -> state,
        'lic_number' => $licenses -> lic_number,
        'country' => $licenses -> country,
        'date_issued' => $licenses -> date_issued,
        'date_expired' => $licenses -> date_expired,
      )) -> execute();
    }

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
    $deareg = new stdClass();
    unset($form_state['values']['deareg']['add_another'], $form_state['values']['deareg']['remove_deareg'], $form_state['values']['deareg']['lines'], $form_state['values']['deareg']['language_spoken'], $form_state['values']['deareg']['na'], $form_state['values']['deareg']['pending']);
    foreach ($form_state['values']['deareg'] AS $key => $value) {
      $form_state['values']['deareg'][$key]['dea_date_issued' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['deareg'][$key]['dea_date_issued' . $key]));
      $form_state['values']['deareg'][$key]['dea_date_expired' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['deareg'][$key]['dea_date_expired' . $key]));
      $deareg -> uid = $user -> uid;
      $deareg -> dea_lic_num = $form_state['values']['deareg'][$key]['dea_lic_num' . $key];
      $deareg -> country = $form_state['values']['deareg'][$key]['dea_country' . $key];
      $deareg -> dea_date_issued = $form_state['values']['deareg'][$key]['dea_date_issued' . $key];
      $deareg -> dea_date_expired = $form_state['values']['deareg'][$key]['dea_date_expired' . $key];

      $deareg -> schedule2 = $form_state['values']['deareg'][$key]['schedules2' . $key];
      $deareg -> schedule3 = $form_state['values']['deareg'][$key]['schedules3' . $key];
      $deareg -> schedule4 = $form_state['values']['deareg'][$key]['schedules4' . $key];
      $deareg -> schedule5 = $form_state['values']['deareg'][$key]['schedules5' . $key];
      $deareg -> schedule2N = $form_state['values']['deareg'][$key]['schedules2N' . $key];
      $deareg -> schedule3N = $form_state['values']['deareg'][$key]['schedules3N' . $key];

      db_insert('vss_deareg') -> fields(array(
        'uid' => $deareg -> uid,
        'lic_number' => $deareg -> dea_lic_num,
        'country' => $deareg -> country,
        'date_issued' => $deareg -> dea_date_issued,
        'date_expired' => $deareg -> dea_date_expired,
        'schedule_2' => $deareg -> schedule2,
        'schedule_3' => $deareg -> schedule3,
        'schedule_4' => $deareg -> schedule4,
        'schedule_5' => $deareg -> schedule5,
        'schedule_2n' => $deareg -> schedule2N,
        'schedule_3n' => $deareg -> schedule3N,
      )) -> execute();
    }

    /*
     * Update the drupal_flags table by setting the deareg
     * status flag, letting us know that the form has been filled out.
     */

    db_update('vss_drupal_flags') -> fields(array('deareg' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/disciplinary' . $user -> uid);

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

  /*
   * Implements the afterbuild
   */
  function vistaportal_licensure_form_afterbuild($form, &$form_state) {
    if ($form_state['values']['licensure']['na']) {
      unset($form['licensure']['fcvs']['#required']);
    }
    if ($form_state['values']['deareg']['na']) {
      unset($form['deareg'][0]['dea_country0'], $form['deareg'][0]['dea_lic_num0'], $form['deareg'][0]['dea_date_issued0'], $form['deareg'][0]['dea_date_expired0']);
    }
    return $form;

  }

  function vistaportal_licensure_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/certifications' . $user -> uid);
  }
 
 /*
   * Go to the next page
   */
  function vistaportal_next($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/disciplinary' . $user -> uid);
  }	