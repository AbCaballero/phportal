<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the medical school section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the medschool form.
 */
function vistaportal_medschool_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['#attributes'] = array('enctype' => array("multipart/form-data")); 
	$form['med'] = array(
		'#type'=>'fieldset',
		'#title' => t('Medical Education'),
		'#collapsible' => FALSE,
	);
	$form['med']['school'] = textfield('School');
	$form['med']['degree'] = edu('Degree Earned');
	$form['med']['city'] = textfield('City');
	$form['med']['state'] = state('State');
	$form['med']['country'] = country('Country');
	$form['med']['date_from'] = date_popup('Start Date');
	$form['med']['date_to'] = date_popup('End Date');
	$form['med']['ecfmg'] = textfield('ECFMG CERTIFICATE #');
	//$form['med']['ecfmg_valid'] = date_popup('Expiration Date');
	$form['med']['edu_counter']['#type'] = "hidden";
	$form['med']['edu_counter']['#default_value'] = -1;
	/*$form['med']['edu'] = vistaportal_set($med_fields, 
		'Add another school', 'Remove a school', 3); */
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_medschool_form_submit'),
	);	
return $form;
}

/*
 * This is the form submission callback for the medschool form.
 */
			
function vistaportal_medschool_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user -> uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record

/* If the user refills this form, we need to unset the
 * medschool status flag in the vss_drupal_flags table.	
 */
	db_update('vss_drupal_flags	')
		->fields(array(
			'medschool'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the medschool table.*/
	db_delete('vss_medschool')
		->condition('uid', $user->uid)
		->execute();		
		
/*Insert the form_state values into the medschool table.*/
	
	$medschool = new stdClass();
	$medschool->uid = $user->uid;
	$medschool->school = $form_state['values']['school'];
	$medschool->degree = $form_state['values']['degree'];
	$medschool->city = $form_state['values']['city'];
	$medschool->state = $form_state['values']['state'];
	$medschool->country = $form_state['values']['country'];
	$medschool->date_from = $form_state['values']['date_from'];
	$medschool->date_to = $form_state['values']['date_to'];
	$medschool->ecfmg = $form_state['values']['ecfmg'];
	
	db_insert('vss_medschool')
		->fields(array(
			'uid' => $medschool->uid,
			'school' => $medschool->school,
			'degree' => $medschool->degree,
			'city' => $medschool->city,
			'state' => $medschool->state,
			'country' => $medschool->country,
			'date_from' => $medschool->date_from,
			'date_to' => $medschool->date_to,
	))
		->execute();
		
/*
 * Update the vss_drupal_flags table by setting the medschool 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags	')
		->fields(array(
			'medschool'=>1,
	))
		->condition('uid', $user->uid)
		->execute();			

	$user = user_load($form_state['uid']);
	drupal_goto('preapp/internship' . $user->uid);

/*
 * @TODO add error checking
 */		
}		
