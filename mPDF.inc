<?php

/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: December 5th, 2012
 * Notes: This file contains the function that
 * renders the PDFs.
 */

function make_pdf_1($html_string, $formtype){
	dsm(getcwd());
	include_once('sites/all/Libraries/MPDF54/mpdf.php');
	global $user;
	$account = user_load($user->uid);
	$mpdf = new mPDF('utf-8', 'A4');
	$mpdf->setFooter("$account->name - {DATE m-j-Y h:i:s A}||page {PAGENO} of {nb}");
  $mpdf->setBasePath("sites/all/modules/vistaportal/pdf_html_strings");
  $mpdf->allow_charset_conversion=true;  // Set by default to TRUE
  $mpdf->charset_in='windows-1252';
  $mpdf -> WriteHTML($html_string);
  $id = $user->uid;
    $directorypath = drupal_realpath('public://') . "/pdf/$id/";
    if (is_dir($directorypath) === true) {
      $filename = $directorypath . $id . '_' . $formtype . '_' . time() . '.pdf';
    }
    else {
      $path = mkdir($directorypath, 0777, true);
      $filename = $directorypath . $id . '_' . $formtype . '_' . time() . '.pdf';
    }
    $mpdf -> Output($filename);

return $filename;
}
