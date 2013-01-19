<?php

  function get_referencesString($counter, $name, $association, $specialty, $email, $phone_num) {
    $referencesString = "<div id=\"references\">" . ($counter == 1) ? "<h3>REFERENCES</h3>
<p>Please list a minimum of six professional references with whom you have worked in
the past two years and who can attest to your specific medical abilities.</p>" : "</div>
<div id=\"references $counter\">";
    $referencesString .= "<ul>
<li id=\"bold\">Reference 1</li>
<li>Name: $name</li>
<li>Association: $association</li>
<li>Specialty: $specialty</li>
<li>Cell: $phone_num</li>
<li>Email: $email</li>
</ul>
</div>";

    return $referencesString;
  }
