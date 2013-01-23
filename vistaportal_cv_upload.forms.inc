<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: January 8th, 2013
   * Notes: This file contains the cv upload section of the
   * physicians pre-application form.
   */

  /*
   * This is the form callback for the vistaportal_cv_upload_form.
   */

  function vistaportal_cv_upload_form($form, &$form_state) {
    include_once ('vistaportal.fields.inc');
    include_once ('vistaportal_functions.inc');
    global $user;
    $account = user_load($user->uid);

    $form['#tree'] = TRUE;
    $form = array();
    $form['upload'] = array(
      '#type' => 'fieldset',
      '#title' => t('Upload CV'),
      '#collapsible' => FALSE,
    );

    $form['upload']['desc'] = array('#markup' => t("<h4>CURRICULUM VITAE (OPTIONAL)</h4>
    <p>We're sure we've only scratched the surface and there is much more to know about your<br>
     career to date. Please upload a current CV.</p><br><br>"), );
    /*$form['submit']= array(
     '#type' => 'submit',
     '#value' => t('Upload'),
     '#attributes' => array('class' => array('submit-upload')),
     );*/
    /* $form['upload']['cv'] = array(
     '#type' => 'file',
     '#title' => t('Choose a file'),
     '#title_display' => 'Upload CV:',
     '#description' => t('Acceptable formats are .pdf, .jpg, and .doc.'),
     //'#size' => 22,
     '#theme_wrappers' => array(),
     //'#weight' => -10,
     );*/

    $form['upload']['cv'] = array(
      '#type' => 'file',
      '#name' => 'files[cv]',
      '#title' => t('Upload CV:'),
      '#value' => t('Upload'),
      '#size' => 45,
      '#description' => t('Acceptable formats are .pdf, .jpg, .doc and .docx.'),
      '#attributes' => array('multiple' => 'multiple'),
      '#upload_validators' => array('file_validate_extensions' => array('pdf, .jpg, .doc, .docx'),
        //'#image'=> "./theme/jobapp/img/file_upload.png",
      )
    );
    $form['upload']['submit'] = array(
      '#prefix' => '<div id="upload-btn">',
      '#type' => 'submit',
      '#value' => t('Upload'),
      '#suffix' => '</div>',
    );


    // Display the link for the existing resumes
    $resumes = $account->data['resumeKeyValues'];

    $list = array();

if(is_array($resumes)) {
  ksort($resumes);
  foreach ($resumes as $key => $value) {
      $list[] = vistaportal_download_link_withremove($value, $user->uid);
  }

  $listarray['items'] = $list;
  $listarray['title'] = 'Uploaded CV';
  $listarray['type'] = "ul";
  $listarray['attributes'] = array();

  $form['upload']['cvlist'] = array(
      '#prefix' => '<div class="docs-txt">',
      '#markup' => theme_item_list($listarray),
      '#suffix' => '</div>',
    );


}

    //$form['upload']['formats'] = array('#markup' => t('Acceptable formats are .pdf, .jpg, and .doc.'), );
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
    $form['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save & Next'),
      '#name' => 'next',
      '#submit' => array('vistaportal_cv_upload_form_submit'),
      '#attributes' => array('class' => array('affiliations-submit')),
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
      '#submit' => array('vistaportal_upload_previous'),
    );
    $form['prev']['#attributes'] = array('class' => array('prev'));
    return $form;
  }

  /*
   * This is the form submission callback for the vistaportal_cv_upload_form
   */

  function vistaportal_cv_upload_form_submit($form, &$form_state) {

    global $user;

    $result = db_query("SELECT entity_id FROM {vss_profile_data} WHERE uid = :uid", array(':uid' => $user -> uid));
    $entityid = null;
    foreach ($result as $entityid) {
      $entityid = $entityid;
    }
    $entityid = $user -> uid;
    $account = user_load($entityid);

    $ftpRootdocspath = variable_get('vistadocsrootpath', '/docs/Vistaportalfiles');

    if (isset($_FILES['files']) && is_uploaded_file($_FILES['files']['tmp_name']['cv'])) {
      $source_file = $_FILES['files']['tmp_name']['cv'];
      $timeuploaded = time();
      $destination_file = $timeuploaded . '_' . $_FILES['files']['name']['cv'];

      $Stream = ftp_connect(variable_get("ftpserver", "oasslcftp02"));
      ftp_login($Stream, variable_get("ftpuser", "applyVista_dev"), variable_get("ftppass", "pw4drup@lFTP"));

      //Check if a directory exists for this entityid, if not create one
      $docsDirectory = $ftpRootdocspath . '/' . $entityid;
      if (!@ftp_chdir($Stream, $docsDirectory)) {
        if (ftp_mkdir($Stream, $docsDirectory) == FALSE) {
          drupal_set_message(t("An error has occurred while saving your document, please try again later"), 'error');
          ftp_close($Stream);
          exit ;
        }
      }

      //Copying the file to the server
      if (!ftp_put($Stream, $docsDirectory . '/' . $destination_file, $source_file, FTP_BINARY)) {
        drupal_set_message(t("An error has occurred, please try again later"), 'error');
      }
      else {
        $resumes[$timeuploaded] = $destination_file;
        $account = user_save($account, array('data' => array('resumeKeyValues' => $resumes)));
        drupal_set_message(t("Your file has been successfully uploaded to the server"));
      }
      ftp_close($Stream);
    }

    //$user = user_load($form_state['uid']);
    drupal_goto('preapp/release');
  }

  function vistaportal_upload_previous($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('preapp/references' . $user -> uid);
  }
