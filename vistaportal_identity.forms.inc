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
		'#title' => t('PERSONAL INFORMATION'),
		'#collapsible' => FALSE,
	);	
	//$form['identity']['lname'] = textfield('Last Name', 15);
	$form['identity']['lename'] = array(
	'#prefix' => '<div class="lname">',
		'#type' => textfield,
		'#title' => t('Last Name'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
		);
	$form['identity']['fname'] = array(
	'#prefix' => '<div class="fname">',
		'#type' => textfield,
		'#title' => t('Fisrt Name'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
		);
	$form['identity']['initial'] = array(
	'#prefix' => '<div class="initial">',
		'#type' => textfield,
		'#title' => t('MI'),
		'#required' => FALSE,
		'#attributes' => array('class' => array('percent_95')),
		'#suffix' => '</div>',
		);
	$form['identity']['phone_choice'] = array(
	'#prefix' => '<div class="phone_choice">',
		'#type' => 'select',
		'#title' => t('Phone'),
		'#options' => drupal_map_assoc(array('-Select-','Home', 'Cell', 'Work')),
		'#required' => FALSE,
		'#attributes' => array('class' => array('percent_95')),
		'#suffix' => '</div>',
		);
	$form['identity']['phone'] = array(
	'#prefix' => '<div class="phone_number">',
		'#type' => textfield,
		'#title' => t(''),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
		);
	$form['identity']['email'] = array(
	'#prefix' => '<div class="email">',
		'#type' => textfield,
		'#title' => t('E-mail address'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_100')),
		'#suffix' => '</div>',
		);
	$form['identity']['home_address'] = array(
	'#prefix' => '<div class="home-address">',
		'#type' => textfield,
		'#title' => t('Home address'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_100')),
		'#suffix' => '</div>',
		);
	$form['identity']['city'] = array(
	'#prefix' => '<div class="city">',
		'#type' => 'textfield',
		'#title' => t('City'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_95')),
		'#suffix' => '</div>',
		);
	$form['identity']['home_state'] = state('State');
	$form['identity']['zip'] = array(
	'#prefix' => '<div class="zipcode">',
		'#type' => textfield,
		'#title' => t('Zipcode'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_95')),
		'#suffix' => '</div>',
		);
	$form['identity']['dob'] = date_mdy('Date of Birth');
	$form['identity']['birth_country'] = country('Country');
	$form['identity']['birth_state'] = state('State');
	$form['identity']['birth_state_other'] = array(
		'#type' => 'textfield',
		'#states' => array(
			'visible'=> array(
				':input[name="birth_state"]' => array('value' => 'Other'),
	)));
	$form['identity']['birth_city'] = array(
	'#prefix' => '<div class="birth-city">',
		'#type' => textfield,
		'#title' => t('City'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('edu-city')),
		'#suffix' => '</div>',
		);
	//$form['identity']['social_security'] = textfield('Social Security Number', 13);
	//$form['identity']['social_security']['#maxlength'] = 11;
	//$form['identity']['npi'] = textfield('National Physician Identifier');
	$form['identity']['ver_label'] = array(
	'#prefix' => '<div class="var_label">',
		'#markup' => t('Can you provide proof of legal eligibility to work in the USA?'), 
		'#required' => TRUE,
		'#suffix' => '</div>',
	);
	$form['identity']['verification'] = radios_yesno();
	$form['identity']['marital_status'] = array(
	'#prefix' => '<div class="marital-status">',
		'#type' => 'select',
		'#title' => t('Marital Status'),
		'#options' => drupal_map_assoc(array('-Select-','Single', 'Married', 'Divorced', 'Widowed')),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
		);
	$form['identity']['marital_status']['#required'] = FALSE;
	$form['identity']['spouse'] = array(
	'#prefix' => '<div class="spouse">',
		'#type' => textfield,
		'#title' => t('Spouse Name'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
		);
	$form['identity']['spouse']['#required'] = FALSE;
	$form['identity']['number_of_children'] = array(
	'#prefix' => '<div class="n-children">',
		'#type' => textfield,
		'#title' => t('# of children'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_97')),
		'#suffix' => '</div>',
		);
	$form['identity']['number_of_children']['#required'] = FALSE;
	/*$form['identity']['comment'] = array(
	'#prefix' => '<div class="comment">',
		'#type' => textarea,
		'#title' => t('Comment Examples'),
		'#required' => FALSE,
		'#attributes' => array('class' => array('percent_95')),
		'#suffix' => '</div>',
		);*/
		$form['identity']['line2'] = array(
	  '#prefix' => '<div class="line_left">',
		//'#markup' => '<hr>',
		//'#attributes' => array('class' => array('line_left')),
		'#suffix' => '</div>',
		);
			
	$form['identity']['required_field'] = array(
	'#prefix' => '<div class="required_field">',
		'#markup' => 'Required Field',
		'#required' => TRUE,
		'#attributes' => array('class' => array('required_field')),
		'#suffix' => '</div>',
		);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Next'),
		'#name' => 'next',
		'#submit' => array('vistaportal_identity_form_submit'),
		'#attributes' => array('class' => array('identity-submit')),
		);
	$form['save_logout'] = button('Save & Logout');	
	//$form['save_logout']['#attributes'] = array('id' => array('identity-save'));
	$form['save_logout']['#attributes'] = array('class' => array('edit-save-logout button previous'));
	$form['prev'] = button('Previous');
	//$form['prev']['#attributes'] = array('id' => array('identity-prev'));
	$form['prev']['#attributes'] = array('class' => array('edit-prev button previous identity-prev'));
	
	

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
