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
	$result = db_select('profile_data', 'p')
	  ->fields('p')
		->condition('entity_id', '', '!=')
		->condition('new_user_flag', 1, '!=')
		->execute()
		->fetchAssoc();
		
		
	foreach($result AS $key => $value){
		$fields = array(
			'name' => $result['email'],
			'pass' => $result['password'],
			'mail' => $result['mail'],
			'status' => 1,
			'init' => $result['email'],
			'roles' => array(
				DRUPAL_AUTHENTICATED_RID => 'authenticated user',
			),
		);
		$account = user_save('', $fields);		
		$to = $result[$key];
		$from = "andrew.browning@anergroup.com";
		$link = user_pass_reset_url($entity_created);
		dsm($link, 'here');
		$params['new_user_link'] = $link; //This will be a link for the user to click
		$sent = drupal_mail('vistaportal_email', 'key', $to, language_default(), $params, $from, TRUE);
		
		if(!$sent){
			//Write a message to the error log
		}
		else{
		db_update('profile_data')
			->fields(array(
				'new_user_flag' => 1
		))
		->condition('email', $result)
		->execute();
		}
	}
}

/*
 * Load user account based upon entity_id
 */
function _account_load($entity_id, $uid){
	$record = db_select('profile_data','p')
		->fields('c')
		->execute()
		->fetchAssoc();	
	
	$account = user_load($record);
	return $account;		
}

/*
 * Retrieve the user object 
 */ 
function _account_resource_retrieve($entity_id){
	return(object)array(
		'account' => account_load($entity_id),
	);
}

/*
 * Candidate class
 */
class Candidate {
	public $uid;
	public $account;
	public $profile;
	public $entity_id; 
 
	/*
 	 * Constructor for the candidate profile 
   */
	function _construct($entity_id, $uid){
		$this->entity_id = $entity_id;
		$this->uid = $uid;
		$this->load($profile);
	}

  /*
   * Function to load the candidate profile. We can use some
	 * of this data to populate the forms
   */
	private function load_profile() {
		$profile = _account_load($this->entity_id, $this->uid);
		$profile->name = $profile->first_name .' '. $profile->last_name; 
	}
}	 

/*
 * get the candidate profile
 */
function get_candidate($entity_id, $uid, $reset = FALSE){
	if (!$entity_id) {
		//Print an error message.
  }
	static $candidates = array();
  if (is_object($candidates[$entity_id]) && !$reset) {
  	return $candidates[$entity_id];
  }
  $candidates[$entity_id] = new Candidate($entity_id, $uid);
	return $candidates[$entity_id];
} 
    
/*
 * Invoke the hook_mail();
 */ 
function vistaportal_email_mail($key, &$message, $params){
	$language = $message['language']; //How do we set this value?
		switch($key){
			case 'new_user':
				//$vars required even if empty
				$message['subject'] = t('Subject', $vars, $language->language);
				$message['body'][] = "This is the body of the new_user email which
					will include some text and a link $link, here";
				break;	
	 	}	 	
} 

  
/*
 * Invoke the hook_email_registration_name().
 */
function vistaportal_email_registration_name($edit, $account){
	return $account->mail;
} 
