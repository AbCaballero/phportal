<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: December 14th, 2012
 * Notes: This file contains is the submit page.
 */

 /*
 * Form callback for the submit form.
 */
function vistaportal_submission_form($form, &$form_state){
	$form = array(); 
	$form['#attributes'] = array('enctype' => array("multipart/form-data"));
	$form['foo'] = array(
		'#type'=>'fieldset',
		'#title' => t('Submission'),
		'#collapsible' => FALSE,
		'#prefix' => '<div id="submission-fieldset-wrapper">',
		'#suffix' => '</div>',
	);	
	$form['foo']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit>'),
		'#submit' => array('vistaportal_submission_form_submit'),
	);
return $form;
}


/*
 * Submission call back for the vistaportal_submit_form
 */
function vistaportal_submission_form_submit(){
	include_once('mPDF.inc');
	include_once('ghostscript.inc');
	$file = "C:/wamp/www/phportal/sites/default/files/pdf/vista-forms.html";
	$html_string = file_get_contents($file);
	$filename = make_pdf_1($html_string);
} 

/*function vistaportal_submission_form_submit(){
	include_once('mPDF.inc');
	include_once('ghostscript.inc');
  $file = "/var/www/html/devapply.vistastaff.com/sites/default/files/pdf/foo.html"; 
	$html_string = file_get_contents($file);
	$filename = make_pdf_1($html_string);
  $tiff = pdf_to_tiff();
}*/