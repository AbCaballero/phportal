<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the references section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the references form.
   */
  function vistaportal_references_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    drupal_add_library('system', 'drupal.ajax');
    drupal_add_library('system', 'jquery.form');
    //Set this to tree so we can access all dynamic form values
    $form['#tree'] = TRUE;
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));
    $form['references'] = fieldset('');
    $form['references']['title'] = array('#markup' => '<h2>RESIDENCY</h2><br />', );

    $form['references'] = array(
      '#type' => 'fieldset',
      '#title' => t('REFERENCES'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="references-fieldset-wrapper">',
      '#suffix' => '</div>',
    );
    $form['references']['txt'] = array('#markup' => t('<p>Please list a minimum of six professional references with whom you have worked in the past two years and who
  	can attest to your specific medical abilities.</p>'), );

    if (empty($form_state['references_count'])) {
      $form_state['references_count'] = 6;
    }

    for ($i = 0; $i < $form_state['references_count']; $i++) {
      $j = $i + 1;
      //This is the line separator
      $form['references'][$i]['line'] = array(
        '#prefix' => '<div class="line-solid">',
        //'#markup' => '<hr>',
        '#attributes' => array('class' => array('line-solid')),
        '#suffix' => '</div>',
      );
      $form['references'][$i]['header'] = array('#markup' => '<h3>Reference ' . $j . ' </h3><br />', );
      $form['references'][$i]['name' . $i] = textfield('Name');
      $form['references'][$i]['name' . $i]['#prefix'] = '<div class = "reference-name">';
      $form['references'][$i]['name' . $i]['#suffix'] = '</div>';
      $form['references'][$i]['association' . $i] = textfield('Association');
      $form['references'][$i]['association' . $i]['#prefix'] = '<div class = "reference-association">';
      $form['references'][$i]['association' . $i]['#suffix'] = '</div>';
      $form['references'][$i]['specialty' . $i] = textfield('Specialty');
      $form['references'][$i]['specialty' . $i]['#prefix'] = '<div class = "reference-specialty">';
      $form['references'][$i]['specialty' . $i]['#suffix'] = '</div>';
      // $form['references'][$i]['phone_num'] = textfield('Phone');
      $form['references'][$i]['phone_choice' . $i] = array(
        '#prefix' => '<div class="phone_choice">',
        '#type' => 'select',
        '#title' => t('Phone'),
        '#options' => drupal_map_assoc(array(
          '-Select-',
          'Home',
          'Cell',
          'Work'
        )),
        '#required' => FALSE,
        '#suffix' => '</div>',
      );
      $form['references'][$i]['phone' . $i] = array(
        '#prefix' => '<div class="phone_number phone_txtfld">',
        '#type' => textfield,
        '#title' => t(''),
        '#required' => FALSE,
        '#suffix' => '</div>',
	 '#attributes' => array('class' => array('textfield-phone')),
      );
      $form['references'][$i]['email' . $i] = email('Email');
      $form['references'][$i]['email' . $i]['#attributes'] = array('class' => array('reference-email'));

      $form['references'][$i]['#title'] = 'References ' . ($i + 1);
    }

    $form['references']['references_another'] = array(
      '#type' => 'submit',
      '#value' => t('+ Add Additional references'),
      '#submit' => array('vistaportal_references_add'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'vistaportal_references_callback',
        'wrapper' => 'references-fieldset-wrapper',
        'method' => 'replaceWith',
        'speed' => 'fast',
      ),
    );

    if ($form_state['references_count'] > 6) {
      $form['references']['references_remove'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove Additional references'),
        '#submit' => array('vistaportal_references_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_references_callback',
          'wrapper' => 'references-fieldset-wrapper',
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
      '#value' => t('Submit'),
      '#name' => 'next',
      '#submit' => array('vistaportal_references_form_submit'),
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
      '#submit'=> array('vistaportal_save_logout'),
    );

    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button prev prev')),
      '#submit'=> array('vistaportal_references_previous'),
    );
    $form['prev']['#attributes'] = array('class' => array('prev'));
    return $form;
  }

  /*
   * Ajax callback for the references form
   */
  function vistaportal_references_callback($form, $form_state) {
    return $form['references'];
  }

  /*
   * Increment the counter when the button is pressed
   */
  function vistaportal_references_add($form, &$form_state) {
    $form_state['references_count']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the counter when the button is pressed
   */
  function vistaportal_references_remove($form, &$form_state) {
    if ($form_state['references_count'] > 6) {
      $form_state['references_count']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * This is the form submission callback for the references form.
   */

  function vistaportal_references_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);

    /* Save the form values to the references table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we need to
     * unset and then reset the references status flag in
     * the drupal_flags table.
     */
    db_update('vss_drupal_flags') -> fields(array('ref' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the references table.*/
    db_delete('vss_references') -> condition('uid', $user -> uid) -> execute();
    unset($form_state['values']['references']['references_another']);
    /*Insert the form_state values into the references table.
     * @TODO remember to add the dynamic fields to the form
     * and also to the db_query.
     */
    $references = new stdClass();
    foreach ($form_state['values']['references'] AS $key => $value) {
      $references -> uid = $user -> uid;
      $references -> name = $form_state['values']['references'][$key]['name' . $key];
      $references -> association = $form_state['values']['references'][$key]['association' . $key];
      $references -> specialty = $form_state['values']['references'][$key]['specialty' . $key];
      $references -> phone_num = $form_state['values']['references'][$key]['phone' . $key];
      $references -> email = $form_state['values']['references'][$key]['email' . $key];

      db_insert('vss_references') -> fields(array(
        'uid' => $references -> uid,
        'name' => $references -> name,
        'association' => $references -> association,
        'specialty' => $references -> specialty,
        'email' => $references -> email,
        'phone_num' => $references -> phone_num,
      )) -> execute();
    }
    /*
     * Update the vss_drupal_flags table by setting the references
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags ') -> fields(array('ref' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/upload' . $user -> uid);
  }

  function vistaportal_references_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/disciplinary' . $user -> uid);
  }

  /*
   * Go to the next page
   */
  function vistaportal_next($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/upload' . $user -> uid);
  }	
