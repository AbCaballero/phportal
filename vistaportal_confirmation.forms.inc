<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: December 7th, 2012
 * Notes: This is the registration 
 * confirmation page.
 */

 /*
 * This is the form callback for the 
  * registration confirmation form.
 */  
function vistaportal_confirmation_form($form, &$form_state){
	include_once('vistaportal.fields.inc');
	$form = array();
	$form['confirmation'] = array(
		'#type' => 'fieldset',
		'#title' => t('Thank You'),
		'#collapsible' => FALSE,
	);
	$form['confirmation']['message'] = array(
<<<<<<< HEAD
		'#markup' => t('<br /><p>Thank you for submitting your information, 
=======
		'#markup' => t('<br /><p>Thank you for submitting you information, 
>>>>>>> fca29b309f4c68500be076725e1d93310cf929a5
			you will receive an email shortly</p>'),
	);
	
return $form;
}	 
