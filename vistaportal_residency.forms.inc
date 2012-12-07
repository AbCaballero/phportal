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
function vistaportal_residency_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['#attributes'] = array('enctype' => array("multipart/form-data"));
	$form['residency'] = fieldset('Residency');
	$form['residency']['type'] = textfield('Type');
	$form['residency']['institution'] = textfield('Institution');
	$form['residency']['city'] = textfield('City');
	$form['residency']['state'] = state('State');
	$form['residency']['country'] = country('Country');
	$form['residency']['date_from'] = date_popup('Start Date');
	$form['residency']['date_to'] = date_popup('End Date');
	$form['residency']['prog_dir'] = textfield('Program Director');
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_residency_form_submit'),
	);
return $form;
}

/*
 * This is the form submission callback for the residency form.
 */
			
function vistaportal_residency_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user -> uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record
	
/* If the user refills this form, we need to unset the
 * residency status flag in the drupal_flags table.	
 */
	db_update('drupal_flags	')
		->fields(array(
			'residency'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the residency table.*/
	db_delete('residency')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the residency table.*/
	$residency = new stdClass();
	$residency->uid = $user->uid;
	$residency->type = $form_state['values']['residency']['type'];
	$residency->institution = $form_state['values']['residency']['institution'];
	$residency->city = $form_state['values']['residency']['city'];
	$residency->state = $form_state['values']['residency']['state'];
	$residency->country = $form_state['values']['residency']['country'];
	$residency->date_from = $form_state['values']['residency']['date_from'];
	$residency->date_to = $form_state['values']['residency']['date_to'];
	$residency->prog_dir = $form_state['values']['residency']['prog_dir'];
	
	db_insert('residency')
		->fields(array(
			'uid' => $residency->uid,
			'type' => $residency->type,
			'institution' => $residency->institution,
			'city' => $residency->city,
			'state' => $residency->state,
			'country' => $residency->country,
			'date_from' => $residency->date_from,
			'date_to' => $residency->date_to,
			'prog_dir' => $residency->prog_dir,
	))
		->execute();

/*
 * Update the drupal_flags table by setting the residency 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('drupal_flags	')
		->fields(array(
			'residency'=>1,
	))
		->condition('uid', $user->uid)
		->execute();
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/affiliations' . $user->uid);	
}	