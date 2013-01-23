 <?php
 function get_licenseseString($counter, $lic_type, $country, $state, $lic_number, $date_issued, $date_expired, $original_state_license) {
$licensesString = "<div id=\"licenses1\">
<ul>
<li id=\"bold\">License $counter</li>
<li>Original State License: $original_state_license</li>
<li>License Type: $lic_type</li>
<li>Country: $country</li>
<li>License #: $lic_number</li>
<li>Date Issued:$date_issued</li>
<li>Expiration Date: $date_expired</li>
</ul>
</div>";

return $licensesString;
 }