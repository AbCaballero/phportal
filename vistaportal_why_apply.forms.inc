<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: January 7th, 2012
   * Notes: This file contains the markup for the
   * 'Why Apply' page.
   */

  function vistaportal_why_apply_form($form, &$form_state) {
    $form['why_apply'] = array(
      '#type' => 'fieldset',
      '#title' => t('Why Apply?'),
      '#collapsible' => FALSE,
      '#markup' => "<p> When you complete Step 1 of our Application Process, we will have
      	enough information to begin to discussing potential locum tenens opportunities with
      	you. The most attractive opportunities are filled quickly, so the sooner we have
      	your information on file the better, as far as finding great assignments goes.</p><br />
      	<p>Step 1 gives you a secure, encrypted way to share your personal and professional
      	information, references, and CV, and an easy way to submit the release and authorization
      	we are required to collect.</p><br /><p>The process will take between 20 and 25 minutes. 
      	You can stop, start, save and update your information anytime you like.</p><br /><p>
      	After you have submitted Step 1, a professional recruiter well versed in your medical
      	specialty will contact you within 24 hours to help you complete the rest of the process, 
      	which includes a telephone interview, document collection and credentials review.</p><br />
      	<p><Strong>Ready? Let's get cracking.</strong></p>",
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('My Application'),
      '#submit' => array('vistaportal_why_apply_form_submit'),
      '#attributes' => array('class' => array('why-apply-submit')),
    );
    return $form;
  }

  function vistaportal_why_apply_form_submit($form, &$form_state) {
    $user = user_load($form_state['uid']);
    drupal_goto('register' . $user -> uid);
  }
