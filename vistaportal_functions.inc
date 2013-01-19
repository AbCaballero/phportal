<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: Demeber 8th, 2012
 * Notes: This file contains the business logic for the 
 * vistaportal site. It willeventually expose the webservices
 * as well.
 */



/*
 * This will run in the hook_cron(). It will send a one-time
 * link via email to new users, allowing them to create 
 * a password
 */  

 function _create_new_account(){
	$query = db_select('users', 'u');
	$query->innerjoin('vss_profile_data', 'p', 'u.uid = p.uid');
	/*Set to isNotNull after testing is complete*/
	$query->isNull('p.entity_id'); 
	$query->condition('p.new_user_flag', 0, '=');	
	$query->fields('u', array('uid', 'name', 'mail'))
		->fields('p', array('entity_id', 'new_user_flag'))
		->orderBy('uid');
	$result = $query->execute();
	
	foreach($result AS $account){
		$mail = _user_mail_notify('register_no_approval_required', $account);
		db_update('vss_profile_data')
			->fields(array(
			'new_user_flag' => 1
		))
		->condition('uid', $account->uid)
		->execute();
	}
 }



  /*
   * Save and logout redirect
   */
  function vistaportal_save_logout($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('user/logout' . $user -> uid);
  } 


    


  
 
