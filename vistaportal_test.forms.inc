<?php
  /**
   * Author: Andrew Browning
   * Company: Aner Group
   * Client: Vista Staffing Solutions
   * Date: December 14th, 2012
   * Notes: This file contains is the submit page.
   */

  /*
   * Form callback for the submit form.
   */
  function vistaportal_submit_form($form, &$form_state) {
    $form = array();
    $form['#attributes'] = array('enctype' => array("multipart/form-data"));
    $form['foo'] = array(
      '#type' => 'fieldset',
      //'#title' => t('Submission'),
      '#collapsible' => FALSE,
      '#prefix' => '<div id="submission-fieldset-wrapper">',
      '#suffix' => '</div>',
    );
    $form['foo']['text'] = array(
      '#prefix' => '<div id="submit-page">',
      '#markup' => t("<h1>Are you ready to submit your step 1 of your application?</h1><br>
      <p>Congratulations! Please click on the submit button below. Your <br>
      application will be sent immediately to a physician recruiter<br>
      assigned to your medical specialty. He or she will review your file <br>
      and be in contact within one business day to discuss your specific <br>
      interests and our current openings.</p>"),
      '#suffix' => '</div>',
    );
    //This is the line separator
    $form['foo']['line3'] = array(
      '#prefix' => '<div class="line-solid-submit">',
      //'#markup' => '<hr>',
      '#suffix' => '</div>',
    );

    $form['foo']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#submit' => array('vistaportal_submit_form_submit'),
      '#attributes' => array('class' => array('education-submit'))
    );
    $form['foo']['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('button prev prev')),
      '#submit' => array('vistaportal_submit_previous'),
    );
    $form['foo']['prev']['#attributes'] = array('class' => array('prev'));
    return $form;
  }

  /*
   * Submission call back for the vistaportal_submit_form
   */
  function vistaportal_submit_form_submit($form, &$form_state) {
   	include_once('mPDF.inc');
     include_once('ghostscript.inc');
     global $user;
     $id = $user->uid;

    $identitystring = get_identity_info($id);
    $premedstring = get_premed_info($id);
    $medstring = get_med_info($id);
    $internstring = get_internship_info($id);
    $residencystring = get_residency_info($id);
    $affiliationsstring = get_affiliations_info($id);
    $certificationstring = get_certifications_info($id);
		$addcertificationsstring = get_additional_certifications_info($id);
		$licensurestring = get_licensure_info($id);
    $licensesstring = get_licenses_info($id);
		$dearegstring = get_deareg_info($id);
    $disciplianrystring = get_disciplinary_info($id);
    $referencesstring = get_references_info($id);
    $examsstring = get_exams_info($id);

$closetags = '</div>
</body>
</html>';

$html_string = $identitystring . $premedstring . $medstring . $internstring . $residencystring . $affiliationsstring . $certificationstring. $addcertificationsstring . $examsstring . $licensurestring . $licensesstring . $dearegstring . $disciplianrystring . $referencesstring . $closetags;

     $filename = make_pdf_1($html_string); 
     include_once 'utilities/ftpupload.inc';
     uploadtoFTP($filename, "PreApplication.pdf", $id);
     $tiff = pdf_to_tiff($filename);
     uploadtoFTP($tiff, "PreApplication.tiff", $id);

    $getRealaseauthstring = get_Releaseauth_info($id);

    uploadtoFTP(make_pdf_1($getRealaseauthstring), "AuthorizationRelease.pdf", $id);

    drupal_goto('preapp/submitted');
  }

  /*function vistaportal_submit_form_submit($form, &$form_state) {
   $user = user_load($form_state['uid']);
   drupal_goto('register' . $user -> uid);
   }*/

  /*function vistaportal_submission_form_submit(){
   include_once('mPDF.inc');
   include_once('ghostscript.inc');
   $file = "/var/www/html/devapply.vistastaff.com/sites/default/files/pdf/foo.html";
   $html_string = file_get_contents($file);
   $filename = make_pdf_1($html_string);
   $tiff = pdf_to_tiff();
   }*/

  function vistaportal_submit_previous($form, &$form_state) {
    global $user;
    drupal_goto('preapp/release' . $user -> uid);
  }

  function get_identity_info($userid) {

    include_once 'pdf_html_strings/preapp_personal.inc';


    $query = db_select('vss_identity', 'iden');
    $query -> condition('iden.uid', $userid, '=')
    ->fields('iden');
    $results = $query -> execute();
    foreach ($results AS $result) {
      $lastname = $result -> last_name;
      $firstname = $result -> first_name;
      $middleinit = $result -> middle_init;
      $address1 = $result -> address;
      $City = $result -> city;
      $State = $result -> state;
      $zip = $result -> zip;
      $phone_choice = $result -> phone_choice;
      $phone = $result -> phone;
      $email = $result -> email;
      $dob = $result -> dob;
      $birth_city = $result -> birth_city;
      $birth_state = $result -> birth_state;
      $birth_country = $result -> birth_country;
      $eligibility = $result -> verification;
      $maritalstatus = $result -> marital_status;
      $spouse = $result -> spouse;
      $children = $result -> number_children;
    }
$personalinfo = get_personalinfoString(date('d/M/YYY'), $firstname, $lastname, $middleinit, $phone_choice, $phone, $email, $address1, $City, $State, $zip, $eligibility, $maritalstatus, $spouse, $children);

return $personalinfo;
  }

  function get_premed_info($userid) {
    include_once 'pdf_html_strings/preapp_premed.inc';
    $premedinfo = '';
    $query = db_select('vss_premed', 'p');
    $query -> condition('p.uid', $userid, '=');
    $query -> fields('p');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {

      $school = $result -> school;
      $degree = $result -> degree;
      $city = $result -> city;
      $country = $result -> country;
      $state = $result->state;
      $date_from = $result -> date_from;
      $date_to = $result -> date_to;

      $premedinfo .= get_premedString($counter, $school, $city, $state, $country, $date_from, $date_to, $degree);
      $counter++;
    }

return $premedinfo;

  }

  function get_med_info($userid) {
include_once 'pdf_html_strings/preapp_medical.inc';
    $medinfo = '';
    $query = db_select('vss_medschool', 'm');
    $query -> condition('m.uid', $userid, '=');
    $query -> fields('m');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {

     $school = $result -> school;
      $degree = $result -> degree;
      $city = $result -> city;
      $country = $result -> country;
      $date_from = $result -> date_from;
      $date_to = $result -> date_to;
      $ecfmg = $result -> ecfmg;
      $state = $result->state;


      $medinfo .= get_medString($counter, $school, $city, $state, $country, $date_from, $date_to, $degree);
      $counter++;
    }

return $medinfo;
  }

  function get_internship_info($userid) {
    include_once 'pdf_html_strings/preapp_internship.inc';

    $interninfo = "";
    $query = db_select('vss_internship', 'i');
    $query -> condition('i.uid', $userid, '=');
    $query -> fields('i');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {
      $type = $result -> type;
      $institution = $result -> institution;
      $city = $result -> city;
      $state = $result -> state;
      $country = $result -> country;
      $date_from = $result -> date_from;
      $date_to = $result -> date_to;
      $prog_dir = $result -> prog_dir;

      $interninfo .= get_internshipString($counter, $type, $institution, $City, $state, $country, $from, $to, $director);
      $counter++;
    }
return $interninfo;
  }

  function get_residency_info($userid) {
include_once 'pdf_html_strings/preapp_residency.inc';

    $residencyinfo = "";
     $query = db_select('vss_residency', 'r');
    $query -> condition('r.uid', $userid, '=');
    $query -> fields('r');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {
      $type = $result -> type;
      $institution = $result -> institution;
      $City = $result -> city;
      $state = $result -> state;
      $country = $result -> country;
      $date_from = $result -> date_from;
      $date_to = $result -> date_to;
      $prog_dir = $result -> prog_dir;

       $residencyinfo .= get_residencyString($counter, $type, $institution, $City, $state, $country, $date_from, $date_to, $director);
      $counter++;
    }


return $residencyinfo;
  }

  function get_affiliations_info($userid) {
include_once 'pdf_html_strings/preapp_affiliations.inc';

$affiliationsinfo = "";

$query = db_select('vss_affiliations', 'a');
    $query -> condition('a.uid', $userid, '=');
    $query -> fields('a');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {
      $facility = $result -> facility;
      $address1 = $result -> address;
      $city = $result -> city;
      $state = $result -> state;
      $zip = $result -> zip;
      $date_from = $result -> date_from;
      $date_to = $result -> date_to;
      $country = $result -> country;
      $capacity = $result -> capacity;

      $affiliationsinfo .= get_affiliationsString($counter, $facility, $address1, $city, $state, $zip, $country, $capacity, $date_from, $date_to);
      $counter++;
    }
return $affiliationsinfo;

  }

  function get_certifications_info($userid) {
  	include_once 'pdf_html_strings/preapp_certifications.inc';
		$certificationsinfo = '';
    $query = db_select('vss_certifications', 'c');
    $query -> condition('c.uid', $userid, '=');
    $query -> fields('c');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {
      $board_status = $result -> board_status;
      $board = $result -> board;
      $board_exp_date = $result -> board_exp_date;
      $cert_num = $result -> cert_num;
      $cert_recert = $result -> cert_recert;
      $certificationsinfo .= get_certificationsString($counter, $board_status, $board, $board_exp_date, $certnum, $cert_recert);
      $counter++;
    }
    return $certificationsinfo;
  }

  function get_licenses_info($userid) {
  	include_once 'pdf_html_strings/preapp_licenses.inc';
		$licenseinfo = '';
    $query = db_select('vss_licenses', 'l');
    $query -> condition('l.uid', $userid, '=');
    $query -> fields('l');
    $results = $query -> execute();
		$counter = 1;
    foreach ($results AS $result) {
      $lic_type = $result -> lic_type;
      $country = $result -> country;
      $state = $result -> state;
      $lic_number = $result -> lic_number;
      $date_issued = $result -> date_issued;
      $date_expired = $result -> date_expired;
      $original_state_license = $result -> original_state_license;
      $licenseinfo .= get_licensureString($counter, $lic_type, $country, $state, $lic_number, $date_issued, $date_expired, $original_state_license);
      $counter++;
    }
    return $licenseinfo;
  }


  function get_disciplinary_info($userid) {
  	include_once 'pdf_html_strings/preapp_disciplinary.inc';
		$disciplinaryinfo = '';
    $query = db_select('vss_disciplinary', 'd');
    $query -> condition('d.uid', $userid, '=');
    $query -> fields('d');
    $results = $query -> execute();
    foreach ($results AS $result) {
      $med_lic = $result -> med_lic;
      $other_lic = $result -> other_lic;
      $dea_reg = $result -> dea_reg;
      $academic_apt = $result -> academic_apt;
      $med_staff_apt = $result -> med_staff_apt;
      $clinical_priv = $result -> clinical_priv;
      $perogatives = $result -> perogatives;
      $affiliation = $result -> affiliation;
      $board_cert = $result -> board_cert;
      $pro_office = $result -> pro_office;
      $other_sanction = $result -> other_sanction;
      $convicted = $result -> convicted;
      $malpractice = $result -> malpractice;
      $insurance = $result -> insurance;
      $med_condition = $result -> med_condition;
      $treatment = $result -> treatment;
      $other = $result -> other;

      $disciplinaryinfo = get_disciplinaryString($med_lic, $other_lic, $dea_reg, $academic_apt, $med_staff_apt, $clinical_priv, $perogatives, $affiliation, $board_cert, $pro_office, $other_sanction, $convicted, $malpractice, $insurance, $med_condition, $treatment, $other);
    }
    return $disciplinaryinfo;
  }

  function get_references_info($userid) {
  	include_once 'pdf_html_strings/preapp_references.inc';
  	$referencesinfo = '';
  	include_once 'pdf_html_strings/preapp_references.inc';
    $query = db_select('vss_references', 'r');
    $query -> condition('r.uid', $userid, '=');
    $query -> fields('r');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {
      $name = $result -> name;
      $association = $result -> association;
      $specialty = $result -> specialty;
      $email = $result -> email;
      $phone_num = $result -> phone_num;

      $referencesinfo .= get_referencesString($counter, $name, $association, $specialty, $email, $phone_num);
      $counter++;
    }
    return $referencesinfo;
  }

  function get_licensure_info($userid) {
  	include_once 'pdf_html_strings/preapp_licensure.inc';
  	$licensureinfo = '';
    $query = db_select('vss_licensure', 'l');
    $query -> condition('l.uid', $userid, '=');
    $query -> fields('l');
    $results = $query -> execute();
    foreach ($results AS $result) {
      $fcvs = $result -> fcvs;
      $language_spoken = $result -> language_spoken;
      $licensureinfo = get_addcertificationsString($fcvs, $language_spoken);
    }
    return $licensureinfo;
  }

  function get_deareg_info($userid) {
  	include_once 'pdf_html_strings/preapp_deareg.inc';
  	$deareginfo = '';
    $query = db_select('vss_deareg', 'd');
    $query -> condition('d.uid', $userid, '=');
    $query -> fields('d');
    $results = $query -> execute();
		$counter = 1;
    foreach ($results AS $result) {
      $pending = $result -> pending;
      $country = $result -> country;
      $lic_number = $result -> lic_number;
      $date_issued = $result -> date_issued;
      $date_expired = $result -> date_expired;
      $schedule_2 = $result -> schedule_2;
      $schedule_3 = $result -> schedule_3;
      $schedule_4 = $result -> schedule_4;
      $schedule_5 = $result -> schedule_5;
      $schedule_2n = $result -> schedule_2n;
      $schedule_3n = $result -> schedule_3n;
      $language = $result -> language;
      $deareginfo .= get_dearegString($counter, $pending, $country, $lic_num, $date_issued, $date_expired, $schedule_2, $schedule_3, $schedule_4, $schedule_5, $schedule_2n, $schedule_3n, $language);
      $counter++;
    }
    return $deareginfo;
  }

  function get_additional_certifications_info($userid) {
  	include_once 'pdf_html_strings/preapp_add_certifications.inc';
		$addcertificationsinfo = '';
    $query = db_select('vss_additional_certifications', 'a');
    $query -> condition('a.uid', $userid, '=');
    $query -> fields('a');
    $results = $query -> execute();
    $counter = 1;
    foreach ($results AS $result) {
      $type = $result -> type;
      $cert_name = $result -> cert_name;
      $exp_date = $result -> exp_date;
      $cert_num = $result -> cert_num;
      $ecfmg = $result -> ecfmg;
      $ecfmg_ecp_date = $result -> ecfmg_exp_date;
      $addcertificationsinfo .= get_addcertificationsString($counter, $board_status, $board, $board_exp_date, $certnum, $cert_recert);
      $counter++;
    }
    return $addcertificationsinfo;
  }

  function get_exams_info($userid) {	
    include_once 'pdf_html_strings/preapp_exams.inc';
    $addexamsinfo = '<div id="exam">
<h3>Exam</h3>
<p>Please list all exams taken, including all steps or parts, number of times taken, and
scores for each exam. You must complete steps or parts in the right sequence.</p>
</div>';
    $query = db_select('vss_exams', 'e');
    $query -> condition('e.uid', $userid, '=');
    $query -> fields('e');
    $results = $query -> execute();
    $counter = 1;

    $previousexam = '';
    foreach ($results AS $result) {
      $title = $result -> title;
      $times = $result -> times;
      $taken = $result -> date_taken;
      $score = $result -> result;

      if ((strcasecmp($previousexam, $title) != 0)) {
        $addexamsinfo .= "<div id=\"exam$counter\">
<ul>
<li id=\"bold\">Exam $counter</li>
<li>Exam Name: $title</li>
<li># of Times Taken: $times</li>";
        $previousexam = $title;
        $attemptcounter = 1;
      }

      if ($attemptcounter != ($times + 1)) {
        $addexamsinfo .= "<li>Attempt $attemptcounter: $taken, score $score</li>";
        $attemptcounter++;
      }

      if ($attemptcounter == ($times + 1)) {
        $addexamsinfo .= "</ul>
</div>";
        $counter++;
      }

    }

  function get_Releaseauth_info($userid) {
include_once 'pdf_html_strings/preapp_authorization.inc';

return get_authrealeaseString();

  }
  }