<?php

function get_residencyString($counter, $type, $institution, $City, $state, $country, $from, $to, $director) {

  $residencyString = "<div id=\"residency\">
<h3>RESIDENCY $counter</h3>
<ul>
<li>Internship Type: $type</li>
</ul>
<ul>
<li>Institution:</li>
<li>$institution</li>
<li>$City, $state, $country</li>
</ul>
<ul>
<li>Dates Attended: $from – $to</li>
</ul>
<ul>
<li>Program Director: $director</li>
</ul>
</div>";

return $residencyString;

}
