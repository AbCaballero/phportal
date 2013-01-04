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
    $form = array();
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
      $form['internship'][$i]['na'] = array(
        '#type' => 'checkbox',
        '#title' => t('Not Applicable'),
        '#required' => FALSE,
      );
      $form['internship'][$i]['type'] = textfield('Type');
      $form['internship'][$i]['institution'] = textfield('Institution');
      $form['internship'][$i]['country'] = country('Country');
      $form['internship'][$i]['state'] = state('State');
      $form['internship'][$i]['city'] = textfield('City');
			//This is the date 
		  $form['internship'][$i]['date'] = array(
			'#markup' => 'Dates Attended',
			'#required' => TRUE,
		  );
      $form['internship'][$i]['date_from'] = date_my('From');
      $form['internship'][$i]['date_to'] = date_my('To');
      $form['internship'][$i]['prog_dir'] = textfield('Program Director');
    }

    if ($form_state['num_ints'] < 3) {
      $form['internship']['add_another'] = array(
        '#type' => 'submit',
        '#value' => t('Add Additional Institution'),
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

    if ($form_state['num_ints'] > 1) {
      $form['internship']['remove_school'] = array(
        '#type' => 'submit',
        '#value' => t('Remove A Institution'),
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
      '#submit' => array('vistaportal_internship_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
    );
		$form['save_logout'] = button('Save & Logout');
    $form['prev'] = button('Previous');
		
    //$form['#after_build'][] = 'vistaportal_internship_form_afterbuild';
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
    $internship -> type = $form_state['values']['internship']['type'];
    $internship -> institution = $form_state['values']['internship']['institution'];
    $internship -> city = $form_state['values']['internship']['city'];
    $internship -> state = $form_state['values']['internship']['state'];
    $internship -> country = $form_state['values']['internship']['country'];
    $internship -> date_from = $form_state['values']['internship']['date_from'];
    $internship -> date_to = $form_state['values']['internship']['date_to'];
    $internship -> prog_dir = $form_state['values']['internship']['prog_dir'];

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

    /*
     * Update the vss_drupal_flags table by setting the internship
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags	') -> fields(array('internship' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/residency' . $user -> uid);
  }

  /*
   * Implements #afterbuild
   */
  function vistaportal_internship_form_afterbuild($form, &$form_state) {
    if ($form_state['values']['internship']['na']) {
      unset($form['internship']['type']['#required'], $form['internship']['institution']['#required'], $form['internship']['country']['#required'], $form['internship']['state']['#required'], $form['internship']['state_other']['#required'], $form['internship']['city']['#required'], $form['internship']['date_from']['#required'], $form['internship']['date_to']['#required'], $form['internship']['prog_dir']['#required']);
    }
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
