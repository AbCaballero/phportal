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
    /*add this css just for exams page*/
    drupal_add_css(path_to_theme() . '/css/exam-css.css', 'theme', 'all');

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
    $form['exams_taken']['top-line'] = array(
      '#prefix' => '<div class="line-solid">',
      '#suffix' => '</div>',
    );
    /*Ajax counter*/

    if (empty($form_state['exams_count'])) {
      $form_state['exams_count'] = 1;
    }


    for ($i = 0; $i < $form_state['exams_count']; $i++) {
      $j = $i + 1;
      if ($i > 0) {
        $form['exams_taken'][$i]['title-txt' . $i]['#prefix'] = '<h2> Exam ' . ($i + 1) . '</h2><br/>';
      }
      $form['exams_taken'][$i]['exam_name' . $i] = exam_name('Exam Name');
      $form['exams_taken'][$i]['exam_name' . $i]['#prefix'] = '<div class = "exam-name">';
      $form['exams_taken'][$i]['exam_name' . $i]['#suffix'] = '</div>';

      /*Select to add additional times an exam is taken*/

      $form['exams_taken'][$i]['times' . $i] = array(
        '#type' => 'select',
        '#title' => t('# of Times Taken'),
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
        '#default_value' => '1',
        '#limit_validation_errors' => array(),
        '#attributes' => array('examset' => array('examset' . $i)),
      );

      for ($j = 1; $j < 8; $j++) {
        $form['exams_taken'][$i]['date' . $i . $j] = ($j == 1) ? date_my('Exam Date') : date_my('');
        $form['exams_taken'][$i]['date' . $i . $j]['#prefix'] = '<div class = "attempt' . $i . $j . '"><h3>Attempt ' . $j . '</h3></div>';
        $form['exams_taken'][$i]['date' . $i . $j]['#attributes'] = array('class' => array('dates' . $i . $j));
        if ($j != 1)
          unset($form['exams_taken'][$i]['date' . $i . $j]['#required']);

        $form['exams_taken'][$i]['score' . $i . $j] = array(
          '#type' => 'textfield',
          '#title' => ($j == 1) ? t('Score') : t(''),
          '#required' => ($j == 1) ? TRUE : FALSE,
          '#attributes' => array('class' => array('scores' . $i . $j)),
        );
      }
    }

    /*To add additional Pages*/

    $form['exams_taken']['exam_another'] = array(
      '#type' => 'submit',
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
    $form['exams_state_cntr']['instructions']['#markup'] = t('Please list all state exams taken.');
    $form['exams_state_cntr']['not_applicable'] = checkbox('Not Applicable');
    unset($form['exams_state_cntr']['not_applicable']['#required']);

    if (empty($form_state['state-exams_count'])) {
      $form_state['state-exams_count'] = 1;
    }

    for ($i = 0; $i < $form_state['state-exams_count']; $i++) {
      $form['exams_state_cntr'][$i]['state' . $i] = state('State');
      $form['exams_state_cntr'][$i]['state' . $i]['#prefix'] = '<div id = "state-exam-state">';
      $form['exams_state_cntr'][$i]['state' . $i]['#suffix'] = '</div>';
      $form['exams_state_cntr'][$i]['state_exam_date' . $i] = date_my('Exam Date');
      $form['exams_state_cntr'][$i]['state_exam_date' . $i]['#prefix'] = '<div id = "state-exam-date">';
      $form['exams_state_cntr'][$i]['state_exam_date' . $i]['#suffix'] = '</div>';
      $form['exams_state_cntr'][$i]['result' . $i] = array(
        '#type' => 'radios',
        '#title' => 'Result',
        '#required' => TRUE,
        '#options' => drupal_map_assoc(array(
          t('Pass'),
          t('Fail')
        )),
      );
    }

    // To add additional pages
    $form['exams_state_cntr']['exam_another'] = array(
      '#type' => 'submit',
      '#value' => t('+ Add Additional State Exam'),
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
        '#value' => t('- Remove State Exam'),
        '#submit' => array('vistaportal_state_exams_remove'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'vistaportal_state_exams_callback',
          'wrapper' => 'state-exams-fieldset-wrapper',
        ),
      );
    }

    //this is a line at the bottom
    $form['last']['line'] = array(
      '#prefix' => '<div class="line_left">',
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
      '#submit' => array('vistaportal_exams_form_submit'),
      '#attributes' => array('class' => array('education-submit')),
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
      '#attributes' => array('class' => array('button prev')),
      '#submit' => array('vistaportal_exams_previous'),
    );
    $form['prev']['#attributes'] = array('class' => array('prev'));
    $form['#after_build'][] = 'vistaportal_exams_form_afterbuild';
    return $form;
  }



  /*
   This is the form submission callback for the exams form.
   */

  function vistaportal_exams_form_submit($form, &$form_state) {
    global $user;
    $account = user_load($user -> uid);

    /* Save the form values to the exams table in
     * the database and set the flag in the drupal_flags
     * table. If the user refills this form, we unset and
     * then reset the exams status flag in the drupal_flags table.
     * We also overwrite any existing data in the exams table.
     */

    db_update('vss_drupal_flags') -> fields(array('exams' => 0, )) -> condition('uid', $user -> uid) -> execute();

    db_delete('vss_exams') -> condition('uid', $user -> uid) -> execute();

    /*Insert the form_state values into the exams table.*/

    $exams = new stdClass();
    unset($form_state['values']['exams_taken']['exam_another'], $form_state['values']['exams_taken']['exam_remove'], $form_state['values']['exams_taken']['instructions'], $form_state['values']['exams_taken']['top-line']);
    foreach ($form_state['values']['exams_taken'] AS $key => $value) {
      $exams -> uid = $user -> uid;
      $exams -> name = $form_state['values']['exams_taken'][$key]['exam_name' . $key];
      $exams -> times = $form_state['values']['exams_taken'][$key]['times' . $key];
      unset($form_state['values']['exams_taken'][$key]['exam_name' . $key]);
      unset($form_state['values']['exams_taken'][$key]['times' . $key]);
      for ($j = 1; $j < 8; $j++) {
        	if(!empty($form_state['values']['exams_taken'][$key]['date' . $key . $j])){
          $form_state['values']['exams_taken'][$key]['date' . $key . $j] = date('Y-m-d H:i:s', strtotime($form_state['values']['exams_taken'][$key]['date' . $key . $j]));
          $exams -> date_taken = $form_state['values']['exams_taken'][$key]['date' . $key . $j];
          $exams -> score = $form_state['values']['exams_taken'][$key]['score' . $key . $j];
          db_insert('vss_exams') -> fields(array(
            'uid' => $exams -> uid,
            'title' => $exams -> name,
            'times' => $exams -> times,
            'date_taken' => $exams -> date_taken,
            'result' => $exams -> score,
          )) -> execute();
        }
      }
    }
    db_update('vss_drupal_flags') -> fields(array('exams' => 1, )) -> condition('uid', $user -> uid) -> execute();

    db_update('vss_drupal_flags') -> fields(array('state_exams' => 0, )) -> condition('uid', $user -> uid) -> execute();

    db_delete('vss_state_exams') -> condition('uid', $user -> uid) -> execute();

    $state_exams = new stdClass();
    unset($form_state['values']['exams_state_cntr']['instructions'], $form_state['values']['exams_state_cntr']['not_applicable'], $form_state['values']['exams_state_cntr']['exam_another'], $form_state['values']['exams_state_cntr']['exam_remove']);
    foreach ($form_state['values']['exams_state_cntr'] AS $key => $value) {
      $form_state['values']['exams_state_cntr'][$key]['state_exam_date' . $key] = date('Y-m-d H:i:s', strtotime($form_state['values']['exams_state_cntr'][$key]['state_exam_date' . $key]));
      $state_exams -> state = $form_state['values']['exams_state_cntr'][$key]['state' . $key];
      $state_exams -> date_taken = $form_state['values']['exams_state_cntr'][$key]['state_exam_date' . $key];
      $state_exams -> result = $form_state['values']['exams_state_cntr'][$key]['result' . $key];
      db_insert('vss_state_exams') -> fields(array(
        'uid' => $user -> uid,
        'state' => $state_exams -> state,
        'date_taken' => $state_exams -> date_taken,
        'result' => $state_exams -> result,
      )) -> execute();
    }

    db_update('vss_drupal_flags') -> fields(array('state_exams' => 1, )) -> condition('uid', $user -> uid) -> execute();
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/licensure' . $user -> uid);
  }


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


  /*
   * Implements the afterbuild
   */
  function vistaportal_exams_form_afterbuild($form, &$form_state) {
    if ($form_state['values']['exams_state_cntr']['not_applicable']) {
      unset($form['exams_state_cntr'][0]['state0'], 
      $form['exams_state_cntr'][0]['state_exam_date0'],
			$form['exams_state_cntr'][0]['result0']);
    }
    return $form;
  }

