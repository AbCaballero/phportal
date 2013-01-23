<?php

function get_affiliationsString($counter, $facility, $address1, $city, $state, $zip, $country, $capacity, $from, $to) {

 $affiliationsString =  "div id=\"affiliations\">" . ($counter == 1) ? "<h3>AFFILIATION</h3>
<p>List all present and previous affiliations with healthcare facilities and medical staff
memberships for the past 10 years, in chronological order. Include clerkships,
assistantships, appointments, and military experience. Specify all departments in
which privileges were exercised and the nature and extent of such privileges. ALL
LOCUM TENENS WORK MUST BE INCLUDED WITH LOCATIONS AND DATES.</p>" : "<h3>AFFILIATION $counter</h3>";

$affiliationsString .= "<ul>
<li>Facility or Practice:</li>
<li>$facility</li>
<li>$address1</li>
</ul>
<ul>
<li>$city, $state $zip</li>
<li>$country</li>
</ul>
<ul>
<li>Program Director: $director</li>
</ul>
<ul>
<li>Capacity: $capacity</li>
</ul>
<ul>
<li>Dates: $from &mdash; $to</li>
</ul>
</div>";

return $affiliationsString;

}
