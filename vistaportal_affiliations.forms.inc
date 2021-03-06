<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the affiliations section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the affiliations form.
   */
  function vistaportal_affiliations_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    drupal_add_library('system', 'drupal.ajax');
    drupal_add_library('system', 'jquery.form');
    //Set this to tree so we can access all dynamic form values
    $form['#tree'] = TRUE;
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));

    //This is Affiliation form
    $form['affiliations'] = array(
      '#type' => 'fieldset',
      '#title' => t('AFFILIATIONS'),
      '#collapsible' => FALSE,
    );

    $form['affiliations']['not_applicable'] = checkbox('Not Applicable');
    unset($form['affiliations']['not_applicable']['#required']);

    $form['affiliations']['listing'] = array('#markup' => t('<p>List all present and previous affiliations with healthcare facilities and medical staff memberships for the past 10 years,
    in chronological order. Include clerkships, assistantships, and military experience. Specify all departments in which privileges were exercised
    and the nature and extent of such privileges. <strong>ALL LOCUM TENENS WORK MUST BE INCLUDED WITH LOCATIONS AND DATES.</strong></p>'), );

    $form['affiliations_cntr'] = array(
      '#type' => 'fieldset',
      '#title' => t(''),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="affiliations-fieldset-wrapper">',
      '#suffix' => '</div>',
    );
    $form['affiliations_cntr']['top-line'] = array ( '#prefix' => '<div class="line-solid">','#suffix' => '</div>',);
    if (empty($form_state['affiliations_count'])) {
      $form_state['affiliations_count'] = 1;
    }

    for ($i = 0; $i < $form_state['affiliations_count']; $i++) {
    	
			
    	if ($i > 0) {
        $form['affiliations_cntr'][$i]['title-txt' . $i]['#prefix'] = '<h2> AFFILIATIONS ' . ($i + 1) . '</h2><br/>';
      }
      $form['affiliations_cntr'][$i]['facility'. $i] = textfield('Facility or Practice');
			$form['affiliations_cntr'][$i]['facility' . $i]['#prefix'] = '<div class = "affiliations-facility">' ;
			$form['affiliations_cntr'][$i]['facility' . $i]['#suffix'] = '</div>' ;
			$form['affiliations_cntr'][$i]['date'. $i] = array(
			'#prefix' => '<div class="date-title">',
			'#markup' => 'Dates Attended',
			'#required' => TRUE,
			'#suffix' => '</div>',
			);
      $form['affiliations_cntr'][$i]['date_from'. $i] = date_my('From');
			$form['affiliations_cntr'][$i]['date_from' . $i]['#prefix'] = '<div class = "affiliations-date_from">' ;
			$form['affiliations_cntr'][$i]['date_from' . $i]['#suffix'] = '</div>' ;
      $form['affiliations_cntr'][$i]['date_to'. $i] = date_my('To');
			$form['affiliations_cntr'][$i]['date_to' . $i]['#prefix'] = '<div class = "affiliations-date_to">' ;
			$form['affiliations_cntr'][$i]['date_to' . $i]['#suffix'] = '</div>' ;
      $form['affiliations_cntr'][$i]['address'. $i] = textfield('Street Address');
			$form['affiliations_cntr'][$i]['address' . $i]['#prefix'] = '<div class = "affiliations-address">' ;
			$form['affiliations_cntr'][$i]['address' . $i]['#suffix'] = '</div>' ;
      $form['affiliations_cntr'][$i]['country'. $i] = country('Country');
			$form['affiliations_cntr'][$i]['country' . $i]['#prefix'] = '<div class = "affiliations-country">' ;
			$form['affiliations_cntr'][$i]['country' . $i]['#suffix'] = '</div>' ;
			$form['affiliations_cntr'][$i]['state'. $i] = state('State');
			$form['affiliations_cntr'][$i]['state' . $i]['#prefix'] = '<div class = "affiliations-state">' ;
			$form['affiliations_cntr'][$i]['state' . $i]['#suffix'] = '</div>' ;
			$form['affiliations_cntr'][$i]['city'. $i] = textfield('City');
			$form['affiliations_cntr'][$i]['city' . $i]['#prefix'] = '<div class = "affiliations-city">' ;
			$form['affiliations_cntr'][$i]['city' . $i]['#suffix'] = '</div>' ;
			$form['affiliations_cntr'][$i]['zip'. $i] = zip('Zip Code');
			$form['affiliations_cntr'][$i]['zip' . $i]['#prefix'] = '<div class = "affiliations-zip">' ;
			$form['affiliations_cntr'][$i]['zip' . $i]['#suffix'] = '</div>' ;
      $form['affiliations_cntr'][$i]['capacity'. $i] = textfield('Capacity');
			$form['affiliations_cntr'][$i]['capacity' . $i]['#prefix'] = '<div class = "affiliations-capacity">' ;
			$form['affiliations_cntr'][$i]['capacity' . $i]['#suffix'] = '</div>' ;
    }
     if ($form_state['affiliations_count'] < 3) {
    $form['affiliations_cntr']['aff_another'] = array(
      '#type' => 'submit',
      '#value' => t('+ Add Another Affiliation'),
      '#submit' => array('vistaportal_affiliations_add'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'vistaportal_affiliations_callback',
        'wrapper' => 'affiliations-fieldset-wrapper',
        'method' => 'replaceWith',
        'speed' => 'fast',
      ),
    );
		}
    if ($form_state['affiliations_count'] > 1) {
      $form['affiliations_cntr']['aff_remove'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove Affiliation'),
        '#submit' => array('vistaportal_affiliations_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_affiliations_callback',
          'wrapper' => 'affiliations-fieldset-wrapper',
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
		'#submit' => array('vistaportal_affiliations_form_submit'),
		'#attributes' => array('class' => array('affiliations-submit')),
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
      '#submit'=> array('vistaportal_release_previous'),
    );

    $form['prev']['#attributes'] = array('class' => array('prev'));
    $form['#after_build'][] = 'vistaportal_affiliations_form_afterbuild';
  
    return $form;
  }

  /*
   * Ajax callback for the premed form
   */
  function vistaportal_affiliations_callback($form, $form_state) {

    return $form['affiliations_cntr'];
  }

  /*
   * Increment the counter when the button is pressed
   */
  function vistaportal_affiliations_add($form, &$form_state) {
    $form_state['affiliations_count']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the counter when the button is pressed
   */
  function vistaportal_affiliations_remove($form, &$form_state) {
    if ($form_state['affiliations_count'] > 1) {
      $form_state['affiliations_count']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * This is the form submission callback for the affiliations form.
   */

  function vistaportal_affiliations_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);
    //$user_name;
    //$html_string;
    //make_pdf;
    //make_tiff;
    //save record

    /* If the user refills this form, we need to unset the
     * affiliations status flag in the vss_drupal_flags table.
     */
    db_update('vss_drupal_flags	') -> fields(array('affiliations' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the affiliations table.*/
    db_delete('vss_affiliations') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the affiliations table.*/
    $affiliations_cntr = new stdClass();
    unset($form_state['values']['affiliations_cntr']['aff_remove'], $form_state['values']['affiliations_cntr']['aff_another']);
    foreach ($form_state['values']['affiliations_cntr'] AS $key => $value) {
      $form_state['values']['affiliations_cntr'][$key]['date_from' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['affiliations_cntr'][$key]['date_from' . $key]));
      $form_state['values']['affiliations_cntr'][$key]['date_to' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['affiliations_cntr'][$key]['date_to' . $key]));
      $affiliations_cntr -> uid = $user -> uid;
      $affiliations_cntr -> facility = $form_state['values']['affiliations_cntr'][$key]['facility' . $key];
      $affiliations_cntr -> date_from = $form_state['values']['affiliations_cntr'][$key]['date_from' . $key];
      $affiliations_cntr -> date_to = $form_state['values']['affiliations_cntr'][$key]['date_to' . $key];
      $affiliations_cntr -> address = $form_state['values']['affiliations_cntr'][$key]['address' . $key];
      $affiliations_cntr -> city = $form_state['values']['affiliations_cntr'][$key]['city' . $key];
      $affiliations_cntr -> state = $form_state['values']['affiliations_cntr'][$key]['state' . $key];
      $affiliations_cntr -> zip = $form_state['values']['affiliations_cntr'][$key]['zip' . $key];
      $affiliations_cntr -> country = $form_state['values']['affiliations_cntr'][$key]['country' . $key];
      $affiliations_cntr -> capacity = $form_state['values']['affiliations_cntr'][$key]['capacity' . $key];

      db_insert('vss_affiliations') -> fields(array(
        'uid' => $affiliations_cntr -> uid,
        'facility' => $affiliations_cntr -> facility,
        'address' => $affiliations_cntr -> address,
        'city' => $affiliations_cntr -> city,
        'state' => $affiliations_cntr -> state,
        'zip' => $affiliations_cntr -> zip,
        'date_from' => $affiliations_cntr -> date_from,
        'date_to' => $affiliations_cntr -> date_to,
        'country' => $affiliations_cntr -> country,
        'capacity' => $affiliations_cntr -> capacity,
      )) -> execute();
    }
    /*
     * Update the vss_drupal_flags table by setting the affiliations
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags	') -> fields(array('affiliations' => 1, )) -> condition('uid', $user -> uid) -> execute();

    $user = user_load($form_state['uid']);
    drupal_goto('preapp/certifications' . $user -> uid);
  }

  /*
   * Implements the afterbuild
   */
  function vistaportal_affiliations_form_afterbuild($form, &$form_state) {
    if ($form_state['values']['affiliations']['not_applicable']) {
      unset($form['affiliations_cntr'][0]['facility0']['#required'], $form['affiliations_cntr'][0]['date_from0']['#required'], $form['affiliations_cntr'][0]['date_to0']['#required'], $form['affiliations_cntr'][0]['address0']['#required'], $form['affiliations_cntr'][0]['country0']['#required'], $form['affiliations_cntr'][0]['state0']['#required'], $form['affiliations_cntr'][0]['city0']['#required'], $form['affiliations_cntr'][0]['zip0']['#required'], $form['affiliations_cntr'][0]['capacity0']['#required']);
    }
    return $form;
  }

  function vistaportal_release_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/residency' . $user -> uid);
  }
	
	/*
   * Go to the next page
   */
  function vistaportal_next($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/certifications' . $user -> uid);
  }