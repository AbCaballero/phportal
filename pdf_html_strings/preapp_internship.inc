<?php

function get_internshipString($counter, $type, $institution, $City, $state, $country, $from, $to, $director) {

  $internshipString = "<div id=\"internship\">
<h3>INTERNSHIP $counter</h3>
<ul>
<li>Internship Type: $type</li>
</ul>
<ul>
<li>Institution:</li>
<li>$institution</li>
<li>$City, $state, $country</li>
</ul>
<ul>
<li>Dates Attended: $from &ndash; $to</li>
</ul>
<ul>
<li>Program Director: $director</li>
</ul>
</div>";

return $internshipString;

}
