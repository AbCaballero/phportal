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
	$form['affiliations'] = fieldset('Affiliations');
	/*$affiliation_fields['facility'] = textfield('Facility or Practice');
	$affiliation_fields['address'] = textfield('Address');
	$affiliation_fields['city'] = textfield('City');
	$affiliation_fields['state'] = state('Sate');
	$affiliation_fields['zip'] = zip('Zip');
	$affiliation_fields['country'] = country('Country');*/
  $form['affiliations']['facility'] = textfield('Facility or Practice');
	$form['affiliations']['address'] = textfield('Address');
	$form['affiliations']['city'] = textfield('City');
	$form['affiliations']['state'] = state('Sate');
	$form['affiliations']['zip'] = zip('Zip');
	$form['affiliations']['country'] = country('Country');
	$form['affiliations']['affiliation_counter']['#type'] = "hidden";
	$form['affiliations']['affiliation_counter']['#default_value'] = -1;
	/*$form['affiliations']['add'] = vistaportal_set($affiliation_fields, 
		'Add another affiliation', 'Remove an affiliation', 3);*/
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
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
	$affiliations->uid = $user->uid;
	$affiliations->facility = $form_state['values']['affiliations']['facility'];
	$affiliations->address = $form_state['values']['affiliations']['address'];
	$affiliations->city = $form_state['values']['affiliations']['city'];
	$affiliations->state = $form_state['values']['affiliations']['state'];
	$affiliations->zip = $form_state['values']['affiliations']['zip'];
	$affiliations->country = $form_state['values']['affiliations']['country'];
	
	db_insert('vss_affiliations')
		->fields(array(
			'uid' => $affiliations->uid,
			'facility' => $affiliations->facility,
			'address' => $affiliations->address,
			'city' => $affiliations->city,
			'state' => $affiliations->state,
			'zip' => $affiliations->zip,
			'country' => $affiliations->country,
	))
		->execute();

/*
 * Update the vss_drupal_flags table by setting the affiliations 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags	')
		->fields(array(
			'affiliations'=>1,
	))
		->condition('uid', $user->uid)
		->execute();	
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/certifications' . $user->uid);	
}		