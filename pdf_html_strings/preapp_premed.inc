<?php

function get_premedString($counter, $school, $City, $State, $Country, $from, $to, $Degree) {

  $premedString = "<div id=\"premed\">
<h3>PRE-MEDICAL EDUCATION $counter</h3>
<ul>
<li>School of Graduation:</li>
<li>$school</li>
<li>$City, $State, $Country</li>
</ul>
<ul>
<li>Dates Attended: $from – $to</li>
<li>Degree: $Degree</li>
</ul>
</div>";

  return $premedString;

}
