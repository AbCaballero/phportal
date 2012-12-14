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
function vistaportal_internship_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['#attributes'] = array('enctype' => array("multipart/form-data"));
	$form['internship'] = fieldset('Internship');
	$form['internship']['type'] = textfield('Type');
	$form['internship']['institution'] = textfield('Institution');
	$form['internship']['city'] = textfield('City');
	$form['internship']['state'] = state('State');
	$form['internship']['country'] = country('Country');
	$form['internship']['date_from'] = date_popup('Start Date');
	$form['internship']['date_to'] = date_popup('End Date');
	$form['internship']['prog_dir'] = textfield('Program Director');
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_internship_form_submit'),
	);
return $form;
}

/*
 * This is the form submission callback for the internship form.
 */
			
function vistaportal_internship_form_submit($form, &$form_state){
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
	db_update('vss_drupal_flags')
		->fields(array(
			'internship'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the internship table.*/
	db_delete('vss_internship')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the internship table.*/
/*The ['internship'] index should fail here, but fails without it*/
	$internship = new stdClass();
	$internship->uid = $user->uid;
	$internship->type = $form_state['values']['internship']['type'];
	$internship->institution = $form_state['values']['internship']['institution'];
	$internship->city = $form_state['values']['internship']['city'];
	$internship->state = $form_state['values']['internship']['state'];
	$internship->country = $form_state['values']['internship']['country'];
	$internship->date_from = $form_state['values']['internship']['date_from'];
	$internship->date_to = $form_state['values']['internship']['date_to'];
	$internship->prog_dir = $form_state['values']['internship']['prog_dir'];
	
	db_insert('vss_internship')
		->fields(array(
			'uid' => $internship->uid,
			'type' => $internship->type,
			'institution' => $internship->institution,
			'city' => $internship->city,
			'state' => $internship->state,
			'country' => $internship->country,
			'date_from' => $internship->date_from,
			'date_to' => $internship->date_to,
			'prog_dir' => $internship->prog_dir,
	))
		->execute();

/*
 * Update the vss_drupal_flags table by setting the internship 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags	')
		->fields(array(
			'internship'=>1,
	))
		->condition('uid', $user->uid)
		->execute();
			
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/residency' . $user->uid);	
}	