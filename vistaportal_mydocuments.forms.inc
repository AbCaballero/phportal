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
    include_once('vistaportal_functions.inc');

    global $user;
    $id = $user->uid;
    $account = user_load($id);




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
$resumes = $account->data['resumeKeyValues'];

$list = array();

if(is_array($resumes) && (count($resumes) != 0)) {
  ksort($resumes);
  foreach ($resumes as $key => $value) {
      $list[] = vistaportal_download_link($value, $id);
  }

  $listarray['items'] = $list;
  $listarray['title'] = 'Uploaded CV';
  $listarray['type'] = "ul";
  $listarray['attributes'] = array();

  $form['mydocuments']['cv'] = array(
      '#prefix' => '<div class="docs-txt">',
      '#markup' => theme_item_list($listarray),
      '#suffix' => '</div>',
    );
}
else {
  $form['mydocuments']['cv'] = array(
      '#prefix' => '<div class="docs-txt">',
      '#markup' => t("<p><strong>Uploaded CV</strong></p><br><p>You have not uploaded any resume.</p>"),
      '#suffix' => '</div>',
    );
}


    return $form;
  }

?>