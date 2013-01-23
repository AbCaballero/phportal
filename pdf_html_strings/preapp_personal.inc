<?php

  function get_personalinfoString($datesubmitted, $firstname, $lastname, $middleinit, $phone_choice, $phone, $email, $address1, $City, $State, $zip, $eligibility, $maritalstatus, $spouse, $children) {

    $personal_information = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
<title>Pdf Strings</title>
<link rel=\"stylesheet\" href=\"../css/preapp_complete.css\" type=\"text/css\" />

</head>

<body>
<div id=\"content-pdf\">
<div id=\"logo\"><img src=\"../img/logo.png\"/></div>
<div id=\"title\">
<h1>Physician Application Step 1</h1>
<h2>Submitted $datesubmitted</h2>
<h2>For $firstname $middleinit $lastname</h2>
</div>
<div id=\"personal-info\">
<h3>PERSONAL INFORMATION</h3>
<ul>
<li>Name: $lastname, $firstname $middleinit</li>
<li>$phone_choice: $phone</li>
<li>Email: $email</li>
</ul>
<ul>
<li>Home Adress: $lastname, $firstname $middleinit</li>
<li>$address1</li>
<li>$City, $State $zip</li>
</ul>
<ul>
<li>Can you provide proof of legal eligibility to work in the USA?</li>
<li>$eligibility</li>
</ul>
<ul>
<li>Marital Status: $maritalstatus</li>
<li>Spouse&apos;s Name: $spouse</li>
<li># of Children: $children</li>
</ul>
</div>";

    return $personal_information;
  }
