<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the licensure section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the licensure form.
 */  
function vistaportal_licensure_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['licensure'] = array(
		'#type'=>'fieldset',
		'#title' => t('Licensure'),
		'#collapsible' => FALSE,
	);
	$form['licensure']['exam'] = textfield('What was your original licensing exam?');
	$form['licensure']['exam_steps'] = textfield('Number of times taken each step');
	$form['licensure']['exam_date'] = date_popup('Exam dates each step');
	$form['licensure']['exam_state'] = state('State in which you took your exam');
	$form['licensure']['fcvs'] = textfield('Federation Credentials Verification Profile Number');
	$form['licensure']['state'] = state('State');
	$form['licensure']['number'] = textfield('Number');
	$form['licensure']['date_issued'] = date_popup('Date Issued');
	$form['licensure']['date_expired']= date_popup('Expiration Date');
	$form['licensure']['cs_number'] = textfield('State C/S #');
	$form['licensure']['active_inactive'] = radios_active_inactive_status('Is this licence active or inactive?');
	$form['licensure']['dea_num'] = textfield('DEA Registration Number');
	$form['licensure']['dea_date_issued'] = date_popup('Date Issued');
	$form['licensure']['dea_date_expired'] = date_popup('Expiration Date');
	$form['licensure']['orig_lic_state'] = state('In which state did you obtain your original licence?');
	$form['licensure']['other_dea'] = textfield('Other active Federal DEA REgistration Numbers');
	$form['licensure']['other_prof'] = textfield('Other professional licences held');
	$form['licensure']['language_spoken'] = textfield('In addition to English, other languages spoken 
		with communication ease or fluency');
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_licensure_form_submit'),
	);	

return $form;
}

/*
 * This is the form submission callback for the licensure form.
 */
			
function vistaportal_licensure_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user -> uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record
	
	/* If the user refills this form, we need to unset the
 * licensure status flag in the drupal_flags table.	
 */
	db_update('drupal_flags	')
		->fields(array(
			'licensure'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the licensure table.*/
	db_delete('licensure')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the licensure table.*/
	$licensure = new stdClass();
	$licensure->uid = $user->uid;
	$licensure->exam_steps = $form_state['values']['exam_steps'];
	$licensure->exam_date = $form_state['values']['exam_date'];
	$licensure->exam_state = $form_state['values']['exam_state'];
	$licensure->fcvs = $form_state['values']['fcvs'];
	$licensure->state = $form_state['values']['state'];
	$licensure->number = $form_state['values']['number'];
	$licensure->date_issued = $form_state['values']['date_issued'];
	$licensure->date_expired = $form_state['values']['date_expired'];
	$licensure->cs_number = $form_state['values']['cs_number'];
	$licensure->active_inactive = $form_state['values']['active_inactive'];
	$licensure->dea_num = $form_state['values']['dea_num'];
	$licensure->dea_date_issued = $form_state['values']['dea_date_issued'];
	$licensure->dea_date_expired = $form_state['values']['dea_date_expired'];
	$licensure->orig_lic_state = $form_state['values']['orig_lic_state'];
	$licensure->other_dea = $form_state['values']['other_dea'];
	$licensure->other_proof = $form_state['values']['other_prof'];
	$licensure->language_spoken = $form_state['values']['language_spoken'];
	
	db_insert('licensure')
		->fields(array(
	'uid' => $licensure->uid,
	'exam_steps' => $licensure->exam_steps, 
	'exam_date' => $licensure->exam_date, 
	'exam_state' => $licensure->exam_state ,
	'fcvs' => $licensure->fcvs, 
	'state' => $licensure->state, 
	'number' => $licensure->number, 
	'date_issued' => $licensure->date_issued, 
	'date_expired' => $licensure->date_expired, 
	'cs_number' => $licensure->cs_number, 
	'active_inactive' => $licensure->active_inactive, 
	'dea_num' => $licensure->dea_num, 
	'dea_date_issued' => $licensure->dea_date_issued, 
	'dea_date_expired' => $licensure->dea_date_expired, 
	'orig_licence_state' => $licensure->orig_lic_state, 
	'other_dea' => $licensure->other_dea, 
	'other_proof' => $licensure->other_proof, 
	'language_spoken' => $licensure->language_spoken, 
	))
		->execute();

/*
 * Update the drupal_flags table by setting the licensure 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('drupal_flags')
		->fields(array(
			'licensure'=>1,
	))
		->condition('uid', $user->uid)
		->execute();			
	
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/disciplinary' . $user->uid);	
}			