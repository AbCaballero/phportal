<?php
include_once('vistaportal_identity.forms.inc');
include_once('vistaportal_premed.forms.inc');
include_once('vistaportal_medschool.forms.inc');
include_once('vistaportal_internship.forms.inc');
include_once('vistaportal_residency.forms.inc');
include_once('vistaportal_affiliations.forms.inc');
include_once('vistaportal_certifications.forms.inc');
include_once('vistaportal_licensure.forms.inc');
include_once('vistaportal_disciplinary.forms.inc');
include_once('vistaportal_references.forms.inc');
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 26th, 2012
 * Notes: This file contains the physician pre-applications wizard
 * forms, the next and previous buttons, the submit handlers and 
 * the validation.
 */

function physician_pre_application_wizard($form, &$form_state){
	//Initialize a description of the steps for the wizard
	if(empty($form_state['step'])){
		$form_state['step'] = 1;
		$form_state['step_information'] = vistaportal_form_steps();
	}
	
	$step = &$form_state['step'];
	
	//Call the function named in $form_state['step_information'], to 
	//get the form elements to display for this step
	$form = $form_state['step_information'][$step]['form']($form, $form_state);
	//Show the previous button if we are not on the first page. The submit
	//handler will skip validation errors when using the back button.
	if($step > 1){
		$form['prev'] = array(
			'#type' => 'submit',
			'#value' => t('Previous'),
			'#name' => 'prev',
			'#submit' => array('physician_pre_application_wizard_previous_submit'),
			'#limit_validation_errors' => array(),
		);
	}
	//Show the next button only if more steps are defined
	if($step < count($form_state['step_information'])){
		//then include the next button
		$form['next'] = array(
			'#type' => 'submit',
			'#value' => t('Next'),
			'#name' => 'next',
			'#submit' => array('physician_pre_application_wizard_next_submit'),
		);
	}
	else{
		//If there are no more steps, use the default submit handler
		$form['finish'] = array(
			'#type' => 'submit',
			'#value' => t('Finalize'),
		);
	}
	
	$form['next']['#validate'] = array();
	if(function_exists($form_state['step_information'][$step]['form'] . '_validate')){
		$form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . 
			'_validate');
	}
	if(isset($form['#validate'])){
		$form['next']['#validate'] = array_merge($form['next']['#validate'], $form['#validate']);
		unset($form['#validate']);
	}
	
	if(function_exists($form_state['step_information'][$step]['form'] . '_submit')){
		$form['next']['#submit'] = array_merge($form_state['step_information'][$step]['form'] . 
			'_submit', $form['next']['#submit']);
	}
	if(isset($form['#submit'])){
		$form['next']['#submit'] = array_merge($form['#submit'], $form['next']['#submit']);
		unset($form['#submit']);
	}

return $form;		
}

/*
 * This is the previous submit handler
 */
function physician_pre_application_wizard_previous_submit($form, &$form_state){
	$current_step = &$form_state['step'];
	$form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
	if($current_step > 1){
		$current_step--;
		$form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
	}
	$form_state['rebuild'] = TRUE;
}

/*
 * This is the next submit handler
 */
function physician_pre_application_wizard_next_submit($form, &$form_state){
	$current_step = &$form_state['step'];
	$form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
	if($current_step < count($form_state['step_information'])){
		$current_step++;
		if(!empty($form_state['step_information'][$current_step]['stored_values'])){
			$form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
		}
		else{
			$form_state['values'] = array();
		}
		//Force rebuild when button is clicked
		$form_state['rebuild'] = TRUE;
		
		return;
	}
}

/*
 * This is the finalize submit handler
 */	
function physician_pre_application_wizard_submit($form, &$form_state){
	$current_step = $form_state['step'];
	$form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
	foreach($form_state['step_information'] AS $key => $value){
		unset($value['stored_values']['form_id']);
		unset($value['stored_values']['form_build_id']);
		unset($value['stored_values']['form_token']);
		
		drupal_set_message(t('Step @num collected the following values: <pre>@result</pre>', 
		array('@num' => $key, '@result' => print_r($value['stored_values'], TRUE))));
	}
	$user = user_load($form_state['uid']);
	drupal_goto('release' . $user->uid);		  
}

/*
 * Pre-application form steps
 */
function vistaportal_form_steps(){
	return array(
		1 => array(
			'form' => 'vistaportal_identity_form',
		),
		2 => array(
			'form' => 'vistaportal_premed_form',
		),
		3 => array(
			'form' => 'vistaportal_medschool_form',
		),
		4 => array(
			'form' => 'vistaportal_internship_form',
		),
		5 => array(
			'form' => 'vistaportal_residency_form',
		),
		6 => array(
			'form' => 'vistaportal_affiliations_form',
		),
		7 => array(
			'form' => 'vistaportal_certifications_form',
		),
		8 => array(
			'form' => 'vistaportal_licensure_form',
		),
		9 => array(
			'form' => 'vistaportal_disciplinary_form',
		),
		10 => array(
			'form' => 'vistaportal_references_form',
		),
	);								
}