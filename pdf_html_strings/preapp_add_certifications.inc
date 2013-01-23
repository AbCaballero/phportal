<?php

  function get_addcertificationsString($counter, $type, $cert_name, $exp_date, $cert_num, $ecfmg, $ecfmg_exp_date){
    $addcertificationsString = "<div id=\"add-certification\">

<h3>Additional Certification $counter</h3>
<ul>
<li>Type: $type</li>
<li>Certificate Name: $type</li>
<li>Certificate #: $cert_num</li>
<li>Expiration Date: $exp_date</li>
</ul>
</div>
<div id=\"ecfmg\">
<ul>
<li>ECFMG CERTIFICATE #: $ecfmg</li>
<li>Expiration Date: $ecfmg_exp_date</li>
</ul>
</div>";

return $addcertificationsString; 
}