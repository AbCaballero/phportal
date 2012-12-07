<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the pre-med section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the premed form.
 */  
function vistaportal_premed_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');
	//Set this to tree so we can access all dynamic form values
	$form['#tree'] = TRUE;
	$form['#attributes'] = array('enctype' => array("multipart/form-data"));
	
	$form['premed'] = array(
		'#type'=>'fieldset',
		'#title' => t('Pre-Medical Education'),
		'#collapsible' => FALSE,
		'#prefix' => '<div id="premed-fieldset-wrapper">',
		'#suffix' => '</div>',
	);
	
	//This counter will be used to determine how many education sections to add
	if(empty($form_state['num_schools'])){
		$form_state['num_schools'] = 1;
	}
	
	for($i = 0; $i < $form_state['num_schools']; $i++){
		$form['premed'][$i]['school'] = textfield('School');
		$form['premed'][$i]['degree'] = edu('Degree Earned');
		$form['premed'][$i]['city'] = textfield('City');
		$form['premed'][$i]['state'] = state('State');
		$form['premed'][$i]['country'] = country('Country');
		$form['premed'][$i]['date_from'] = date_popup('Start Date');
		$form['premed'][$i]['date_to'] = date_popup('End Date');
	}
	
	//Only allow 3 schools for the premed form
	if($form_state['num_schools'] < 3 ){
		$form['premed']['add_another'] = array(
   		'#type' => 'submit',
   		'#value' => t('Add another school'),
   		'#submit' => array('vistaportal_premed_form_add_school'),
   		'#limit_validation_errors' => array(),
   		'#ajax' => array(
     		'callback' => 'vistaportal_premed_form_add_school_callback',
     		'wrapper' => 'premed-fieldset-wrapper',
     		'method' => 'replaceWith',
			),
  	);
	}
	
	//First school is mandatory
	if($form_state['num_schools'] > 1 ){
		$form['premed']['remove_school'] = array(
		  '#type' => 'submit',
   		'#value' => t('Remove a school'),
   		'#submit' => array('vistaportal_premed_form_remove_school'),
   		'#limit_validation_errors' => array(),
   		'#ajax' => array(
     		'callback' => 'vistaportal_premed_form_add_school_callback',
     		'wrapper' => 'premed-fieldset-wrapper',
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
	include_once('pdf_html_strings/premed_html.inc');
	include_once('mPDF.inc');
	global $user;
	$account = user_load($user -> uid);
	dsm($form_state['values']['premed'], 'here');
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;

	$html_string = getpremed_html(
		$form_state['values']['premed'][0]['school'],
		$form_state['values']['premed'][0]['degree'], 
		$form_state['values']['premed'][0]['city'],
		$form_state['values']['premed'][0]['state'], 
		$form_state['values']['premed'][0]['country'],
		$form_state['values']['premed'][0]['date_from'], 
		$form_state['values']['premed'][0]['date_to']
	);
	
	$filename = make_pdf_1($html_string,'Pre-med form');
	pdf_to_tiff();
 
/* Save the form values to the premed table in 
 * the database and set the flag in the drupal_flags 
 * table. If the user refills this form, we need to 
 * unset and then reset the premed status flag in 
 * the drupal_flags table.	
 */
	db_update('drupal_flags')
		->fields(array(
			'premed'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the premed table.*/
	db_delete('premed')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the premed table.
 * @TODO remember to add the dynamic fields to the form
 * and also to the db_query.
 */		
	$premed = new stdClass();
	$premed->uid = $user->uid;
	foreach($form_state['values']['premed'] AS $key => $value){
		$premed->school = $form_state['values']['premed'][$key]['school'];
		$premed->degree = $form_state['values']['premed'][$key]['degree'];
		$premed->city = $form_state['values']['premed'][$key]['city'];
		$premed->state = $form_state['values']['premed'][$key]['state'];
		$premed->country = $form_state['values']['premed'][$key]['country'];
		$premed->date_from = $form_state['values']['premed'][$key]['date_from'];
		$premed->date_to = $form_state['values']['premed'][$key]['date_to'];

	db_insert('premed')
		->fields(array(
			'uid' => $premed->uid,
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
	db_update('drupal_flags	')
		->fields(array(
			'premed'=>1,
	))
		->condition('uid', $user->uid)
		->execute();			
			
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/medschool' . $user->uid);	
	
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
 * Increment the counter when the button is pressed
 */
function vistaportal_premed_form_add_school($form, &$form_state){
	$form_state['num_schools']++;
  $form_state['rebuild'] = TRUE;		
}

/*
 * Decrement the counter when the button is pressed
 */	
function vistaportal_premed_form_remove_school($form, &$form_state){
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
