<?php

  function get_certificationsString($counter, $board_status, $board, $board_exp_date, $certnum, $cert_recert){
    $certificationsString = "<div id=\"certification\">
<h3>CERTIFICATIONS $counter</h3>
<ul>
<li id=\"bold\">Board Certification</li>
<li>Current Specialty Board Status: $board_status</li>
<li>American Board of Medical Sciences: $board</li>
<li>Was this a Certification or a Recertification?: $cert_recert</li>
<li>Date: $board_exp_date</li>
<li>Certificate #: $certnum</li>
</ul>
</div>";
$certificationsString;
}