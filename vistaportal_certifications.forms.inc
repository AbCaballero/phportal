<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the certifications section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the certifications form.
 */ 
function vistaportal_certifications_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['certifications1'] = array(
		'#type'=>'fieldset',
		'#title' => t('Certifications'),
		'#collapsible' => FALSE,
	);
	$form['certifications1']['desc'] = array(
		'#markup' => t('Board Certification'));
	$form['certifications1']['not_board_cert'] = array(
		'#type' => 'checkbox',
		'#title' => t('Not Board Certified'),
		'#required' => FALSE,
	);	
	$form['certifications1']['board_status'] = radios_board_status('Current Specialty Board Status');
	$form['certifications1']['board'] = cert('American Board of Medical Sciences');
	$form['certifications1']['cert/recert'] = status('Was this a Certification or a Recertification?');
	$form['certifications1']['specialty'] = medical_specialty('Specialty');
	$form['certifications1']['date'] = date_my('Certification/Recertification Date');
	$form['certifications1']['certnum'] = textfield('Certificate #');
	
	$form['certifications2']['additional'] = array(
		'#markup' => t('Additional Certification'),
	);
	$form['certifications2']['na'] = array(
		'#type' => 'checkbox',
		'#title' => t('Not Applicable'),
	);
	$form['certifications2']['type'] = cert('Type');
	$form['certifications2']['name'] = array(
		'#type' => 'textfield',
		'#states' => array(
			'visible'=> array(
				':input[name="type"]' => array('value' => 'Other'),
	)));
	$form['certifications2']['certnum'] = textfield('Certificate#');
	$form['certifications2']['exp_date'] = date_my('Expiration Date');
	
	$form['certification']['ecfmg'] = textfield('ECFMG CERTIFICATE');
	$form['certification']['ecfmg_exp'] = date_my('Expiration Date');
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_certifications_form_submit'),
	);

return $form;
}
/*
 * This is the form submission callback for the certifications form.
 */
			
function vistaportal_certifications_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user -> uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record

/* If the user refills this form, we need to unset the
 * certifications status flag in the vss_drupal_flags table.	
 */
	db_update('vss_drupal_flags	')
		->fields(array(
			'certifications'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the certifications table.*/
	db_delete('vss_certifications')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the certifications table.*/
	$certifications = new stdClass();
	$certifications->uid = $user->uid;
	$certifications->not_board_cert = $form_state['values']['not_board_cert'];
	$certifications->board_status = $form_state['values']['board_status'];
	$certifications->board = $form_state['values']['board'];
	$certifications->board_cert_recert = $form_state['values']['cert/recert'];
	$certifications->specialty = $form_state['values']['specialty'];
	$certifications->board_cert_date = $form_state['values']['date'];
	$certifications->board_certnum = $form_state['values']['certnum'];

	
	db_insert('vss_certifications')
		->fields(array(
			'uid' => $certifications->uid,
			'not_board_cert' => $certifications->not_board_cert,
			'board_status' => $certifications->board_status,
			'board' => $certifications->board,
			'board_cert_recert' => $certifications->board_cert_recert,
			'board_specialty' => $certifications->specialty,
			'board_cert_date' => $certifications->board_cert_date,
			'board_cert_num' => $certifications->board_cert_num,
	))
		->execute();

/*
 * Update the vss_drupal_flags table by setting the certifications 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags	')
		->fields(array(
			'certifications'=>1,
	))
		->condition('uid', $user->uid)
		->execute();			
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/licensure' . $user->uid);	
}
	