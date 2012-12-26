<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the identity section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the identity form.
 */ 
function vistaportal_identity_form($form, &$form_state){
	include_once('vistaportal.fields.inc');	
	$form = array();
	$form['#attributes'] = array('enctype' => array('multipart/form-data'));
	//Identifying information
	$form['identity'] = array(
		'#type' => 'fieldset',
		'#title' => t('Identifying Information'),
		'#collapsible' => FALSE,
	);	
	$form['identity']['lname'] = textfield('Last Name', 15);
	$form['identity']['fname'] = textfield('First Name', 15);
	$form['identity']['initial'] = textfield('Middle', 15);
	$form['identity']['phone_choice'] = phone_choice('Phone');
	$form['identity']['phone'] = phone('');
	$form['identity']['email'] = email('E-mail address');
	$form['identity']['home_address'] = textfield('Home Address', 40);
	$form['identity']['city'] = textfield('City', 20);
	$form['identity']['state'] = state('State');
	$form['identity']['zip'] = zip('Zip Code');
	$form['identity']['dob'] = date_mdy('Date of Birth');
	$form['identity']['birth_country'] = country('Country of Birth');
	$form['identity']['birth_state'] = state('State of Birth');
	$form['identity']['birth_state_other'] = array(
		'#type' => 'textfield',
		'#states' => array(
			'visible'=> array(
				':input[name="birth_state"]' => array('value' => 'Other'),
	)));
	$form['identity']['birth_city'] = textfield('City of Birth');
	//$form['identity']['social_security'] = textfield('Social Security Number', 13);
	//$form['identity']['social_security']['#maxlength'] = 11;
	$form['identity']['npi'] = textfield('National Physician Identifier');
	$form['identity']['verification'] = radios_yesno('Can you provide proof of 
		legal eligibility to work in the USA?');
	$form['identity']['marital_status'] = marital_status('Marital Status');
	$form['identity']['marital_status']['#required'] = FALSE;
	$form['identity']['spouse'] = textfield("Spouse's Name");
	$form['identity']['spouse']['#required'] = FALSE;
	$form['identity']['number_of_children'] = children('# of Children:');
	$form['identity']['number_of_children']['#required'] = FALSE;
	$form['prev'] = button('<Previous');
	$form['save_logout'] = button('Save & Logout');	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Next>'),
		'#name' => 'next',
		'#submit' => array('vistaportal_identity_form_submit'),
		);

return $form;
	
}

/*
 * This is the form submission callback for the identity form.
 */ 
			
function vistaportal_identity_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user -> uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record
/*
 * If the user refills this form, we need to unset the
 * identity status flag in the vss_drupal_flags table.	
 */
	db_update('vss_drupal_flags')
		->fields(array(
			'identity'=>0,
	))
		->condition('uid', $user->uid)
		->execute();
		 
/*Overwrite any existing values in the identity table.*/
	db_delete('vss_identity')
		->condition('uid', $user->uid)
		->execute();
		
/*Insert the form_state values into the identity table.*/		
  $form_state['values']['dob'] = date('Y-m-d H:i:s', strtotime($form_state['values']['dob']));
  $identity = new stdClass();
	$identity->uid = $user->uid;
	$identity->last_name = $form_state['values']['lname'];
	$identity->first_name = $form_state['values']['fname'];
	$identity->middle_init = $form_state['values']['initial'];
	$identity->address = $form_state['values']['home_address'];
	$identity->city = $form_state['values']['city'];
	$identity->state = $form_state['values']['state'];
	$identity->zip = $form_state['values']['zip'];
	$identity->phone_choice = $form_state['values']['phone_choice'];
	$identity->phone = $form_state['values']['phone'];
	$identity->email = $form_state['values']['email'];
	$identity->dob = $form_state['values']['dob'];
	$identity->birth_country = $form_state['values']['birth_country'];
	$identity->birth_state = $form_state['values']['birth_state'];
	$identity->birth_city = $form_state['values']['birth_city'];
	$identity->npi = $form_state['values']['npi'];
	$identity->verification = $form_state['values']['verification'];
	$identity->marital_status = $form_state['values']['marital_status'];
	$identity->spouse = $form_state['values']['spouse'];
	$identity->number_children = $form_state['values']['number_of_children'];
  
  db_insert('vss_identity')
		->fields(array(
			'uid' => $identity->uid, 
			'last_name' => $identity->last_name, 
			'first_name'=> $identity->first_name, 
			'middle_init'=> $identity->middle_init, 
			'address'=> $identity->address, 
  		'city'=> $identity->city, 
  		'state'=> $identity->state, 
  		'zip'=> $identity->zip,
  		'phone_choice'=> $identity->phone_choice,
  		'phone'=> $identity->phone,  
  		'email'=>$identity->email,  
  		'dob'=> $identity->dob,
  		'birth_city'=> $identity->birth_city,
  		'birth_state'=> $identity->birth_state, 
  		'birth_country'=> $identity->birth_country,
  		'npi'=> $identity->npi,
  		'verification'=> $identity->verification,  
  		'marital_status'=> $identity->marital_status,
  		'spouse'=> $identity->spouse, 
  		'number_children'=> $identity->number_children))
		->execute();

/*
 * Insert the user_id into the vss_drupal_flags table and set the identity bit,
 * letting us know that the form has been filled out.
 */		
		db_insert('vss_drupal_flags')
		->fields(array(
			'uid'=>$user->uid,
			'identity' => 1,
		))
		->execute();		
	$user = user_load($form_state['uid']);	
	drupal_goto('preapp/premed' . $user->uid);

/*
 * @TODO add error checking
 */		
}
