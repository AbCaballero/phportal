<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: December 14th, 2012
 * Notes: This code to invoke ghostscript and create the 
 * the requisite tiff files.
 */

/*
 * Function to raster a tif file from a pdf
 */
 
 
/*function pdf_to_tiff(){
	$outputTiffFileName = "C:/wamp/www/phportal/sites/default/files/pdf/foo.tiff";
	$inputPDFFileName = "C:/wamp/www/phportal/sites/default/files/pdf/VISTA13_phys_apply_v1.pdf";	
	$cmd = "c:/progra~1/gs/gs9.06/bin/gswin64c -SDEVICE=tiffg4 -r300x300 -sPAPERSIZE=letter -sOutputFile=$outputTiffFileName -dNOPAUSE -dBATCH  $inputPDFFileName";	
	$response = shell_exec($cmd);
	return $response;	
}*/

function pdf_to_tiff(){
	$outputTiffFileName = "/var/www/html/devapply.vistastaff.com/sites/default/files/tiff/foo.tiff";
	$inputPDFFileName = "/var/www/html/devapply.vistastaff.com/sites/default/files/pdf/foo.pdf"; 	
	$cmd = "gs -SDEVICE=tiffg4 -r300x300 -sPAPERSIZE=letter -sOutputFile=$outputTiffFileName -dNOPAUSE -dBATCH  $inputPDFFileName";
	$response = shell_exec($cmd);
	dsm($response);
	return $response;	
}
