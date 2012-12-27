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
	$form['residency1'] = fieldset('');
	$form['residency1']['na'] = array(
		'#type'=> 'checkbox',
		'#title' => t('Not Applicable'),
		'#required' => FALSE,
	);
	$form['residency1']['type'] = textfield('Type');
	$form['residency1']['institution'] = textfield('Institution');
	$form['residency1']['country'] = country('Country');
	$form['residency1']['state'] = state('State');
	$form['residency1']['state_other'] = array(
		'#type' => 'textfield',
		'#states' => array(
			'visible'=> array(
				':input[name="residency1[state]"]' => array('value' => 'Other'),
	)));			
	$form['residency1']['city'] = textfield('City');
	$form['residency1']['date_from'] = date_my('Start Date');
	$form['residency1']['date_to'] = date_my('End Date');
	$form['residency1']['prog_dir'] = textfield('Program Director');
	
	$form['residency2'] = fieldset('');	
	
	$form['residency2']['desc'] =array(
		'#markup'=> t('ADDITIONAL RESIDENCY OR FELLOWSHIP OR OTHER GRADUATE EDUCATION'),
	);
	$form['residency2']['na'] = array(
		'#type'=> 'checkbox',
		'#title' => t('Not Applicable'),
		'#required' => FALSE,
	);
  $form['residency2']['type'] = textfield('Type');
  $form['residency2']['institution'] = textfield('Institution');
	$form['residency2']['country'] = country('Country');
	$form['residency2']['state'] = state('State');
	$form['residency2']['state_other'] = array(
		'#type' => 'textfield',
		'#states' => array(
			'visible'=> array(
				':input[name="residency2[state]"]' => array('value' => 'Other'),
	)));
  $form['residency2']['city'] = textfield('City');
  $form['residency2']['date_from'] = date_my('From');
  $form['residency2']['date_to'] = date_my('To');
  $form['residency2']['prog_dir'] = textfield('Program Director');
	$form['<prev'] = button('Previous');
  $form['save_logout'] = button('Save & Logout');	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Next>'),
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
 * residency status flag in the vss_drupal_flags table.	
 */
	db_update('vss_drupal_flags	')
		->fields(array(
			'residency'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the residency table.*/
	db_delete('vss_residency')
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
	
	db_insert('vss_residency')
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
 * Update the vss_drupal_flags table by setting the residency 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags	')
		->fields(array(
			'residency'=>1,
	))
		->condition('uid', $user->uid)
		->execute();
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/affiliations' . $user->uid);	
}	