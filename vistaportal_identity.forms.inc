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

  global $user;

  //Get the user profile data to pre-populate the application
  $query = db_select('vss_profile_data', 'pd')
  ->condition('pd.uid', $user->uid, '=')
  ->fields('pd', array('first_name', 'last_name', 'email', 'phone'));
  $profiledata = $query->execute();

  //initialize the candidate profile array
    $candprofile['firstname'] = " ";
    $candprofile['lastname'] = " ";
    $candprofile['email'] = " ";
    $candprofile['phone'] = " ";

  foreach ($profiledata as $profilevalues) {
    $candprofile['firstname'] = $profilevalues->first_name;
    $candprofile['lastname'] = $profilevalues->last_name;
    $candprofile['email'] = $profilevalues->email;
    $candprofile['phone'] = $profilevalues->phone;
  }

	$form = array();
	$form['#attributes'] = array('enctype' => array('multipart/form-data'));
	//Identifying information
	$form['identity'] = array(
		'#type' => 'fieldset',
		'#title' => t('PERSONAL INFORMATION'),
		'#collapsible' => FALSE,
	);	
	//$form['identity']['lname'] = textfield('Last Name', 15);
	$form['identity']['lname'] = array(
	'#prefix' => '<div class="lname">',
		'#type' => 'textfield',
		'#title' => t('Last Name'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
              '#maxlength' => 40,
		);
	$form['identity']['fname'] = array(
	'#prefix' => '<div class="fname">',
		'#type' => 'textfield',
		'#title' => t('First Name'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
              '#maxlength' => 15,
              '#default_value' => $candprofile['firstname'],
		);
	$form['identity']['initial'] = array(
	'#prefix' => '<div class="initial">',
		'#type' => 'textfield',
		'#title' => t('MI'),
		'#required' => FALSE,
		'#attributes' => array('class' => array('percent_95')),
		'#suffix' => '</div>',
              '#maxlength' => 15,
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
		'#type' => 'textfield',
		'#title' => t(''),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90 textfield-phone')),
		'#suffix' => '</div>',
              '#maxlength' => 20,
              '#default_value' => $candprofile['phone'],
		);
	$form['identity']['email'] = array(
	'#prefix' => '<div class="email">',
		'#type' => 'textfield',
		'#title' => t('E-mail address'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_100')),
		'#suffix' => '</div>',
              '#maxlength' => 60,
              '#default_value' => $candprofile['email'],
		);
	$form['identity']['home_address'] = array(
	'#prefix' => '<div class="home-address">',
		'#type' => 'textfield',
		'#title' => t('Home address'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_100')),
		'#suffix' => '</div>',
              '#maxlength' => 40,
		);
	$form['identity']['city'] = array(
	'#prefix' => '<div class="city">',
		'#type' => 'textfield',
		'#title' => t('City'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_95')),
		'#suffix' => '</div>',
              '#maxlength' => 20,
		);
	$form['identity']['home_state'] = state('State');
	$form['identity']['zip'] = array(
	'#prefix' => '<div class="zipcode">',
		'#type' => 'textfield',
		'#title' => t('Zipcode'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_95 textfield-postal')),
		'#suffix' => '</div>',
              '#maxlength' => 10,
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
		'#type' => 'textfield',
		'#title' => t('City'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('edu-city')),
		'#suffix' => '</div>',
              '#maxlength' => 20,
		);
	//$form['identity']['social_security'] = textfield('Social Security Number', 13);
	//$form['identity']['social_security']['#maxlength'] = 11;
	//$form['identity']['npi'] = textfield('National Physician Identifier');
	$form['identity']['ver_label'] = array(
	'#prefix' => '<div class="var_label_iden">',
		'#markup' => t('Can you provide proof of legal eligibility to work in the USA?'), 
		'#required' => TRUE,
		'#suffix' => '</div>',
	);
	$form['identity']['verification'] = radios_yesno('');
	$form['identity']['verification']['#prefix'] = '<div class = "p-r-yn">';
  $form['identity']['verification']['#suffix'] = '</div>';
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
		'#type' => 'textfield',
		'#title' => t('Spouse Name'),
		'#required' => TRUE,
		'#attributes' => array('class' => array('percent_90')),
		'#suffix' => '</div>',
              '#maxlength' => 39, 
		);
	$form['identity']['spouse']['#required'] = FALSE;
	$form['identity']['number_of_children'] = array(
	'#prefix' => '<div class="n-children">',
		'#type' => 'textfield',
		'#title' => t('# of children'),
		'#required' => FALSE,
		'#attributes' => array('class' => array('percent_97 textfield-license')),
		'#suffix' => '</div>',
              '#maxlength' => 3, 
		);
	/*$form['identity']['comment'] = array(
	'#prefix' => '<div class="comment">',
		'#type' => 'textarea',
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
		'#value' => t('Submit'),
		'#name' => 'next',
		'#submit' => array('vistaportal_identity_form_submit'),
		'#attributes' => array('class' => array('identity-submit')),
		);
		
		$form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button')),
      '#submit' => array('vistaportal_next'),
    );
		$form['next']['#attributes'] = array('class' => array('next'));
		
      $form['save_logout'] = array(
             '#type' => 'submit',
      	      '#value' => t('Save & Logout'),
      	      '#limit_validation_errors' => array(),
             '#attributes' => array('class' => array('button')),
             '#submit' => array('vistaportal_save_logout'),
             );

    $form['prev'] = array(
            '#type' => 'submit',
            '#value' => t('Previous'),
            '#limit_validation_errors' => array(),
            '#attributes' => array('class' => array('button prev')),
            '#submit' => array('vistaportal_identity_form_previous'),
            );
    $form['prev']['#attributes'] = array('class' => array('prev'));
	

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
	$identity->state = $form_state['values']['home_state'];
	$identity->zip = $form_state['values']['zip'];
	$identity->phone_choice = $form_state['values']['phone_choice'];
	$identity->phone = $form_state['values']['phone'];
	$identity->email = $form_state['values']['email'];
	$identity->dob = $form_state['values']['dob'];
	$identity->birth_country = $form_state['values']['birth_country'];
	$identity->birth_state = $form_state['values']['birth_state'];
	$identity->birth_city = $form_state['values']['birth_city'];
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
	drupal_goto('preapp/education' . $user->uid);

/*
 * @TODO add error checking
 */		
}


  function vistaportal_identity_form_logout($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('user/logout' . $user -> uid);
  }

  function vistaportal_identity_form_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('home' . $user -> uid);
  }
	
	/*
   * Go to the next page
   */
  function vistaportal_next($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/education' . $user -> uid);
  }	
	