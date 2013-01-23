<?php

  function get_addcertificationsString($counter, $type, $cert_name, $exp_date, $cert_num){
    $addcertificationsString = "<div id=\"add-certification\">

<h3>Additional Certification $counter</h3>
<ul>
<li>Type: $type</li>
<li>Certificate Name: $cert_name</li>
<li>Certificate #: $cert_num</li>
<li>Expiration Date: $exp_date</li>
</ul>
</div>
<div id=\"ecfmg\">
<ul>
<li>ECFMG CERTIFICATE #:</li>
<li>Expiration Date:</li>
</ul>
</div>";

return $addcertificationsString; 
}