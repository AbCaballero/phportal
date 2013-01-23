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
	$form['disc'] = fieldset('DISCIPLINARY ACTIONS');
	
  $form['disc']['desc'] = array('#markup' => t('<p>Have any of the following ever been
		or are currently in the process of being investigated, denied, revoked, suspended, reduced,
		limited, placed on probation, not renewed, been subject to disciplinary action or voluntarily
		relinquished? <strong>IF yes, please provide a full explanation on a separate sheet of paper</strong></p>'));
		/*$form['disc']['expl'] = array('#markup' => t("<p><strong>If you answer 'YES' to any of the following, please provide 
		signed and dated explanations on a separate sheet</strong></p>"));*/
				//This is the line separator
  $form['disc']['line'] = array('#prefix' => '<div class="line-solid">','#suffix' => '</div>',);
	$form['disc']['med_lic'] = array(
      '#type' => 'radios','#title' => t('Medical license in any jurisdication?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
  $form['disc']['other_lic'] = array(
      '#type' => 'radios','#title' => t('Other professional registration/licence?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
  $form['disc']['dea_reg'] = array(
      '#type' => 'radios','#title' => t('DEA registration?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
  $form['disc']['academic_apt'] = array(
      '#type' => 'radios','#title' => t('Academic discipline or appointment?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['med_staff_apt'] = array(
      '#type' => 'radios','#title' => t('Membership on any hospital medical staff?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['clinical_priv'] = array(
      '#type' => 'radios','#title' => t('Clinical privileges?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['perogatives'] = array(
      '#type' => 'radios','#title' => t('Perogatives/rights on any medical staff?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['affiliation'] = array(
      '#type' => 'radios','#title' => t('Any medical organization or other institutional 
		affiliation or status there at?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['board_cert'] = array(
      '#type' => 'radios','#title' => t('Professional society membership or fellowship/Board 
		Certification?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['pro_office'] = array(
      '#type' => 'radios','#title' => t('Professional Office?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['other_sanction'] = array(
      '#type' => 'radios','#title' => t('Any other type of professional sanction or 
		discipline, including by Medicare/Medicaid or private insurance company?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['convicted'] = array(
      '#type' => 'radios','#title' => t('Have you ever been convicted of a misdemeanor
		/(other than minor traffic violation) or a felony?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['malpractice'] = array(
      '#type' => 'radios','#title' => t('Have there ever been or are there currently 
		pending, any malpractice claims, suits, settlements or arbitration proceedings involving
		your professional practice?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['insurance'] = array(
      '#type' => 'radios','#title' => t('Have you ever been denied, gone without, 
		or not maintained Professional Liability Insurance?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['med_condition'] = array(
      '#type' => 'radios','#title' => t('Do you currently have any medical condition or 
		use any chemical substance which impairs or limits your ability to practice medicine
		with reasonable skill and safety? If yes, provide evidence that such conditions do not 
		currently impair or limit your ability to practice medicine in your specialty with 
		reasonable skill and safety.'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['treatment'] = array(
      '#type' => 'radios','#title' => t('Within the past two (2) years, have you received 
		treatment for alcoholism, drug abuse, or for any infectious disease, mental illness or 
		psychiatric problem which could impair or limit your ability to practice medicine in your 
		specialty with reasonable skill and safety? If yes, provide evidence that such conditions 
		do not currently impair or limit your ability to practice medicine in your specialty with 
		reasonable skill and safety.'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	$form['disc']['other'] = array(
      '#type' => 'radios','#title' => t('Other than those circumstances noted above, is there 
		anything in your personal or professional background that may surface during our credentials 
		verification process that may be construed as derogatory or negative?'),
      '#attributes' => array('class' => array('dis-radio')),'#required' => TRUE,
      '#options' => drupal_map_assoc(array('Yes','No' )),
  );
	
	//$form['disc']['dea_reg'] = radios_yesno('DEA registration?');
	//$form['disc']['academic_apt'] = radios_yesno('Academic discipline or appointment?');
	//$form['disc']['med_staff_apt'] = radios_yesno('Membership on any hospital medical staff?');
	//$form['disc']['clinical_priv'] = radios_yesno('Clinical privileges?');
	//$form['disc']['perogatives'] = radios_yesno('Perogatives/rights on any medical staff?');
	//$form['disc']['affiliation'] = radios_yesno('Any medical organization or other institutional 
	//	affiliation or status there at?');
	//$form['disc']['board_cert'] = radios_yesno('Professional society membership or fellowship/Board 
	//	Certification?');
	//$form['disc']['pro_office'] = radios_yesno('Professional Office?');
	//$form['disc']['other_sanction'] = radios_yesno('Any other type of professional sanction or 
		//discipline, including by Medicare/Medicaid or private insurance company?');
	//$form['disc']['convicted'] = radios_yesno('Have you ever been convicted of a misdemeanor
		//(other than minor traffic violation) or a felony?');
	/*$form['disc']['malpractice'] = radios_yesno('Have there ever been or are there currently 
		pending, any malpractice claims, suits, settlements or arbitration proceedings involving
		your professional practice?');*/
	/*$form['disc']['insurance'] = radios_yesno('Have you ever been denied, gone without, 
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
		verification process that may be construed as derogatory or negative?');*/
	
	  //this is a line at the bottom
	  $form['last']['line'] = array(
	  '#prefix' => '<div class="line_left">',
		//'#markup' => '<hr>',
		'#attributes' => array('class' => array('line_left')),
		'#suffix' => '</div>',
		);
		
	  $form['last']['required_field'] = array(
	  '#prefix' => '<div class="required_field2">',
		'#markup' => 'Required Field',
		'#required' => TRUE,
		'#suffix' => '</div>',
		);
	  $form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#name' => 'next',
		'#submit' => array('vistaportal_disciplinary_form_submit'),
		'#attributes' => array('class' => array('affiliations-submit')),
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
      '#submit'=> array('vistaportal_save_logout'),
    );

    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button prev prev')),
      '#submit'=> array('vistaportal_disciplinary_previous'),
    );
    $form['prev']['#attributes'] = array('class' => array('prev'));

return $form;
}

/*
   * Go to the next page
   */
  function vistaportal_next($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/references' . $user -> uid);
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
 * disciplinary status flag in the vss_drupal_flags table.	
 */
	db_update('vss_drupal_flags	')
		->fields(array(
			'disciplinary'=>0,
	))
		->condition('uid', $user->uid)
		->execute();

/*Overwrite any existing values in the disciplinary table.*/
	db_delete('vss_disciplinary')
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
	
	db_insert('vss_disciplinary')
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
 * Update the vss_drupal_flags table by setting the disciplinary 
 * status flag, letting us know that the form has been filled out.
 */		
	db_update('vss_drupal_flags')
		->fields(array(
			'disciplinary'=>1,
	))
		->condition('uid', $user->uid)
		->execute();				
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/references' . $user->uid);	

} 
 function vistaportal_disciplinary_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/licensure' . $user -> uid);
}		