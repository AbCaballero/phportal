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
		'#title' => t('RELEASE & AUTHORIZATION'),
		'#collapsible' => FALSE,
	);
	
	$form['authorization']['desc'] = array(
		'#markup' => t('
<br />
<p>
	I, hereby authorize all medical schools, university transcript
	offices, medical institutions or organizations, personal references, physicians,
	attorneys, employers, medical malpractice insurance carriers or organizations,
	business and professional associates, all government agencies and
	instrumentalities (local, state, federal, or foreign), all health care providers, the
	American Medical Association and/or the American Osteopathic Association,
	the National Practitioner Data Bank and the Federation of State Medical Boards
	to release to state licensing boards and to VISTA Staffing Solutions and VISTA
	HealthCare Partners any information, opinions, files, transcripts, or records required
	by that particular board or by VISTA Staffing Solutions and VISTA HealthCare
	Partners for its evaluation of my qualifications for credentialing and for medical
	licensing purposes. I hereby give my permission for representatives of VISTA
	Staffing Solutions and VISTA HealthCare Partners to discuss my application
	information with clients and licensing boards, and hereby waive any privilege of
	confidentiality of such information for the purpose indicated herein.
</p>
<br><br>
<p>
	I consent to the release of all information necessary, including that which otherwise
	is privileged or confidential, to evaluate my qualifications, character, professional
	ethics and competence to practice medicine in my specialty. This includes
	information relative to any treatment for or the existence of a condition that could
	impair my ability to practice medicine with reasonable skill and safety, including
	infectious diseases, psychiatric and mental health conditions, and alcohol and
	drug abuse.
</p>
<br><br>
<p>
	I, the undersigned, release all organizations and individuals from all liability for
	any damages that may result from providing this information. I agree that neither
	VISTA Staffing Solutions nor VISTA HealthCare Partners is under any obligation
	to disclose to me any of the information collected for credentialing, referencing,
	and licensing purposes except pursuant to subpoena. This consent for release of
	information may be revoked by me anytime in writing. However, any party, program
	or person making disclosure prior to receipt of such revocation is deemed as having
	acted in good faith based on this document. If not previously revoked, this Release
	and Authorization will terminate two years from the date on this document.
</p>
<br><br>
<p>
	The original or a copy hereof shall operate as full proof of authority and release.
</p>
<br><br>
'),
);
	//This is the line separator
    $form['authorization']['lines'] = array(
	  '#prefix' => '<div class="line-solid">',
		'#suffix' => '</div>',
	  );
	$form['authorization']['accept'] = array(
		'#type' =>'checkbox',
		'#title' => t('By checking this box you agree that all your information is correct...NEED FROM LEGAL DEPARTMENT'),
		'#required' => TRUE,
	);
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
      '#attributes' => array('class' => array('button prev')),
      '#submit'=> array('vistaportal_release_previous'),
    );
    $form['prev']['#attributes'] = array('class' => array('prev')); 
												
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
       	/*	db_update('vss_drupal_flags')
		->fields(array(
			'uid'=>$user->uid,
			'release' => 0,
		))
		->execute();*/
		 
/*Overwrite any existing values in the references table.*/
	db_delete('vss_release')
		->condition('uid', $user->uid)
		->execute();
		
/*Insert the form_state values into the references table.*/		
  $release = new stdClass();
	$release->uid = $user->uid;
	$release->terms = $form_state['values']['accept'];
	
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
       /*		db_update('vss_drupal_flags')
		->fields(array(
			'uid'=>$user->uid,
			'release' => 1,
		))
		->execute();	*/							
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/submit' . $user->uid);	
}

  function vistaportal_release_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/upload' . $user -> uid);
  }
	
	/*
   * Go to the next page
   */
  function vistaportal_next($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/submit' . $user -> uid);
  }	