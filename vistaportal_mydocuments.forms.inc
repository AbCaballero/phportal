<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: January 7th, 2012
   * Notes: This file contains the markup for the
   * 'Why Apply' page.
   */

  function vistaportal_mydocuments_form($form, &$form_state) {
  	include_once('vistaportal.fields.inc');

    global $user;
    $id = $user->uid;
  	$form = array();
    $form['mydocuments'] = array(
      '#type' => 'fieldset',
      //'#title' => t('My Documents?'),
      '#collapsible' => FALSE,
    );
		$form['mydocuments']['title'] = array(
		  '#prefix' => '<div class="docs-header">',
      '#markup' => t("<h2>Copies of your submitted application forms and uploaded documents.</h2>"),
      '#suffix' => '</div>',
    );
		$form['mydocuments']['docs'] = array(
		  '#prefix' => '<div class="docs-txt">',
      '#markup' => t("<p><strong>Physician Application Step 1</strong></p><br><ul><li><a href = \"downloadfile/$id/PreApplication.pdf\">PreApplication.pdf</a></li><li><a href = \"downloadfile/$id/AuthorizationRelease.pdf\">Release_and_Authorization.pdf<a></li></ul>"),
      '#suffix' => '</div>',
    );

		$form['mydocuments']['cv'] = array(
		  '#prefix' => '<div class="docs-txt">',
      '#markup' => t("<p><strong>Uploaded CV</strong></p><br><ul><li>Megan_johnson_2012_CV.pdf</li></ul>"),
      '#suffix' => '</div>',
    );

    return $form;
  }

?>