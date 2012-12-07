<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the disciplinary actions section of the 
 * physicians pre-application form.
 */

/*
 * This is the form callback for the disciplinary form.
 */ 
function vistaportal_disciplinary_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	include_once('vistaportal_functions.inc');	
	$form = array();
	$form['disc'] = fieldset('Disciplinary Actions');
	$form['disc']['expl'] = array('#markup' => t("If you answer 'YES' to any of the following, please provide 
		signed and dated explanations on a separate sheet"));
  $form['disc']['desc'] = array('#markup' => t('DISCIPLINARY ACTIONS - Have any of the following ever been
		or are currently in the process of being investigated, denied, revoked, suspended, reduced,
		limited, placed on probation, not renewed, been subject to disciplinary action or voluntarily
		relinquished? IF yes, please provide a full explanation on a separate sheey of paper'));
	$form['disc']['med_lic'] = radios_yesno('Medical licence in any jurisdication?');
	$form['disc']['other_lic'] = radios_yesno('Other professional registration/licence?');
	$form['disc']['dea_reg'] = radios_yesno('DEA registration?');
	$form['disc']['academic_apt'] = radios_yesno('Academic discipline or appointment?');
	$form['disc']['med_staff_apt'] = radios_yesno('Membership on any hospital medical staff?');
	$form['disc']['clinical_priv'] = radios_yesno('Clinical privileges?');
	$form['disc']['perogatives'] = radios_yesno('Perogatives/rights on any medical staff?');
	$form['disc']['affiliation'] = radios_yesno('Any medical organization or other institutional 
		affiliation or status there at?');
	$form['disc']['board_cert'] = radios_yesno('Professional society membership or fellowship/Board 
		Certification?');
	$form['disc']['pro_office'] = radios_yesno('Professional Office?');
	$form['disc']['other_sanction'] = radios_yesno('Any other type of professional sanction or 
		discipline, including by Medicare/Medicaid or private insurance company?');
	$form['disc']['convicted'] = radios_yesno('Have you ever been convicted of a misdemeanor
		(other than minor traffic violation) or a felony?');
	$form['disc']['malpractice'] = radios_yesno('Have there ever been or are there currently 
		pending, any malpractice claims, suits, settlements or arbitration proceedings involving
		your professional practice?');
	$form['disc']['insurance'] = radios_yesno('Have you ever been denied, gone without, 
		or not maintained Professional Liability Insurance?');
	$form['disc']['med_condition'] = radios_yesno('Do you currently have any medical condition or 
		use any chemical substance which impairs or limits your ability to practice medicine
		with reasonable skill and safety? If yes, provide evidence that such conditions do not 
		currently impair or limit your ability to practice medicine in your specialty with 
		reasonable skill and safety.');
	$form['disc']['treatment'] = radios_yesno('Within the past two (2) years, have you received 
		treatment for alcoholism, drug abuse, or for any infectious disease, mental illness or 
		psychiatric problem which could impair or limit your ability to practice medicine in your 
		specialty with reasonable skill and safety? If yes, provide evidence that such conditions 
		do not currently impair or limit your ability to practice medicine in your specialty with 
		reasonable skill and safety.');
	$form['disc']['other'] = radios_yesno('Other than those circumstances noted above, is there 
		anything in your personal or professional background that may surface during our credentials 
		verification process that may be construed as derogatory or negative?');
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Continue'),
		'#name' => 'next',
		'#submit' => array('vistaportal_disciplinary_form_submit'),
	);	

return $form;
}

/*
 * This is the form submission callback for the disciplinary form.
 */
			
function vistaportal_disciplinary_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user -> uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record
	
/* If the user refills this form, we need to unset the
 * disciplinary status flag in the drupal_flags table.	
 */
	db_update('drupal_flags	')
		->fields(array(
			'disciplinary'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the disciplinary table.*/
	db_delete('disciplinary')
		->condition('uid', $user->uid)
		->execute();		

/*Insert the form_state values into the disciplinary table.*/
	$disciplinary = new stdClass();
	$disciplinary->uid = $user->uid;
	$disciplinary->med_lic = $form_state['values']['disc']['med_lic'];
	$disciplinary->other_lic = $form_state['values']['disc']['other_lic'];
	$disciplinary->dea_reg = $form_state['values']['disc']['dea_reg'];
	$disciplinary->academic_apt = $form_state['values']['disc']['academic_apt'];
	$disciplinary->med_staff_apt = $form_state['values']['disc']['med_staff_apt'];
	$disciplinary->clinical_priv = $form_state['values']['disc']['clinical_priv'];
	$disciplinary->perogatives = $form_state['values']['disc']['perogatives'];
	$disciplinary->affiliation = $form_state['values']['disc']['affiliation'];
	$disciplinary->board_cert = $form_state['values']['disc']['board_cert'];
	$disciplinary->pro_office = $form_state['values']['disc']['pro_office'];
	$disciplinary->other_sanction = $form_state['values']['disc']['other_sanction'];
	$disciplinary->convicted = $form_state['values']['disc']['convicted'];
	$disciplinary->malpractice = $form_state['values']['disc']['malpractice'];
	$disciplinary->insurance = $form_state['values']['disc']['insurance'];
	$disciplinary->med_condition = $form_state['values']['disc']['med_condition'];
	$disciplinary->treatment = $form_state['values']['disc']['treatment'];
	$disciplinary->other = $form_state['values']['disc']['other'];
	
	db_insert('disciplinary')
		->fields(array(
	'uid' => $disciplinary->uid,
	'med_lic' => $disciplinary->med_lic, 
	'other_lic' => $disciplinary->other_lic, 
	'dea_reg' => $disciplinary->dea_reg,
	'academic_apt' => $disciplinary->academic_apt, 
	'med_staff_apt' => $disciplinary->med_staff_apt, 
	'clinical_priv' => $disciplinary->clinical_priv, 
	'perogatives' => $disciplinary->perogatives, 
	'affiliation' => $disciplinary->affiliation, 
	'board_cert' => $disciplinary->board_cert, 
	'pro_office' => $disciplinary->pro_office, 
	'other_sanction' => $disciplinary->other_sanction, 
	'convicted' => $disciplinary->convicted, 
	'malpractice' => $disciplinary->malpractice, 
	'insurance' => $disciplinary->insurance, 
	'med_condition' => $disciplinary->med_condition, 
	'treatment' => $disciplinary->treatment, 
	'other' => $disciplinary->other, 
	))
		->execute();

/*
 * Update the drupal_flags table by setting the disciplinary 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('drupal_flags')
		->fields(array(
			'disciplinary'=>1,
	))
		->condition('uid', $user->uid)
		->execute();				
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/references' . $user->uid);	
}		