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
function vistaportal_affiliations_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['#attributes'] = array('enctype' => "multipart/form-data");
	$form['affiliations'] = array(
  	'#type'=>'fieldset',
    '#collapsible' => FALSE,
  );
	$form['affiliations']['listing'] = array(
  	'#markup' => t('<p>List all present and previous affiliations with healthcare facilities and medical staff memberships for the past 10 years,
   	in chronological order. Include clerkships, assistantships, and military experience. Specify all departments in which privileges were exercised
   	and the nature and extent of such privileges. <strong>ALL LOCUM TENENS WORK MUST BE INCLUDED WITH LOCATIONS AND DATES</strong></p>'),
  );
  $form['affiliations']['facility'] = textfield('Facility or Practice');
	$form['affiliations']['date_from'] = date_my('Dates From');
  $form['affiliations']['date_to'] = date_my('To');
	$form['affiliations']['address'] = textfield('Street Address');
	$form['affiliations']['country'] = country('Country');
	$form['affiliations']['state'] = state('State');
	$form['affiliations']['city'] = textfield('City');
	$form['affiliations']['zip'] = zip('Zip Code');
	$form['affiliations']['capacity'] = textfield('Capacity', 5);
	$form['prev'] = button('<Previous');
	$form['save_logout'] = button('Save & Logout');	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Next>'),
		'#name' => 'next',
		'#submit' => array('vistaportal_affiliations_form_submit'),
	);		
return $form;
}

/*
 * This is the form submission callback for the affiliations form.
 */
			
function vistaportal_affiliations_form_submit($form, &$form_state){
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
	db_update('vss_drupal_flags	')
		->fields(array(
			'affiliations'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the affiliations table.*/
	db_delete('vss_affiliations')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the affiliations table.*/
	$affiliations = new stdClass();
	foreach($form_state['values']['affiliations'] AS $key => $value){
		$affiliations->date_from = $form_state['values']['affiliations'][$key]['date_from'] = 
			date('Y-m-d H:i:s', strtotime($form_state['values']['affiliations'][$key]['date_from']));
  	$affiliations->date_to = $form_state['values']['affiliations'][$key]['date_to'] = 
  		date('Y-m-d H:i:s', strtotime($form_state['values']['affiliations'][$key]['date_to']));
		$affiliations->uid = $user->uid;
		$affiliations->facility = $form_state['values']['affiliations'][$key]['facility'];
		$affiliations->date_from = $form_state['values']['affiliations'][$key]['date_from']; 
  	$affiliations->date_to = $form_state['values']['affiliations'][$key]['date_to']; 
		$affiliations->address = $form_state['values']['affiliations'][$key]['address'];
		$affiliations->country = $form_state['values']['affiliations'][$key]['country'];
		$affiliations->state = $form_state['values']['affiliations'][$key]['state'];
		$affiliations->city = $form_state['values']['affiliations'][$key]['city'];
		$affiliations->zip = $form_state['values']['affiliations'][$key]['zip'];
		$affiliations->capacity = $form_state['values']['affiliations'][$key]['capacity'];
	
	
		db_insert('vss_affiliations')
			->fields(array(
				'uid' => $affiliations->uid,
				'facility' => $affiliations->facility,
				'date_from' => $affiliations -> date_from,
				'date_to' => $affiliations -> date_to,
				'address' => $affiliations->address,
				'country' => $affiliations->country,
				'state' => $affiliations->state,
				'city' => $affiliations->city,
				'zip' => $affiliations->zip,
				'capacity' => $affiliations->capacity,
			
		))
			->execute();
	}
/*
 * Update the vss_drupal_flags table by setting the affiliations 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags')
		->fields(array(
			'affiliations'=>1,
	))
		->condition('uid', $user->uid)
		->execute();	
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/certifications' . $user->uid);	
}		