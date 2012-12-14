<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the education section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the premed form.
 */  
function vistaportal_premed_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');
	drupal_add_library('system', 'drupal.ajax');
  drupal_add_library('system', 'jquery.form');
	//Set this to tree so we can access all dynamic form values
	$form['#tree'] = TRUE;
	$form['#attributes'] = array('enctype' => array("multipart/form-data"));

	//This is the pre-med education form	
	$form['premed'] = array(
		'#type'=>'fieldset',
		'#title' => t('PRE-MEDICAL EDUCATION (OPTIONAL)'),
		'#collapsible' => FALSE,
		'#prefix' => '<div id="premed-fieldset-wrapper">',
		'#suffix' => '</div>',
	);
	
	//This counter will be used to determine how many education sections to add
	if(empty($form_state['num_schools'])){
		$form_state['num_schools'] = 1;
	}

	for($i = 0; $i < $form_state['num_schools']; $i++){
		$form['premed'][$i]['school'] = textfield('School of Graduation');
		$form['premed'][$i]['city'] = textfield('City');
		$form['premed'][$i]['state'] = state('State');
		$form['premed'][$i]['country'] = country('Country');
		$form['premed'][$i]['month_from'] = month('Month From');
		$form['premed'][$i]['year_from'] = year('Year From');
		$form['premed'][$i]['month_to'] = month('Month To');
		$form['premed'][$i]['year_to'] = year('Year To');
		$form['premed'][$i]['degree'] = edu('Degree');
	}
	
	//Only allow 3 schools for the premed form
	if($form_state['num_schools'] < 3 ){
		$form['premed']['add_another'] = array(
   		'#type' => 'submit',
   		'#value' => t('Add another school'),
   		'#submit' => array('vistaportal_form_add'),
   		'#limit_validation_errors' => array(),
   		'#ajax' => array(
     		'callback' => 'vistaportal_premed_form_add_school_callback',
     		'wrapper' => 'premed-fieldset-wrapper',
     		'method' => 'replaceWith',
     		'speed' => 'fast',
			),
  	);
	}
	
	//First school is mandatory
	if($form_state['num_schools'] > 1 ){
		$form['premed']['remove_school'] = array(
		  '#type' => 'submit',
   		'#value' => t('Remove a school'),
   		'#submit' => array('vistaportal_form_remove'),
   		'#limit_validation_errors' => array(),
   		'#ajax' => array(
     		'callback' => 'vistaportal_premed_form_add_school_callback',
     		'wrapper' => 'premed-fieldset-wrapper',
   		),
  	);
	}

//This is the medical school form	
	$form['med'] = array(
		'#type'=>'fieldset',
		'#title' => t('MEDICAL EDUCATION'),
		'#collapsible' => FALSE,
		'#prefix' => '<div id="med-fieldset-wrapper">',
		'#suffix' => '</div>',
	);
	
	//This counter will be used to determine how many education sections to add
	if(empty($form_state['num_schools'])){
		$form_state['num_schools'] = 1;
	}
	
	for($i = 0; $i < $form_state['num_schools']; $i++){
		$form['med'][$i]['school'] = textfield('School of Graduation');
		$form['med'][$i]['city'] = textfield('City');
		$form['med'][$i]['state'] = state('State');
		$form['med'][$i]['country'] = country('Country');
		$form['med'][$i]['month_from'] = month('Month From');
		$form['med'][$i]['year_from'] = year('Year From');
		$form['med'][$i]['month_to'] = month('Month To');
		$form['med'][$i]['year_to'] = year('Year To');
		$form['med'][$i]['degree'] = edu('Degree');
		$form['med']['ecfmg'] = textfield('ECFMG CERTIFICATE #');
	}
	
	//Only allow 3 schools for the med form
	if($form_state['num_schools'] < 3 ){
		$form['med']['add_another'] = array(
   		'#type' => 'submit',
   		'#value' => t('Add another school'),
   		'#submit' => array('vistaportal_form_add'),
   		'#limit_validation_errors' => array(),
   		'#ajax' => array(
     		'callback' => 'vistaportal_med_form_add_school_callback',
     		'wrapper' => 'med-fieldset-wrapper',
     		'method' => 'replaceWith',
			),
  	);
	}
	
	//First school is mandatory
	if($form_state['num_schools'] > 1 ){
		$form['med']['remove_school'] = array(
		  '#type' => 'submit',
   		'#value' => t('Remove a school'),
   		'#submit' => array('vistaportal_form_remove'),
   		'#limit_validation_errors' => array(),
   		'#ajax' => array(
     		'callback' => 'vistaportal_med_form_add_school_callback',
     		'wrapper' => 'med-fieldset-wrapper',
   		),
  	);
	}

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_premed_form_submit'),
	);	
return $form;
}


/*
 * This is the form submission callback for the premed form.
 */
			
function vistaportal_premed_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user -> uid);

