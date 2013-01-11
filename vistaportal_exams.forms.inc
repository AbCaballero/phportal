<?php
/*
This is the form callback for the exams form
 * 
 */
function vistaportal_exams_form($form, &$form_state){
    include_once('vistaportal.fields.inc');
    include_once('vistaportal_functions.inc');  
    $form = array();
    $form['exams'] = array(
        '#type'=>'fieldset',
        '#title' => t('Exams'),
        '#collapsible' => FALSE,
    );
    $form['exams']['exam_name'] = exam('Exam Name');
    $form['exams']['other_exam_name'] = array(
        '#type' => 'textfield',
        '#title' => t('License exam name'),
        '#required' => TRUE,
        '#states' => array(
        'visible'=> array(
          ':input[name="exam_name"]' => array('value' => 'Other'),
    )));
    //$form['exams']['exam_num_times'] = exam_num_times('# of Times Taken');
    $form['exams']['exam_date'] = date_my('Exam Date');
    $form['exams']['score'] = textfield('Score');
   /* $form['exams']['attempt2_score'] = array(
        '#type' => 'date_my',
        '#title' => t('Exam Date'),
        '#required' => TRUE,
        '#states' => array(
        'visible'=> array(
          ':input[name="exam_num_times"]' => array('value' => '2'),
    )));
    $form['exams']['attempt2_date'] = array(
        '#type' => 'textfield',
        '#title' => t('Score'),
        '#required' => TRUE,
        '#states' => array(
        'visible'=> array(
          ':input[name="exam_num_times"]' => array('value' => '2'),
    )));*/
    $form['exams']['state'] = state('State');
    $form['exams']['state_exam_date'] = date_my('Exam Date');
    $form['exams']['result'] = array(
        '#type' => 'radios',
        '#title' => 'Result',
        '#required' => TRUE,
        '#options' => drupal_map_assoc(array(t('Pass'), t('Fail'))),
    ); 
    
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save & Continue'),
        '#name' => 'next',
        '#submit' => array('vistaportal_exams_form_submit'),
    );
    $form['prev'] = button('Previous');
    $form['save_logout'] = button('Save & Logout');
  return $form;
}


/*
 * This is the form submission callback for the exams form.
 */
function vistaportal_exams_form_submit($form, &$form){
    global $user;
    $account = user_load($user -> uid);
    
/* If the user refills this form, we need to unset the
 * exams status flag in the vss_drupal_flags table.    
 */
    db_update('vss_drupal_flags ')
        ->fields(array(
            'exams'=>0,
    ))
        ->condition('uid', $user->uid)
        ->execute();
        
        
/*Overwrite any existing values in the exams table.*/
    db_delete('vss_exams')
        ->condition('uid', $user->uid)
        ->execute();        

/*Insert the form_state values into the exams table.*/  
    $exams = new stdClass();
    $exams->uid = $user->uid;
    $exams->exam_name = $form_state['values']['exam_name'];
    $exams->other_exam_name = $form_state['values']['other_exam_name'];    
    $exams->exam_num_times = $form_state['values']['exam_num_times'];    
    $exams->exam_date = $form_state['values']['exams']['exam_date'] = date('Y-m-d H:i:s', strtotime($form_state['values']['exams']['exam_date']));
    $exams->score = $form_state['values']['score'];
    //$exams->attempt2_date = $form_state['values']['attempt2_date'];
    //$exams->attempt2_score = $form_state['values']['attempt2_score'];
    $exams->state = $form_state['values']['state'];
    $exams->state_exam_date = $form_state['values']['exams']['state_exam_date'] = date('Y-m-d H:i:s', strtotime($form_state['values']['exams']['state_exam_date']));
    $exams->result = $form_state['values']['result'];
    
    
    db_insert('vss_exams')
        ->fields(array(
            'uid' => $exams->uid,
            'exam_name' => $exams->exam_name,
            'other_exam_name' => $exams->other_exam_name,
            'exam_num_times' => $exams->exam_num_times,
            'exam_date' => $exams->exam_date,
            'score' => $exams->score,
            //'attempt2_date' => $exams->attempt2_date,
            //'attempt2_score' => $exams->attempt2_score,
            'state' => $exams->state,
            'state_exam_date' => $exam->state_exam_date,
            'result' => $exam->result,
    ))
        ->execute();

/*
 * Update the vss_drupal_flags table by setting the exams 
 * status flag, letting us know that the form has been filled out.
 */     
    db_update('vss_drupal_flags ')
        ->fields(array(
            'exams'=>1,
    ))
        ->condition('uid', $user->uid)
        ->execute();            
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/licensure' . $user->uid);  
     
}



