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
 

  function pdf_to_tiff($filename) {
    global $user;
    $account = user_load($user -> uid);
    $id = $user -> uid;
    $outputdirectorypath = drupal_realpath('public://') . "/tiff/$id/";
    $directorypath = drupal_realpath('public://') . "/pdf/$id/";
    if (is_dir($outputdirectorypath) === true) {
       $outputTiffFileName = $outputdirectorypath . 'preApplication.tiff';
    }
    else {
      $path = mkdir($outputdirectorypath, 0777, true);
      $outputTiffFileName = $directorypath . 'preApplication.tiff';
    }
    $inputPDFFileName = $filename;
    $cmd = "gs -SDEVICE=tiffg4 -r300x300 -sPAPERSIZE=letter -sOutputFile=$outputTiffFileName -dNOPAUSE -dBATCH  $inputPDFFileName";
    $response = shell_exec($cmd);
    return $outputTiffFileName;
  }

 /* function pdf_to_tiff($filename) {
    global $user;
    $account = user_load($user -> uid);
    $id = $user -> uid;
    $outputTiffFileName = uploadtoFTP($filename, "PreApplication.tiff", $id);
    $inputPDFFileName = $filename;
    $cmd = "gs -SDEVICE=tiffg4 -r300x300 -sPAPERSIZE=letter -sOutputFile=$outputTiffFileName -dNOPAUSE -dBATCH  $inputPDFFileName";
    $response = shell_exec($cmd);
    return $response;
  }*/