/* Save the form values to the premed table in 
 * the database and set the flag in the drupal_flags 
 * table. If the user refills this form, we need to 
 * unset and then reset the premed status flag in 
 * the drupal_flags table.	
 */
	db_update('vss_drupal_flags')
		->fields(array(
			'premed'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the premed table.*/
	db_delete('vss_premed')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the premed table.
 * @TODO remember to add the dynamic fields to the form
 * and also to the db_query.
 */		
	$premed = new stdClass();
	foreach($form_state['values']['premed'] AS $key => $value){
		$form_state['values']['premed'][$key]['date_from'] = 
			$form_state['values']['premed'][$key]['year_from'] . '-' .
			$form_state['values']['premed'][$key]['month_from'];
		$form_state['values']  ['premed'][$key]['date_to'] = 
			$form_state['values']['premed'][$key]['year_to'] . '-' .
			$form_state['values']['premed'][$key]['month_to'];		
		$premed->uid = $user->uid;
		$premed->formtype = 1001;
		$premed->school = $form_state['values']['premed'][$key]['school'];
		$premed->degree = $form_state['values']['premed'][$key]['degree'];
		$premed->city = $form_state['values']['premed'][$key]['city'];
		$premed->state = $form_state['values']['premed'][$key]['state'];
		$premed->country = $form_state['values']['premed'][$key]['country'];
		$premed->date_from = $form_state['values']['premed'][$key]['date_from'];
		$premed->date_to = $form_state['values']['premed'][$key]['date_to'];

	db_insert('vss_premed')
		->fields(array(
			'uid' => $premed->uid,
			'formtype' => $premed->formtype,
			'school' => $premed->school,
			'degree' => $premed->degree,
			'city' => $premed->city,
			'state' => $premed->state,
			'country' => $premed->country,
			'date_from' => $premed->date_from,
			'date_to' => $premed->date_to,
		))
		->execute();	
	}		
/*
 * Update the drupal_flags table by setting the premed 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags')
		->fields(array(
			'premed'=>1,
	))
		->condition('uid', $user->uid)
		->execute();			

/*%&%&%&&%%&%&%&%&%&%&&%&%&%&%&%&%&&%&%&%&%&%&%&%&%&%&%&%&%%&%&%&*/

/* Save the form values to the med table in 
 * the database and set the flag in the drupal_flags 
 * table. If the user refills this form, we need to 
 * unset and then reset the premed status flag in 
 * the drupal_flags table.	
 */
	db_update('vss_drupal_flags')
		->fields(array(
			'med'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the med table.*/
	db_delete('vss_medschool')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the med table.
 * @TODO remember to add the dynamic fields to the form
 * and also to the db_query.
 */		
	$premed = new stdClass();
	foreach($form_state['values']['med'] AS $key => $value){
		$form_state['values']['med'][$key]['date_from'] = 
			$form_state['values']['med'][$key]['year_from'] . '-' .
			$form_state['values']['med'][$key]['month_from'];
		$form_state['values']  ['med'][$key]['date_to'] = 
			$form_state['values']['med'][$key]['year_to'] . '-' .
			$form_state['values']['med'][$key]['month_to'];
				
		$med->uid = $user->uid;
		$med->formtype = 1001;
		$med->school = $form_state['values']['premed'][$key]['school'];
		$med->degree = $form_state['values']['premed'][$key]['degree'];
		$med->city = $form_state['values']['premed'][$key]['city'];
		$med->state = $form_state['values']['premed'][$key]['state'];
		$med->country = $form_state['values']['premed'][$key]['country'];
		$med->date_from = $form_state['values']['premed'][$key]['date_from'];
		$med->date_to = $form_state['values']['premed'][$key]['date_to'];
		$med->ecfmg = $form_state['values']['ecfmg'];

	db_insert('vss_medschool')
		->fields(array(
			'uid' => $med->uid,
			'formtype' => $med->formtype,
			'school' => $med->school,
			'degree' => $med->degree,
			'city' => $med->city,
			'state' => $med->state,
			'country' => $med->country,
			'date_from' => $med->date_from,
			'date_to' => $med->date_to,
			'ecfmg'=> $med->ecfmg,
		))
		->execute();	
	}		
/*
 * Update the drupal_flags table by setting the premed 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags')
		->fields(array(
			'med'=>1,
	))
		->condition('uid', $user->uid)
		->execute();
			
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/internship' . $user->uid);	
	
/*
 * @TODO add error checking
 */	
}	


/*
 * Ajax callback for the premed form
 */
function vistaportal_premed_form_add_school_callback($form, $form_state){
	return $form['premed'];
}

/*
 * Ajax callback for the med form
 */
function vistaportal_med_form_add_school_callback($form, $form_state){
	return $form['med'];
}

/*
 * Increment the counter when the button is pressed
 */
function vistaportal_form_add($form, &$form_state){
	$form_state['num_schools']++;
  $form_state['rebuild'] = TRUE;		
}

/*
 * Decrement the counter when the button is pressed
 */	
function vistaportal_form_remove($form, &$form_state){
	if ($form_state['num_schools'] > 1) {
  	$form_state['num_schools']--;
  }
  $form_state['rebuild'] = TRUE;
}

/*
 * Function to raster a tif file from a pdf
 */
function pdf_to_tiff(){
	$outputTiffFileName = "C:/wamp/www/phportal/sites/default/files/pdf/foo.tiff";
	$inputPDFFileName = "C:/wamp/www/phportal/sites/default/files/pdf/VISTA13_phys_apply_v1.pdf";	
	$cmd = "c:/progra~1/gs/gs9.06/bin/gswin64c -SDEVICE=tiffg4 -r300x300 -sPAPERSIZE=letter -sOutputFile=$outputTiffFileName -dNOPAUSE -dBATCH  $inputPDFFileName";	
	$response = shell_exec($cmd);
	return $response;	
} 
