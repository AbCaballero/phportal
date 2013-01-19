<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: November 19th, 2012
   * Notes: This file contains the residency section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the residency form.
   */
  function vistaportal_residency_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    $form['#tree'] = TRUE;
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));
    $form['residency'] = array(
      '#type' => 'fieldset',
      '#title' => t('RESIDENCY'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="residency-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    /*This counter will be used to determine the number
     of residency sections to add
     */

    if (empty($form_state['num_res'])) {
      $form_state['num_res'] = 1;
    }

    for ($i = 0; $i < $form_state['num_res']; $i++) {
      if ($i > 0) {
        $form['residency'][$i]['title-txt' . $i]['#prefix'] = '<div class="line-solid"></div><h2> RESIDENCY ' . ($i + 1) . '</h2><br/>';
      }	
      $form['residency'][$i]['na'] = array(
        '#type' => 'checkbox',
        '#title' => t('Not Applicable'),
        '#required' => FALSE,
      );
			
      $form['residency'][$i]['type' . $i] = textfield('Type');
			$form['residency'][$i]['type' . $i]['#prefix'] = '<div class = "residency-type">' ;
			$form['residency'][$i]['type' . $i]['#suffix'] = '</div>' ;
      $form['residency'][$i]['institution' . $i] = textfield('Institution');
			$form['residency'][$i]['institution' . $i]['#prefix'] = '<div class = "residency-institution">' ;
			$form['residency'][$i]['institution' . $i]['#suffix'] = '</div>' ;
      $form['residency'][$i]['country' . $i] = country('Country');
			$form['residency'][$i]['country' . $i]['#prefix'] = '<div class = "residency-country">' ;
			$form['residency'][$i]['country' . $i]['#suffix'] = '</div>' ;
      $form['residency'][$i]['state' . $i] = state('State');
			$form['residency'][$i]['state' . $i]['#prefix'] = '<div class = "residency-state">' ;
			$form['residency'][$i]['state' . $i]['#suffix'] = '</div>' ;
      $form['residency'][$i]['city' . $i] = textfield('City');
			$form['residency'][$i]['city' . $i]['#prefix'] = '<div class = "residency-city">' ;
			$form['residency'][$i]['city' . $i]['#suffix'] = '</div>' ;
      $form['residency'][$i]['date_from' . $i] = date_my('From');
			$form['residency'][$i]['date_from' . $i]['#prefix'] = '<div class = "residency-date_from">' ;
			$form['residency'][$i]['date_from' . $i]['#suffix'] = '</div>' ;
      $form['residency'][$i]['date_to' . $i] = date_my('To');
			$form['residency'][$i]['date_to' . $i]['#prefix'] = '<div class = "residency-date_to">' ;
			$form['residency'][$i]['date_to' . $i]['#suffix'] = '</div>' ;
      $form['residency'][$i]['prog_dir' . $i] = textfield('Program Director');
			$form['residency'][$i]['prog_dir' . $i]['#prefix'] = '<div class = "residency-prog_dir">' ;
			$form['residency'][$i]['prog_dir' . $i]['#suffix'] = '</div>' ;
    }

    if ($form_state['num_res'] < 3) {
      $form['residency']['add_res'] = array(
        '#type' => 'submit',
        '#value' => t(' + Add Additional Residency'),
        '#submit' => array('vistaportal_residency_form_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_residency_callback',
          'wrapper' => 'residency-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );
    }

    if ($form_state['num_res'] > 1) {
      $form['residency']['remove_res'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove Residency'),
        '#submit' => array('vistaportal_residency_form_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_residency_callback',
          'wrapper' => 'residency-fieldset-wrapper',
        ),
      );
    }
		
			//This is the line separator
      $form['p']['line3'] = array(
	    '#prefix' => '<div class="line-solid">',
		  //'#markup' => '<hr>',
	  	'#attributes' => array('class' => array('line-solid')),
		  '#suffix' => '</div>',
	    );

    $form['fellowship'] = array(
      '#type' => 'fieldset',
      '#title' => t('ADDITIONAL RESIDENCY OR FELLOWSHIP OR OTHER <br> GRADUATE EDUCATION'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="fellowship-fieldset-wrapper">',
      '#suffix' => '</div>',
    );

    if (empty($form_state['num_fellow'])) {
      $form_state['num_fellow'] = 1;
    }

    for ($i = 0; $i < $form_state['num_fellow']; $i++) {
      if ($i > 0) {
        $form['fellowship'][$i]['title-txt' . $i]['#prefix'] = '<div class="line-solid"></div><h2> RESIDENCY ' . ($i + 1) . '</h2><br/>';
      }
		  $form['fellowship'][$i]['na'] = array(
        '#type' => 'checkbox',
        '#title' => t('Not Applicable'),
        '#required' => FALSE,
      );
			
      $form['fellowship'][$i]['type' . $i] = textfield('Type');
			$form['fellowship'][$i]['type' . $i]['#prefix'] = '<div class = "residency-type">' ;
			$form['fellowship'][$i]['type' . $i]['#suffix'] = '</div>' ;
      $form['fellowship'][$i]['institution' . $i] = textfield('Institution');
			$form['fellowship'][$i]['institution' . $i]['#prefix'] = '<div class = "residency-institution">' ;
			$form['fellowship'][$i]['institution' . $i]['#suffix'] = '</div>' ;
      $form['fellowship'][$i]['country' . $i] = country('Country');
			$form['fellowship'][$i]['country' . $i]['#prefix'] = '<div class = "residency-country">' ;
			$form['fellowship'][$i]['country' . $i]['#suffix'] = '</div>' ;
      $form['fellowship'][$i]['state' . $i] = state('State');
			$form['fellowship'][$i]['state' . $i]['#prefix'] = '<div class = "residency-state">' ;
			$form['fellowship'][$i]['state' . $i]['#suffix'] = '</div>' ;
      $form['fellowship'][$i]['city' . $i] = textfield('City');
			$form['fellowship'][$i]['city' . $i]['#prefix'] = '<div class = "residency-city">' ;
			$form['fellowship'][$i]['city' . $i]['#suffix'] = '</div>' ;
      $form['fellowship'][$i]['date_from' . $i] = date_my('From');
			$form['fellowship'][$i]['date_from' . $i]['#prefix'] = '<div class = "residency-date_from">' ;
			$form['fellowship'][$i]['date_from' . $i]['#suffix'] = '</div>' ;
      $form['fellowship'][$i]['date_to' . $i] = date_my('To');
			$form['fellowship'][$i]['date_to' . $i]['#prefix'] = '<div class = "residency-date_to">' ;
			$form['fellowship'][$i]['date_to' . $i]['#suffix'] = '</div>' ;
      $form['fellowship'][$i]['prog_dir' . $i] = textfield('Program Director');
			$form['fellowship'][$i]['prog_dir' . $i]['#prefix'] = '<div class = "residency-prog_dir">' ;
			$form['fellowship'][$i]['prog_dir' . $i]['#suffix'] = '</div>' ;
    }

    if ($form_state['num_fellow'] < 3) {
      $form['fellowship']['add_fellow'] = array(
        '#type' => 'submit',
        '#value' => t(' + Add Additional Institution'),
        '#submit' => array('vistaportal_fellowship_form_add'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_fellowship_callback',
          'wrapper' => 'fellowship-fieldset-wrapper',
          'method' => 'replaceWith',
          'speed' => 'fast',
        ),
      );
    }

    if ($form_state['num_fellow'] > 1) {
      $form['fellowship']['remove_fellow'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove A Institution'),
        '#submit' => array('vistaportal_fellowship_form_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_add_fellowship_callback',
          'wrapper' => 'fellowship-fieldset-wrapper',
        ),
      );
    }

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
      '#value' => t('Save & Next'),
      '#name' => 'next',
      '#submit' => array('vistaportal_residency_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
    );
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
      '#submit'=> array('vistaportal_residency_previous'),
    );
    $form['prev']['#attributes'] = array('class' => array('prev'));		

    $form['#after_build'][] = 'vistaportal_residency_form_afterbuild';
    return $form;
  }

   /*
   * This is the form submission callback for the residency form.
   */

  function vistaportal_residency_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);
    //$user_name;
    //$html_string;
    //make_pdf;
    //make_tiff;
    //save record

    /* If the user refills this form, we need to unset the
     * residency status flag in the vss_drupal_flags table.
     */
    db_update('vss_drupal_flags	') -> fields(array('residency' => 0, )) -> condition('uid', $user -> uid) -> execute();

    /*Overwrite any existing values in the residency table.*/
    db_delete('vss_residency') -> condition('uid', $user -> uid) -> execute();

    unset($form_state['values']['residency']['add_res'], $form_state['values']['residency']['remove_res']);

    dsm($form_state['values']['residency']);
    /*Insert the form_state values into the residency table.*/
    $residency = new stdClass();
    $residency -> uid = $user -> uid;

    foreach ($form_state['values']['residency'] AS $key => $value) {
      $form_state['values']['residency'][$key]['date_from' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['residency'][$key]['date_from' . $key]));
      $form_state['values']['residency'][$key]['date_to' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['residency'][$key]['date_to' . $key]));
      $residency -> type = $form_state['values']['residency'][$key]['type' . $key];
      $residency -> institution = $form_state['values']['residency'][$key]['institution' . $key];
      $residency -> city = $form_state['values']['residency'][$key]['city' . $key];
      $residency -> state = $form_state['values']['residency'][$key]['state' . $key];
      $residency -> country = $form_state['values']['residency'][$key]['country' . $key];
      $residency -> date_from = $form_state['values']['residency'][$key]['date_from' . $key];
      $residency -> date_to = $form_state['values']['residency'][$key]['date_to' . $key];
      $residency -> prog_dir = $form_state['values']['residency'][$key]['prog_dir' . $key];

      db_insert('vss_residency') -> fields(array(
        'uid' => $residency -> uid,
        'type' => $residency -> type,
        'institution' => $residency -> institution,
        'city' => $residency -> city,
        'state' => $residency -> state,
        'country' => $residency -> country,
        'date_from' => $residency -> date_from,
        'date_to' => $residency -> date_to,
        'prog_dir' => $residency -> prog_dir,
      )) -> execute();
    }

    unset($form_state['values']['fellowship']['add_fellow'], $form_state['values']['fellowship']['remove_fellow']);
    dsm($form_state['values']['fellowship']);
    $fellowship = new stdClass();
    $fellowship -> uid = $user -> uid;
    foreach ($form_state['values']['fellowship'] AS $key => $value) {
      $form_state['values']['fellowship'][$key]['date_from' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['fellowship'][$key]['date_from' . $key]));
      $form_state['values']['fellowship'][$key]['date_to' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['fellowship'][$key]['date_to' . $key]));
      $fellowship -> type = $form_state['values']['fellowship'][$key]['type' . $key];
      $fellowship -> institution = $form_state['values']['fellowship'][$key]['institution' . $key];
      $fellowship -> city = $form_state['values']['fellowship'][$key]['city' . $key];
      $fellowship -> state = $form_state['values']['fellowship'][$key]['state' . $key];
      $fellowship -> country = $form_state['values']['fellowship'][$key]['country' . $key];
      $fellowship -> date_from = $form_state['values']['fellowship'][$key]['date_from' . $key];
      $fellowship -> date_to = $form_state['values']['fellowship'][$key]['date_to' . $key];
      $fellowship -> prog_dir = $form_state['values']['fellowship'][$key]['prog_dir' . $key];

      db_insert('vss_residency') -> fields(array(
        'uid' => $fellowship -> uid,
        'type' => $fellowship -> type,
        'institution' => $fellowship -> institution,
        'city' => $fellowship -> city,
        'state' => $fellowship -> state,
        'country' => $fellowship -> country,
        'date_from' => $fellowship -> date_from,
        'date_to' => $fellowship -> date_to,
        'prog_dir' => $fellowship -> prog_dir,
      )) -> execute();
    }
    /*
     * Update the vss_drupal_flags table by setting the residency
     * status flag, letting us know that the form has been filled out.
     */
    db_update('vss_drupal_flags	') -> fields(array('residency' => 1, )) -> condition('uid', $user -> uid) -> execute();
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/affiliations' . $user -> uid);
  }

  /*
   * Ajax callback for the residency and fellowship forms
   */

  function vistaportal_add_residency_callback($form, $form_state) {
    return $form['residency'];
  }

  function vistaportal_add_fellowship_callback($form, $form_state) {
    return $form['fellowship'];
  }

  /*
   * Increment the residency counter when the button is pressed
   */

  function vistaportal_residency_form_add($form, &$form_state) {
    $form_state['num_res']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the residency counter when the button is pressed
   */

  function vistaportal_residency_form_remove($form, &$form_state) {
    if ($form_state['num_res'] > 1) {
      $form_state['num_res']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Increment the fellowship counter when the button is pressed
   */

  function vistaportal_fellowship_form_add($form, &$form_state) {
    $form_state['num_fellow']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the fellowship counter when the button is pressed
   */

  function vistaportal_fellowship_form_remove($form, &$form_state) {
    if ($form_state['num_fellow'] > 1) {
      $form_state['num_fellow']--;
    }
    $form_state['rebuild'] = TRUE;
  }

	/*
	 * Implements the afterbuild
	 */
	  function vistaportal_residency_form_afterbuild($form, &$form_state) {
    if ($form_state['values']['residency'][0]['na']) {
      unset($form['residency'][0]['type0']['#required'], 
      $form['residency'][0]['institution0']['#required'], 
      $form['residency'][0]['state0']['#required'], 
      $form['residency'][0]['city0']['#required'], 
      $form['residency'][0]['date_from0']['#required'],  
      $form['residency'][0]['date_to0']['#required'],  
      $form['residency'][0]['prog_dir0']['#required']);
    }
		if ($form_state['values']['fellowship'][0]['na']) {
      unset($form['fellowship'][0]['type0']['#required'], 
      $form['fellowship'][0]['institution0']['#required'], 
      $form['fellowship'][0]['state0']['#required'], 
      $form['fellowship'][0]['city0']['#required'], 
      $form['fellowship'][0]['date_from0']['#required'],  
      $form['fellowship'][0]['date_to0']['#required'],  
      $form['fellowship'][0]['prog_dir0']['#required']);
    }
		
    return $form;
  }

  function vistaportal_residency_previous($form, &$form_state){
	$user = user_load($form_state['uid']);
	drupal_goto('preapp/internship' . $user -> uid);
}	