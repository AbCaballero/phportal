<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the education section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the premed form.
   */
  function vistaportal_education_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    drupal_add_library('system', 'drupal.ajax');
    drupal_add_library('system', 'jquery.form');
    //Set this to tree so we can access all dynamic form values
    $form['#tree'] = TRUE;
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));
    $date = date('Y-m-d H:m:s');
    $format = 'Y-m';
    $format1 = 'Y-m-d';
    //This is the pre-med education form
    $form['premed'] = array(
      '#type' => 'fieldset',
      '#title' => t('PRE-MEDICAL EDUCATION (OPTIONAL)'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="premed-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    //This counter will be used to determine how many premed sections to add
    if (empty($form_state['p_num_schools'])) {
      $form_state['p_num_schools'] = 1;
    }

    for ($i = 0; $i < $form_state['p_num_schools']; $i++) {
      if ($i > 0) {
        $form['premed'][$i]['title-txt' . $i]['#prefix'] = '<div class="line-solid"></div><h2> Pre-Medical Education ' . ($i + 1) . '</h2><br/>';
      }
      $form['premed'][$i]['school' . $i] = textfield('School of Graduation');
      $form['premed'][$i]['school' . $i]['#prefix'] = '<div class = "premed-school">';
      $form['premed'][$i]['school' . $i]['#suffix'] = '</div>';
      $form['premed'][$i]['school' . $i]['#required'] = FALSE;
      $form['premed'][$i]['country' . $i] = country('Country');
      $form['premed'][$i]['country' . $i]['#prefix'] = '<div class = "premed-country">';
      $form['premed'][$i]['country' . $i]['#suffix'] = '</div>';
      $form['premed'][$i]['country' . $i]['#required'] = FALSE;
      $form['premed'][$i]['state' . $i] = state('State');
      $form['premed'][$i]['state' . $i]['#prefix'] = '<div class = "premed-state">';
      $form['premed'][$i]['state' . $i]['#suffix'] = '</div>';
      $form['premed'][$i]['state' . $i]['#required'] = FALSE;
      $form['premed'][$i]['city' . $i] = textfield('City');
      $form['premed'][$i]['city' . $i]['#required'] = FALSE;
      $form['premed'][$i]['city' . $i]['#prefix'] = '<div class = "premed-city">';
      $form['premed'][$i]['city' . $i]['#suffix'] = '</div>';
      //This is the date
      $form['premed'][$i]['date' . $i] = array(
        '#prefix' => '<div class="premed-date">',
        '#markup' => 'Dates Attended',
        '#suffix' => '</div>',
      );
      $form['premed'][$i]['date_from' . $i] = date_my('From');
      $form['premed'][$i]['date_from' . $i]['#prefix'] = '<div class = "premed-date-from">';
      $form['premed'][$i]['date_from' . $i]['#suffix'] = '</div>';
      $form['premed'][$i]['date_to' . $i] = date_my('To');
      $form['premed'][$i]['date_to' . $i]['#prefix'] = '<div class = "premed-date-to">';
      $form['premed'][$i]['date_to' . $i]['#suffix'] = '</div>';
      $form['premed'][$i]['degree' . $i] = edu('Degree');
      $form['premed'][$i]['degree' . $i]['#required'] = FALSE;
      $form['premed'][$i]['degree' . $i]['#prefix'] = '<div class = "premed-degree">';
      $form['premed'][$i]['degree' . $i]['#suffix'] = '</div>';
    }
    //Only allow 3 schools for the premed form
    if ($form_state['p_num_schools'] < 3) {
      $form['premed']['add_another'] = array(
        //'#prefix' => '<div class="edu-btn">',
        '#type' => 'submit',
        '#value' => t('+ Add Additional Pre-medical Institution'),
        '#submit' => array('vistaportal_form_premed_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_premed_form_add_school_callback',
          'wrapper' => 'premed-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );
    }

    //First school is mandatory
    if ($form_state['p_num_schools'] > 1) {
      $form['premed']['remove_school'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove A Pre-medical Institution'),
        '#submit' => array('vistaportal_form_premed_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_premed_form_add_school_callback',
          'wrapper' => 'premed-fieldset-wrapper',
        ),
      );
    }

    //This is the line separator
    $form['p']['line3'] = array(
      '#prefix' => '<div class="line-solid">',
      //'#markup' => '<hr>',
      '#attributes' => array('class' => array('line-solid')),
      '#suffix' => '</div>',
    );

    //This is the medical school form
    $form['med'] = array(
      '#type' => 'fieldset',
      '#title' => t('MEDICAL EDUCATION'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="med-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    //This counter will be used to determine how many medical school sections to add
    if (empty($form_state['m_num_schools'])) {
      $form_state['m_num_schools'] = 1;
    }

    for ($i = 0; $i < $form_state['m_num_schools']; $i++) {
      if ($i > 0) {
        $form['med'][$i]['title-txt' . $i]['#prefix'] = '<div class="line-solid"></div><h2> Medical Education ' . ($i + 1) . '</h2><br/>';
      }
      $form['med'][$i]['school' . $i] = textfield('School of Graduation');
      $form['med'][$i]['school' . $i]['#prefix'] = '<div class = "med-school">';
      $form['med'][$i]['school' . $i]['#suffix'] = '</div>';
      $form['med'][$i]['country' . $i] = country('Country');
      $form['med'][$i]['country' . $i]['#prefix'] = '<div class = "med-country">';
      $form['med'][$i]['country' . $i]['#suffix'] = '</div>';
      $form['med'][$i]['state' . $i] = state('State');
      $form['med'][$i]['state' . $i]['#prefix'] = '<div class = "med-state">';
      $form['med'][$i]['state' . $i]['#suffix'] = '</div>';
      $form['med'][$i]['city' . $i] = textfield('City');
      $form['med'][$i]['city' . $i]['#prefix'] = '<div class = "med-city">';
      $form['med'][$i]['city' . $i]['#suffix'] = '</div>';

      //This is the date
      $form['med'][$i]['date' . $i] = array(
        '#prefix' => '<div class="med-date">',
        '#markup' => 'Dates Attended',
        '#suffix' => '</div>',
      );
      $form['med'][$i]['date_from' . $i] = date_my('From');
      $form['med'][$i]['date_from' . $i]['#prefix'] = '<div class = "med-date-from">';
      $form['med'][$i]['date_from' . $i]['#suffix'] = '</div>';
      $form['med'][$i]['date_to' . $i] = date_my('To');
      $form['med'][$i]['date_to' . $i]['#prefix'] = '<div class = "med-date-to">';
      $form['med'][$i]['date_to' . $i]['#suffix'] = '</div>';
      $form['med'][$i]['degree' . $i] = edu('Degree');
      $form['med'][$i]['degree' . $i]['#prefix'] = '<div class = "med-degree">';
      $form['med'][$i]['degree' . $i]['#suffix'] = '</div>';
      $form['med'][$i]['ecfmg' . $i] = textfield('ECFMG CERTIFICATE #');
      $form['med'][$i]['ecfmg' . $i]['#prefix'] = '<div class = "med-ecfmg">';
      $form['med'][$i]['ecfmg' . $i]['#suffix'] = '</div>';

      //added fields
      $form['med'][$i]['valid' . $i] = array(
        '#prefix' => '<div class="var_label">',
        '#markup' => t('Valid Indefinitely'),
        '#required' => TRUE,
        '#suffix' => '</div>',
      );
      $form['med'][$i]['valid-indef' . $i] = radios_yesno();
      $form['med'][$i]['valid-indef' . $i]['#prefix'] = '<div class = "med-yes-no">';
      $form['med'][$i]['valid-indef' . $i]['#suffix'] = '</div>';
      $form['med'][$i]['exp_date' . $i] = date_my('If no state expiration date');
      $form['med'][$i]['exp_date' . $i]['#prefix'] = '<div class = "med-exp-date">';
      $form['med'][$i]['exp_date' . $i]['#suffix'] = '</div>';
    }

    //Only allow 3 schools for the med form
    if ($form_state['m_num_schools'] < 3) {
      $form['med']['add_another'] = array(
        '#type' => 'submit',
        '#value' => t('+ Add Additional Institution'),
        '#submit' => array('vistaportal_form_med_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_med_form_add_school_callback',
          'wrapper' => 'med-fieldset-wrapper',
          'method' => 'replaceWith',
        ),
      );
    }

    //First school is mandatory
    if ($form_state['m_num_schools'] > 1) {
      $form['med']['remove_school'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove A Medical Institution'),
        '#submit' => array('vistaportal_form_med_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_med_form_add_school_callback',
          'wrapper' => 'med-fieldset-wrapper',
        ),
      );
    }

    //this is a line at the bottom
    $form['last']['line'] = array(
      '#prefix' => '<div class="line_left">',
      //'#markup' => '<hr>',
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
      '#submit' => array('vistaportal_education_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
    );
    $form['save_logout'] = button('Save & Logout');
    $form['prev'] = button('Previous');

    return $form;
  }

  /*
   * This is the form submission callback for the premed form.
   */

  function vistaportal_education_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);

    /* Save the form values to the premed table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the premed status flag in
     * the drupal_flags table.
     */
    db_update('vss_drupal_flags') -> fields(array('premed' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the premed table.*/
    db_delete('vss_premed') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the premed table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */
    $premed = new stdClass();
    unset($form_state['values']['premed']['add_another'], $form_state['values']['premed']['remove_school']);
    foreach ($form_state['values']['premed'] AS $key => $value) {
      $form_state['values']['premed'][$key]['date_from' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['premed'][$key]['date_from' . $key]));
      $form_state['values']['premed'][$key]['date_to' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['premed'][$key]['date_to' . $key]));
      $premed -> uid = $user -> uid;
      $premed -> school = $form_state['values']['premed'][$key]['school' . $key];
      $premed -> degree = $form_state['values']['premed'][$key]['degree' . $key];
      $premed -> city = $form_state['values']['premed'][$key]['city' . $key];
      $premed -> state = $form_state['values']['premed'][$key]['state' . $key];
      $premed -> country = $form_state['values']['premed'][$key]['country' . $key];
      $premed -> date_from = $form_state['values']['premed'][$key]['date_from' . $key];
      $premed -> date_to = $form_state['values']['premed'][$key]['date_to' . $key];

      db_insert('vss_premed') -> fields(array(
        'uid' => $premed -> uid,
        'school' => $premed -> school,
        'degree' => $premed -> degree,
        'city' => $premed -> city,
        'state' => $premed -> state,
        'country' => $premed -> country,
        'date_from' => $premed -> date_from,
        'date_to' => $premed -> date_to,
      )) -> execute();
    }
    /*
     * Update the drupal_flags table by setting the premed
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags') -> fields(array('premed' => 1, )) -> condition('uid', $user -> uid) -> execute();

    /* Save the form values to the med table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the premed status flag in
     * the drupal_flags table.
     */
    db_update('vss_drupal_flags') -> fields(array('medschool' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the med table.*/
    db_delete('vss_medschool') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the med table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */
    $med = new stdClass();
    unset($form_state['values']['med']['add_another'], $form_state['values']['med']['remove_school']);
    foreach ($form_state['values']['med'] AS $key => $value) {
      $form_state['values']['med'][$key]['date_from' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['med'][$key]['date_from' . $key]));
      $form_state['values']['med'][$key]['date_to' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['med'][$key]['date_to' . $key]));
      $med -> uid = $user -> uid;
      $med -> school = $form_state['values']['med'][$key]['school' . $key];
      $med -> degree = $form_state['values']['med'][$key]['degree' . $key];
      $med -> city = $form_state['values']['med'][$key]['city' . $key];
      $med -> state = $form_state['values']['med'][$key]['state' . $key];
      $med -> country = $form_state['values']['med'][$key]['country' . $key];
      $med -> date_from = $form_state['values']['med'][$key]['date_from' . $key];
      $med -> date_to = $form_state['values']['med'][$key]['date_to' . $key];
      $med -> ecfmg = $form_state['values']['med'][$key]['ecfmg' . $key];
      watchdog('errors', $key);
      db_insert('vss_medschool') -> fields(array(
        'uid' => $med -> uid,
        'school' => $med -> school,
        'degree' => $med -> degree,
        'city' => $med -> city,
        'state' => $med -> state,
        'country' => $med -> country,
        'date_from' => $med -> date_from,
        'date_to' => $med -> date_to,
        'ecfmg' => $med -> ecfmg,
      )) -> execute();
    }
    /*
     * Update the drupal_flags table by setting the premed
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags') -> fields(array('medschool' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/internship' . $user -> uid);

    /*
     * @TODO add error checking
     */

  }

  /*
   * Ajax callback for the premed form
   */
  function vistaportal_premed_form_add_school_callback($form, $form_state) {
    return $form['premed'];
  }

  /*
   * Ajax callback for the med form
   */
  function vistaportal_med_form_add_school_callback($form, $form_state) {
    return $form['med'];
  }

  /*
   * Increment the premed counter when the button is pressed
   */
  function vistaportal_form_premed_add($form, &$form_state) {
    $form_state['p_num_schools']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   =======
   $form['prev'] = button('Previous');
   $form['save_logout'] = button('Save & Logout');

   return $form;
   }

   /*
   * This is the form submission callback for the premed form.
   */

  function vistaportal_education_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);

    /* Save the form values to the premed table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the premed status flag in
     * the drupal_flags table.
     */
    db_update('vss_drupal_flags') -> fields(array('premed' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the premed table.*/
    db_delete('vss_premed') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the premed table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */
    $premed = new stdClass();
    unset($form_state['values']['premed']['add_another'], $form_state['values']['med']['add_another']);
    foreach ($form_state['values']['premed'] AS $key => $value) {
      $form_state['values']['premed'][$key]['date_from'] = date('Y-m-d H:i:s', strtotime($form_state['values']['premed'][$key]['date_from']));
      $form_state['values']['premed'][$key]['date_to'] = date('Y-m-d H:i:s', strtotime($form_state['values']['premed'][$key]['date_to']));
      $premed -> uid = $user -> uid;
      $premed -> school = $form_state['values']['premed'][$key]['school'];
      $premed -> degree = $form_state['values']['premed'][$key]['degree'];
      $premed -> city = $form_state['values']['premed'][$key]['city'];
      $premed -> state = $form_state['values']['premed'][$key]['state'];
      $premed -> country = $form_state['values']['premed'][$key]['country'];
      $premed -> date_from = $form_state['values']['premed'][$key]['date_from'];
      $premed -> date_to = $form_state['values']['premed'][$key]['date_to'];

      db_insert('vss_premed') -> fields(array(
        'uid' => $premed -> uid,
        'school' => $premed -> school,
        'degree' => $premed -> degree,
        'city' => $premed -> city,
        'state' => $premed -> state,
        'country' => $premed -> country,
        'date_from' => $premed -> date_from,
        'date_to' => $premed -> date_to,
      )) -> execute();
    }
    /*
     * Update the drupal_flags table by setting the premed
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags') -> fields(array('premed' => 1, )) -> condition('uid', $user -> uid) -> execute();

    /* Save the form values to the med table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the premed status flag in
     * the drupal_flags table.
     */
    db_update('vss_drupal_flags') -> fields(array('medschool' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the med table.*/
    db_delete('vss_medschool') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the med table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */
    $med = new stdClass();
    foreach ($form_state['values']['med'] AS $key => $value) {
      $form_state['values']['med'][$key]['date_from'] = date('Y-m-d H:i:s', strtotime($form_state['values']['med'][$key]['date_from']));
      $form_state['values']['med'][$key]['date_to'] = date('Y-m-d H:i:s', strtotime($form_state['values']['med'][$key]['date_to']));
      $med -> uid = $user -> uid;
      $med -> school = $form_state['values']['med'][$key]['school'];
      $med -> degree = $form_state['values']['med'][$key]['degree'];
      $med -> city = $form_state['values']['med'][$key]['city'];
      $med -> state = $form_state['values']['med'][$key]['state'];
      $med -> country = $form_state['values']['med'][$key]['country'];
      $med -> date_from = $form_state['values']['med'][$key]['date_from'];
      $med -> date_to = $form_state['values']['med'][$key]['date_to'];
      $med -> ecfmg = $form_state['values']['med'][$key]['ecfmg'];
      watchdog('errors', $key);
      db_insert('vss_medschool') -> fields(array(
        'uid' => $med -> uid,
        'school' => $med -> school,
        'degree' => $med -> degree,
        'city' => $med -> city,
        'state' => $med -> state,
        'country' => $med -> country,
        'date_from' => $med -> date_from,
        'date_to' => $med -> date_to,
        'ecfmg' => $med -> ecfmg,
      )) -> execute();
    }
    /*
     * Update the drupal_flags table by setting the premed
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags') -> fields(array('medschool' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/internship' . $user -> uid);

    /*
     * @TODO add error checking
     */

  }

  /*
   * Ajax callback for the premed form
   */
  function vistaportal_premed_form_add_school_callback($form, $form_state) {
    return $form['premed'];
  }

  /*
   * Ajax callback for the med form
   */
  function vistaportal_med_form_add_school_callback($form, $form_state) {
    return $form['med'];
  }

  /*
   * Increment the premed counter when the button is pressed
   */
  function vistaportal_form_premed_add($form, &$form_state) {
    $form_state['p_num_schools']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   >>>>>>> 8946bcadc7a780506ff46361d45d209ffd27df17
   * Decrement the premed counter when the button is pressed
   */
  function vistaportal_form_premed_remove($form, &$form_state) {
    if ($form_state['p_num_schools'] > 1) {
      $form_state['p_num_schools']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Increment the med counter when the button is pressed
   */
  function vistaportal_form_med_add($form, &$form_state) {
    $form_state['m_num_schools']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the med counter when the button is pressed
   */
  function vistaportal_form_med_remove($form, &$form_state) {
    if ($form_state['m_num_schools'] > 1) {
      $form_state['m_num_schools']--;
    }
    $form_state['rebuild'] = TRUE;
  }
