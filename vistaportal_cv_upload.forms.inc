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


    $form = array();
    $form['upload'] = array(
      '#type' => 'fieldset',
      '#title' => t('Upload CV'),
      '#collapsible' => FALSE,
    );
    $form['upload']['desc'] = array('#markup' => t("<p><strong> CURRICULUM VITAE (OPTIONAL)</p></stong><p> We're sure we've only scratched the surface and there is much more to know about your career to date. Please upload a current CV.</p>"), );
    $form['upload']['cv'] = array(
      '#type' => 'file',
      '#title' => t('Choose a file'),
      '#title_display' => 'Upload CV:',
      '#size' => 22,
      '#theme_wrappers' => array(),
      '#weight' => -10,
    );
    $form['upload']['formats'] = array('#markup' => t('Acceptable formats are .pdf, .jpg, and .doc.'), );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Upload'),
      '#attributes' => array('class' => array('submit-upload')),
    );
    return $form;
  }

   /*
   * This is the form submission callback for the vistaportal_cv_upload_form
   */

  function vistaportal_cv_upload_form_submit($form, &$form_state) {

    $result = db_query("SELECT entity_id FROM {vss_profile_data} WHERE uid = :uid", array(':uid' => 153));
    $entityid = null;
    foreach ($result as $entityid) {
      $entityid = $entityid;
    }

    $ftpRootdocspath = variable_get('vistadocsrootpath', '/docs/Vistaportalfiles');

    if (isset($_FILES['files']) && is_uploaded_file($_FILES['files']['tmp_name']['cv'])) {
      $source_file = $_FILES['files']['tmp_name']['cv'];
      $destination_file = $_FILES['files']['name']['cv'];

      $Stream = ftp_connect(variable_get("ftpserver", "oasslcftp02"));
      ftp_login($Stream, variable_get("ftpuser", "applyVista_dev"), variable_get("ftppass", "pw4drup@lFTP"));

      //Check if a directory exists for this entityid, if not create one
      $docsDirectory = $ftpRootdocspath . '/' . $entityid;
      if (!@ftp_chdir($Stream, $docsDirectory)) {
        if (ftp_mkdir($Stream, $docsDirectory == FALSE)) {
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
        drupal_set_message(t("Your file has been successfully uploaded to the server"));
      }
      ftp_close($Stream);
    }
  }
