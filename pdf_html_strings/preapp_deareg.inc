<?php
  function get_dearegString($counter, $pending, $country, $lic_num, $date_issued, $date_expired, $schedule_2, $schedule_3, $schedule_4, $schedule_5, $schedule_2n, $schedule_3n) {
    $dearegString = "<div id=\"dea\">
<ul>
<li id=\"bold\">DEA Registration $counter</li>
<li>Pending</li>
<li>Country: $country</li>
<li>License #: $lic_num</li>
<li>Date Issued:  $date_issued</li>
<li>Expiration Date: $date_expired</li>
</ul>
<ul>
<li>Schedules: $schedule_2, $schedule_3, $schedule_4, $schedule_5, $schedule_2n, $schedule_3n</li>
</ul>
<ul>
<li>Expiration Date: July 2013</li>
</ul>
</div>
<div id=\"dea-language\">
<h3>In addition to English, other languages spoken with communication ease and/
or fluency:</h3>
<ul>
<li></li>
</ul>
</div>";

    return $dearegString;
  }
