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
	$form['certifications'] = array(
		'#type'=>'fieldset',
		'#title' => t('Certifications'),
		'#collapsible' => FALSE,
	);
	$form['certifications']['board_status'] = radios_board_status('Current Specialty Board Status');
	$form['certifications']['board'] = textfield('American Board of:');
	$form['certifications']['date'] = date_popup('Certification/Recertification Date');
	$form['certifications']['other'] = textfield('Other Current ABMS/Subspecialty Certification');
	$form['certifications']['bcls'] = checkbox('BCLS');
	//$form['certifications']['bcls']['exp'] = date_popup('Expiration Date');
	$form['certifications']['acls'] = checkbox('ACLS');
	//$form['certifications']['acls']['exp'] = date_popup('Expiration Date');
	$form['certifications']['atls'] = checkbox('ATLS');
	//$form['certifications']['atls']['exp'] = date_popup('Expiration Date');
	$form['certifications']['pals'] = checkbox('PALS');
	//$form['certifications']['pals']['exp'] = date_popup('Expiration Date');
	$form['certifications']['nrp'] = checkbox('NRP/NALS');
	//$form['certifications']['nrp']['exp'] = date_popup('Expiration Date');
	$form['certifications']['also'] = checkbox('ALSO');
	//$form['certifications']['also']['exp'] = date_popup('Expiration Date');
	$form['certifications']['mqsa'] = checkbox('MQSA');
	//$form['certifications']['mqsa']['exp'] = date_popup('Expiration Date');
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
 * certifications status flag in the drupal_flags table.	
 */
	db_update('drupal_flags	')
		->fields(array(
			'certifications'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the certifications table.*/
	db_delete('certifications')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the certifications table.*/
	$certifications = new stdClass();
	$certifications->uid = $user->uid;
	$certifications->board_status = $form_state['values']['board_status'];
	$certifications->board = $form_state['values']['board'];
	$certifications->board_cert_date = $form_state['values']['date'];
	$certifications->other = $form_state['values']['other'];
	$certifications->bcls = $form_state['values']['bcls'];
	$certifications->bcls_exp_date = $form_state['values']['bcls_exp'];
	$certifications->acls = $form_state['values']['acls'];
	$certifications->acls_exp_date = $form_state['values']['acls_exp'];
	$certifications->atls = $form_state['values']['atls'];
	$certifications->atls_exp_date = $form_state['values']['atls_exp'];
	$certifications->pals = $form_state['values']['pals'];
	$certifications->pals_exp_date = $form_state['values']['pals_exp'];
	$certifications->nrp = $form_state['values']['nrp'];
	$certifications->nrp_exp_date = $form_state['values']['nrp_exp'];
	$certifications->also = $form_state['values']['also'];
	$certifications->also_exp_date = $form_state['values']['also_exp'];
	$certifications->mqsa = $form_state['values']['mqsa'];
	$certifications->mqsa_exp_date = $form_state['values']['mqsa_exp'];
	
	db_insert('certifications')
		->fields(array(
			'uid' => $certifications->uid,
			'board_status' => $certifications->board_status,
			'board' => $certifications->board,
			'board_cert_date' => $certifications->board_cert_date,
			'other' => $certifications->other,
			'bcls' => $certifications->bcls,
			'bcls_exp_date' => $certifications->bcls_exp_date,
			'acls' => $certifications->acls,
			'acls_exp_date' => $certifications->acls_exp_date,
			'atls' => $certifications->atls,
			'atls_exp_date' => $certifications->atls_exp_date,
			'pals' => $certifications->pals,
			'pals_exp_date' => $certifications->pals_exp_date,
			'nrp' => $certifications->nrp,
			'nrp_exp_date' => $certifications->nrp_exp_date,
			'also' => $certifications->also,
			'also_exp_date' => $certifications->also_exp_date,
			'mqsa' => $certifications->mqsa,
			'mqsa_exp_date' => $certifications->mqsa_exp_date,
	))
		->execute();

/*
 * Update the drupal_flags table by setting the certifications 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('drupal_flags	')
		->fields(array(
			'certifications'=>1,
	))
		->condition('uid', $user->uid)
		->execute();			
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/licensure' . $user->uid);	
}
	