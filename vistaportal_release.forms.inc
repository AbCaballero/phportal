<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the vistaportal_release_authorization_form
 * callback and form submission callback 
 */
 
 
/*
 * Form callback for release and authorization form
 */
function vistaportal_release_authorization_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	$form = array();
	$form['authorization'] = array(
		'#type' => 'fieldset',
		'#title' => t('Release & Authorization'),
		'#collapsible' => FALSE,
	);
	
	$form['authorization']['desc'] = array(
		'#markup' => t('<br /><p>I hereby authorize all medical schools, university 
		transcript offices, medical institutions or organizations, personal references, physicians, 
		attorneys, employers, medical malpractice insurance carriers or organizations, business and 
		professional associates, all government agencies and instrumentalities (local, state, federal, 
		or foreign), all health care providers, the American Medical Association and/or the American 
		Osteopathic Association, the National Practitioner Data Bank and the Federation of State 
		Medical Boards to release to state licensing boards and to VISTA Staffing Solutions and 
		VISTA HealthCare Partners any information, opinions, files, transcripts, or records required 
		by that particular board or by VISTA Staffing Solutions and HealthCare Partners for its 
		evaluation of my qualifications for credentialing and for medical licensing purposes. I hereby 
		give my permission for representatives of VISTA Staffing Solutions and HealthCare Partners to 
		discuss my application information with clients and licensing boards, and hereby waive any 
		privilege of confidentiality of such information for the purpose indicated herein.</p>
		<p>I consent to the release of all information necessary, including that which otherwise is 
		privileged or confidential, to evaluate my qualifications, character, professional ethics and 
		competence to practice medicine in my specialty. This includes information relative to any 
		treatment for or the existence of a condition which could impair my ability to practice medicine 
		with reasonable skill and safety, including infectious diseases, psychiatric and mental health 
		conditions, and alcohol and drug abuse.<p><p>I, the undersigned, release all organizations 
		and individuals from all liability for any damages which may result from providing this 
		information. I agree that neither VISTA Staffing Solutions nor VISTA HealthCare Partners is 
		under any obligation to disclose to me any of the information collected for the credentialing, 
		referencing, and licensing purposes except pursuant to subpoena. This consent for release of 
		information may be revoked by me anytime in writing. However, any party, program or person 
		making disclosure prior to receipt of such revocation is deemed as having acted in good faith 
		based on this document. If not previously revoked, this Release and Authorization will terminate 
		two (2) years from the date on this document.</p><p>The original or a copy hereof shall 
		operate as full proof of authority and release.'),
	);
		
	$form['authorization']['accept'] = array(
		'#type' =>'checkbox',
		'#title' => t('I Accept the Terms'),
		'#required' => TRUE,
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Submit',
	);											
return $form;	
}	

function vistaportal_release_authorization_form_submit($form, &$form_state){
	global $user;
	$account = user_load($user->uid);
	//$user_name;
	//$html_string;
	//make_pdf;
	//make_tiff;
	//save record

/*
 * If the user refills this form, we need to unset the
 * release status flag in the vss_drupal_flags table.	
 */
	db_update('vss_drupal_flags')
		->fields(array(
			'release'=>0,
	))
		->condition('uid', $user->uid)
		->execute();
		 
/*Overwrite any existing values in the references table.*/
	db_delete('vss_release')
		->condition('uid', $user->uid)
		->execute();
		
/*Insert the form_state values into the references table.*/		
  $release = new stdClass();
	$release->uid = $user->uid;
	$release->terms = $form_state['values']['authorization']['accept'];
	
  db_insert('vss_release')
		->fields(array(
			'uid' => $release->uid, 
			'terms' => $release->terms, 
	))
		->execute();

/*
 * Insert the user_id into the vss_drupal_flags table and set the references bit,
 * letting us know that the form has been filled out.
 */		
		db_update('vss_drupal_flags')
		->fields(array(
			'uid'=>$user->uid,
			'release' => 1,
		))
		->execute();								
	$user = user_load($form_state['uid']);
	drupal_goto('submission' . $user->uid);	
}