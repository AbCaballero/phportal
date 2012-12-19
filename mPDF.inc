<?php

/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: December 5th, 2012
 * Notes: This file contains the function that
 * renders the PDFs.
 */

/*function make_pdf_1($html_string, $formtype){
	dsm(getcwd());
	define('_MPDF_PATH','sites/all/libraries/MPDF54/');
	include_once(_MPDF_PATH . "mpdf.php");
	global $user;
	$account = user_load($user->uid);
  //$candidate = get_candidate($account->rmaxid, $account->uid);	
	//$name = $candidate->profile->name;
	$mpdf = new mPDF('utf-8', 'A4');
	$mpdf->setFooter("$name - {DATE m-j-Y h:i:s A}||page {PAGENO} of {nb}");
  $mpdf->setBasePath("sites/all/modules/vistaportal/pdf_html_strings");
  $mpdf->allow_charset_conversion=true;  // Set by default to TRUE
  $mpdf->charset_in='windows-1252';
  $mpdf->WriteHTML($html_string);
  if(is_dir("C:/wamp/www/phportal/sites/default/files/pdf")===true){
		$filename = "C:/wamp/www/phportal/sites/default/files/pdf/foo.pdf";
	}
	else{
		$path = mkdir("C:/wamp/www/phportal/sites/default/files/pdf", 0070);
		$filename = "C:/wamp/www/phportal/sites/default/files/pdf/foo.pdf";
	}
	$mpdf->Output($filename);		
return $filename;
} */

function make_pdf_1($html_string){
include_once('sites/all/Libraries/MPDF54/mpdf.php');
  global $user;
  $account = user_load($user->uid);
  $mpdf = new mPDF('utf-8', 'A4');
  $mpdf->setFooter("$name - {DATE m-j-Y h:i:s A}||page {PAGENO} of {nb}");
  $mpdf->setBasePath("/var/www/html/devapply.vistastaff.com/sites/all/modules/vistaportal/pdf_html_strings");
  $mpdf->allow_charset_conversion=true;  // Set by default to TRUE
  $mpdf->charset_in='windows-1252';
  $mpdf->WriteHTML($html_string);
  if(is_dir("/var/www/html/devapply.vistastaff.com/sites/default/files/pdf")===true){
		$filename = "/var/www/html/devapply.vistastaff.com/sites/default/files/pdf/foo.pdf";
	}
	else{
		$path = mkdir("/var/www/html/devapply.vistastaff.com/sites/default/files/pdf", 0070);
		$filename = "/var/www/html/devapply.vistastaff.com/sites/default/files/pdf/foo.pdf";
	}
	$mpdf->Output($filename);		
return $filename;
} 
