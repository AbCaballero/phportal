<?php

  function uploadtoFTP($source_file, $destination_file, $entityid) {

    $ftpRootdocspath = variable_get('vistadocsrootpath', '/docs/Vistaportalfiles');

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
      drupal_set_message(t("Your file has been successfully uploaded to the server"));
    }
    ftp_close($Stream);

  }
