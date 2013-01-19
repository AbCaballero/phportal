<?php

function get_medString($counter, $school, $City, $State, $Country, $from, $to, $Degree) {

  $medString = "<div id=\"med\">
<h3>MEDICAL EDUCATION $counter</h3>
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

  return $medString;

}
