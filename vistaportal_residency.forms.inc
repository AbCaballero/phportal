<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the residency section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the residency form.
   */
  function vistaportal_residency_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    $form = array();
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));
    $form['residency'] = array(
      '#type' => 'fieldset',
      '#title' => t('RESIDENCY'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="residency-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    /*This counter will be used to determine the number
     of residency sections to add
     */

    if (empty($form_state['num_res'])) {
      $form_state['num_res'] = 1;
    }

    for ($i = 0; $i < $form_state['num_res']; $i++) {
      $form['residency'][$i]['na'] = array(
        '#type' => 'checkbox',
        '#title' => t('Not Applicable'),
        '#required' => FALSE,
      );
      $form['residency'][$i]['type'] = textfield('Type');
      $form['residency'][$i]['institution'] = textfield('Institution');
      $form['residency'][$i]['country'] = country('Country');
      $form['residency'][$i]['state'] = state('State');
     
      $form['residency'][$i]['city'] = textfield('City');
      $form['residency'][$i]['date_from'] = date_my('From');
      $form['residency'][$i]['date_to'] = date_my('To');
      $form['residency'][$i]['prog_dir'] = textfield('Program Director');
    }

    if ($form_state['num_res'] < 3) {
      $form['residency']['add_res'] = array(
        '#type' => 'submit',
        '#value' => t('Add Additional Residency'),
        '#submit' => array('vistaportal_residency_form_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_residency_callback',
          'wrapper' => 'residency-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );
    }

    if ($form_state['num_res'] > 1) {
      $form['residency']['remove_res'] = array(
        '#type' => 'submit',
        '#value' => t('Remove A Residency'),
        '#submit' => array('vistaportal_residency_form_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_residency_callback',
          'wrapper' => 'residency-fieldset-wrapper',
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

    $form['fellowship'] = array(
      '#type' => 'fieldset',
      '#title' => t('ADDITIONAL RESIDENCY OR FELLOWSHIP OR OTHER GRADUATE EDUCATION'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="fellowship-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    if (empty($form_state['num_fellow'])) {
      $form_state['num_fellow'] = 1;
    }

    for ($i = 0; $i < $form_state['num_fellow']; $i++) {
      $form['fellowship'][$i]['na'] = array(
        '#type' => 'checkbox',
        '#title' => t('Not Applicable'),
        '#required' => FALSE,
      );
      $form['fellowship'][$i]['type'] = textfield('Type');
      $form['fellowship'][$i]['institution'] = textfield('Institution');
      $form['fellowship'][$i]['country'] = country('Country');
      $form['fellowship'][$i]['state'] = state('State');
      $form['fellowship'][$i]['city'] = textfield('City');
      $form['fellowship'][$i]['date_from'] = date_my('From');
      $form['fellowship'][$i]['date_to'] = date_my('To');
      $form['fellowship'][$i]['prog_dir'] = textfield('Program Director');
    }

    if ($form_state['num_fellow'] < 3) {
      $form['fellowship']['add_fellow'] = array(
        '#type' => 'submit',
        '#value' => t('Add Additional Institution'),
        '#submit' => array('vistaportal_fellowship_form_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_fellowship_callback',
          'wrapper' => 'fellowship-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );
    }

    if ($form_state['num_fellow'] > 1) {
      $form['fellowship']['remove_fellow'] = array(
        '#type' => 'submit',
        '#value' => t('Remove A Institution'),
        '#submit' => array('vistaportal_fellowship_form_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_fellowship_callback',
          'wrapper' => 'fellowship-fieldset-wrapper',
        ),
      );
    }

    //this is a line at the bottom
	$form['last']['line'] = array(
	'#prefix' => '<div class="line_left">',
		'#markup' => '<hr>',
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
      '#submit' => array('vistaportal_residency_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
    );
		$form['save_logout'] = button('Save & Logout');
    $form['prev'] = button('Previous');
    return $form;
  }

  /*
   * This is the form submission callback for the residency form.
   */

  function vistaportal_residency_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);
    //$user_name;
    //$html_string;
    //make_pdf;
    //make_tiff;
    //save record

    /* If the user refills this form, we need to unset the
     * residency status flag in the vss_drupal_flags table.
     */
    db_update('vss_drupal_flags	') -> fields(array('residency' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the residency table.*/
    db_delete('vss_residency') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the residency table.*/
    $residency = new stdClass();
    $residency -> uid = $user -> uid;
    $residency -> type = $form_state['values']['residency']['type'];
    $residency -> institution = $form_state['values']['residency']['institution'];
    $residency -> city = $form_state['values']['residency']['city'];
    $residency -> state = $form_state['values']['residency']['state'];
    $residency -> country = $form_state['values']['residency']['country'];
    $residency -> date_from = $form_state['values']['residency']['date_from'];
    $residency -> date_to = $form_state['values']['residency']['date_to'];
    $residency -> prog_dir = $form_state['values']['residency']['prog_dir'];

    db_insert('vss_residency') -> fields(array(
      'uid' => $residency -> uid,
      'type' => $residency -> type,
      'institution' => $residency -> institution,
      'city' => $residency -> city,
      'state' => $residency -> state,
      'country' => $residency -> country,
      'date_from' => $residency -> date_from,
      'date_to' => $residency -> date_to,
      'prog_dir' => $residency -> prog_dir,
    )) -> execute();

    /*
     * Update the vss_drupal_flags table by setting the residency
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags	') -> fields(array('residency' => 1, )) -> condition('uid', $user -> uid) -> execute();
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/affiliations' . $user -> uid);
  }

  /*
   * Ajax callback for the residency and fellowship forms
   */

  function vistaportal_add_residency_callback($form, $form_state) {
    return $form['residency'];
  }

  function vistaportal_add_fellowship_callback($form, $form_state) {
    return $form['fellowship'];
  }

  /*
   * Increment the residency counter when the button is pressed
   */

  function vistaportal_residency_form_add($form, &$form_state) {
    $form_state['num_res']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the residency counter when the button is pressed
   */

  function vistaportal_residency_form_remove($form, &$form_state) {
    if ($form_state['num_res'] > 1) {
      $form_state['num_res']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Increment the fellowship counter when the button is pressed
   */

  function vistaportal_fellowship_form_add($form, &$form_state) {
    $form_state['num_fellow']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the fellowship counter when the button is pressed
   */

  function vistaportal_fellowship_form_remove($form, &$form_state) {
    if ($form_state['num_fellow'] > 1) {
      $form_state['num_fellow']--;
    }
    $form_state['rebuild'] = TRUE;
  }
