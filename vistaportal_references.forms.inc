<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the references section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the references form.
 */ 
function vistaportal_references_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['references'] = fieldset('References');
	/*$ref_fields['name'] = textfield('Name');
	$ref_fields['Association'] = textfield('Association');
	$ref_fields['Specialty'] = textfield('Specialty');
	$ref_fields['home_phone'] = phone('Home Phone');
	$ref_fields['work_phone'] = phone('Work Phone');*/
	$form['references']['name'] = textfield('Name');
	$form['references']['association'] = textfield('Association');
	$form['references']['specialty'] = textfield('Specialty');
	$form['references']['home_phone'] = phone('Home Phone');
	$form['references']['work_phone'] = phone('Work Phone');
	
	$terms_desc = '<p>I certify that the information on this application is true to the best of my 
		knowledge. I authorize all persons and institutions to disclose to and share with HCP
		opinions and information regarding me, including but not limited to, information contained in 
		this application and my skills, experience, fitness to practice medicine, character, work habits, 
		and performance. I authorize HCP to release information contained in this application or obtained 
		by HCP pursuant to the authorization contained in this paragraph to HCP’s insurance companies 
		and medical facility clients. I waive any claims I might otherwise have against HCP resulting 
		from HCP obtaining or releasing information as authorized by this paragraph.</p>';
	
	//$form['references']['application_terms'] = terms_1($terms_desc);
	//$form['references']['application_terms']['#attributes']['class'] .= 
	//	'edit-references-application-terms required';
	$form['references']['application_terms']['#title'] = 'I Accept Terms';
	$form['references']['application_terms']['#rules'] = array( 
		array('rule' => 'chars[1]', 'error' => 'You must accept the Terms to continue.'));
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_references_form_submit'),
	);		

return $form;
}

/*
 * This is the form submission callback for the references form.
 */
			
function vistaportal_references_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user->uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record

/*
 * If the user refills this form, we need to unset the
 * references status flag in the vss_drupal_flags table.	
 */
	db_update('vss_drupal_flags')
		->fields(array(
			'ref'=>0,
	))
		->condition('uid', $user->uid)
		->execute();
		 
/*Overwrite any existing values in the references table.*/
	db_delete('vss_ref')
		->condition('uid', $user->uid)
		->execute();
		
/*Insert the form_state values into the references table.*/		
  $references = new stdClass();
	$references->uid = $user->uid;
	$references->name = $form_state['values']['references']['name'];
	$references->association = $form_state['values']['references']['association'];
	$references->specialty = $form_state['values']['references']['specialty'];
	$references->home_phone = $form_state['values']['references']['home_phone'];
	$references->work_phone = $form_state['values']['references']['work_phone'];
	
  db_insert('vss_ref')
		->fields(array(
			'uid' => $references->uid, 
			'name' => $references->name, 
			'association'=> $references->association, 
			'specialty'=> $references->specialty, 
			'home_phone'=> $references->home_phone, 
  		'work_phone'=> $references->work_phone))
		->execute();

/*
 * Insert the user_id into the vss_drupal_flags table and set the references bit,
 * letting us know that the form has been filled out.
 */		
		db_insert('vss_drupal_flags')
		->fields(array(
			'uid'=>$user->uid,
			'ref' => 1,
		))
		->execute();								
	$user = user_load($form_state['uid']);
	drupal_goto('release' . $user->uid);	
}		