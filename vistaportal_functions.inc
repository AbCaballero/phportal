<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains the function definitions for the
 * different forms.
 */

  
/*Ajax method to dynamically add fields to a form
 * 
 */
	function vistaportal_add_fields($form, &$form_state){
		$form_state['counter']++;
  	$form_state['rebuild'] = TRUE;		
	}

/*Ajax method to dynamically remove fields from a form
 * 
 */	
	function vistaportal_remove_fields($form, &$form_state){
		if ($form_state['counter'] > 1) {
    	$form_state['counter']--;
  	}
  	$form_state['rebuild'] = TRUE;
	}