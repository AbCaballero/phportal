<?php

  /*
   This is the form callback for the exams form
   *
   */
  function vistaportal_exams_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    drupal_add_library('system', 'drupal.ajax');
    drupal_add_library('system', 'jquery.form');

    /*Set this to tree so we can access all dynamic form values*/

    $form['#tree'] = TRUE;
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));

    /*Exams taken fieldset*/

    $form['exams_taken'] = array(
      '#type' => 'fieldset',
      '#title' => t('EXAMS'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="exams-fieldset-wrapper">',
      '#suffix' => '</div>',
    );
    $form['exams_taken']['instructions'] = array('#markup' => t('<p>Please list all exams taken, including <strong>all steps or parts</strong>, 
    number of times taken, and scores for each exam. <strong>You must complete steps or parts in the right sequence.</strong></p>'), );
		$form['exams_taken']['top-line'] = array ( '#prefix' => '<div class="line-solid">','#suffix' => '</div>',);
    /*Ajax counter*/

    if (empty($form_state['exams_count'])) {
      $form_state['exams_count'] = 1;
    }

   
    

    for ($i = 0; $i < $form_state['exams_count']; $i++) {
      $j = $i + 1;
			if ($i > 0) {
        $form['exams_taken'][$i]['title-txt' . $i]['#prefix'] = '<div class="line-solid"></div><h2> Exam ' . ($i + 1) . '</h2><br/>';
      }	
			$form['exams_taken'][$i]['exam_name' . $i] = exam_name('Exam Name');
			$form['exams_taken'][$i]['exam_name' . $i]['#prefix'] = '<div class = "exam-name">' ;
			$form['exams_taken'][$i]['exam_name' . $i]['#suffix'] = '</div>' ;
      /*Select to add additional times an exam is taken*/
      $form['exams_taken'][$i]['times' . $i] = array(
        '#type' => 'select',
        '#title' => t('# of times<br>Taken'),
        '#required' => TRUE,
        '#options' => array(
          '1' => '1',
          '2' => '2',
          '3' => '3',
          '4' => '4',
          '5' => '5',
          '6' => '6',
          '7' => '7',
        ),
        '#limit_validation_errors' => array(),
        '#attributes' => array('class' => array('examtimes' . $i)),
      );
       $form['exams_taken'][$i]['times' . $i]['#title'] = '- Attempt 1';
			 
			 
     /* $exam_fields[$i]['date' . $i . $j] = array(
        '#type' => 'date',
        '#title' => t('Exam Date'),
        '#date_format' => 'm-Y',
        '#date_year_range' => '-30:+0',
        '#date_label_position' => 'within',
        '#required' => TRUE,
        '#attributes' => array('class' => array('examtimes' . $i . $j)),
      );*/
      
			$exam_fields[$i]['date' . $i]  = date_my('');
			$exam_fields[$i]['date' . $i]["#attributes"] = array('examtimes' . $i );
			$exam_fields[$i]['date' . $i]['#required'] = FALSE;
			//$exam_fields[$i]['date' . $i]['#title'] = 'Exam Date';
			

      $exam_fields[$i]['score' . $i] = array(
        '#type' => 'textfield',
        //'#title' => t('Score'),
        '#required' => TRUE,
        '#attributes' => array('class' => array('examtimes' . $i)),
      );
    }

    /*To add additional Pages*/

    $form['exams_taken']['exam_another'] = array(
      '#type' => 'submit',
      '#weight' =>1,
      '#value' => t('+ Add Additional Exam'),
      '#submit' => array('vistaportal_exams_add'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'vistaportal_exams_callback',
        'wrapper' => 'exams-fieldset-wrapper',
        'method' => 'replaceWith',
        'speed' => 'fast',
 
      ),
    );

    // To remove additional pages
    if ($form_state['exams_count'] > 1) {
      $form['exams_taken']['exam_remove'] = array(
        '#type' => 'submit',
        '#value' => t('- Remove Exam'),
        '#submit' => array('vistaportal_exams_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_exams_callback',
          'wrapper' => 'exams-fieldset-wrapper',
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

    /*State exams fieldset*/

    $form['exams_state_cntr'] = array(
      '#type' => 'fieldset',
      '#title' => t('State Exam'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="state-exams-fieldset-wrapper">',
      '#suffix' => '</div>',
    );
    $form['exams_state_cntr']['instructions']['#markup'] = t('<br/>Please list all state exams taken.<br/>');
    $form['exams_state_cntr']['not_applicable'] = checkbox('Not Applicable');
    unset($form['exams_state_cntr']['not_applicable']['#required']);

    if (empty($form_state['state-exams_count'])) {
      $form_state['state-exams_count'] = 1;
    }

    for ($i = 0; $i < $form_state['state-exams_count']; $i++) {
      $form['exams_state_cntr'][$i]['state' . $i] = state('State');
      $form['exams_state_cntr'][$i]['state_exam_date' . $i] = date_my('Exam Date');
      $form['exams_state_cntr'][$i]['result' . $i] = array(
        '#type' => 'radios',
        '#title' => 'Result',
        '#required' => TRUE,
        '#options' => drupal_map_assoc(array(
          t('Pass'),
          t('Fail')
        )),
      );
      // $form['exams_state_cntr'][$i]['set']['#title'] = 'Exam ' . ($i+1);
    }

    // To add additional pages
    $form['exams_state_cntr']['exam_another'] = array(
      '#type' => 'submit',
      '#value' => t('Add Additional State Exam'),
      '#submit' => array('vistaportal_state_exams_add'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'vistaportal_state_exams_callback',
        'wrapper' => 'state-exams-fieldset-wrapper',
        'method' => 'replaceWith',
        'speed' => 'fast',
      ),
    );

    //To remove additional pages
    if ($form_state['state-exams_count'] > 1) {
      $form['exams_state_cntr']['exam_remove'] = array(
        '#type' => 'submit',
        '#value' => t('Remove State Exam'),
        '#submit' => array('vistaportal_state_exams_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_state_exams_callback',
          'wrapper' => 'state-exams-fieldset-wrapper',
        ),
      );
    }


    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save & Next>'),
      '#name' => 'next',
      '#submit' => array('vistaportal_exams_form_submit'),
    );
    $form['save_logout'] = array(
      '#type' => 'submit',
      '#value' => t('Save & Logout'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button')),
      '#submit' => array('vistaportal_save_logout'),
    );

    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button prev prev')),
      '#submit' => array('vistaportal_exams_previous'),
    );

    $form['exams_taken']['et'] = vistaportal_set($exam_fields);
    return $form;
  }

  /*This function creates the field tree*/

  function vistaportal_set($sub_elements, $ct = 7) {
    $orig_elements = $sub_elements;
    $sub_elements['#tree'] = TRUE;
    $sub_elements['start'] = array('#weight' => -1000, );
    $sub_elements['end'] = array('#weight' => 1999, );

    $elements = array();
    for ($k = 1; $k <= $ct; $k++) {
      foreach ($sub_elements as $key => $value) {
        if ($k >= 2) {
          unset($sub_elements[$key]['#required']);
        }
      }
      $elements[] = $sub_elements;
    }
    return $elements;
  }
  
 /* function vistaportal_set($sub_elements, $ct = 7) {
  unset($sub_elements['system_meta_generator']);
	for ($k = 1; $k <= $ct; $k++) {
  foreach ($sub_elements as $key => $element) {
  if ($k >= 2) {
  if (isset($element['#required']['rel']) && $element['#required']['rel'] == 'shortlink') {
  unset($sub_elements[$key]);
	}
		}
}

}
}*/

  /*
   * Ajax callback for the exams form
   */
  function vistaportal_exams_callback($form, $form_state) {

    return $form['exams_taken'];
  }

  /*
   * Increment the counter when the button is pressed
   */
  function vistaportal_exams_add($form, &$form_state) {
    $form_state['exams_count']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the counter when the button is pressed
   */
  function vistaportal_exams_remove($form, &$form_state) {
    if ($form_state['exams_count'] > 1) {
      $form_state['exams_count']--;
    }
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Go to the previous page
   */
  function vistaportal_exams_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/certifications' . $user -> uid);
  }

/*
   * Ajax callback for the state-exams form
   */
  function vistaportal_state_exams_callback($form, $form_state) {

    return $form['exams_state_cntr'];
  }

  /*
   * Increment the counter when the button is pressed
   */
  function vistaportal_state_exams_add($form, &$form_state) {
    $form_state['state-exams_count']++;
    $form_state['rebuild'] = TRUE;
  }

  /*
   * Decrement the counter when the button is pressed
   */
  function vistaportal_state_exams_remove($form, &$form_state) {
    if ($form_state['state-exams_count'] > 1) {
      $form_state['state-exams_count']--;
    }
    $form_state['rebuild'] = TRUE;
  }  