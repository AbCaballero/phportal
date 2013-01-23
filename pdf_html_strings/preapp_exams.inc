<?php
  function get_stateexamString($counter, $state, $taken, $result) {

    $stateExamstring = "<div id=\"state-exam\">
<ul>
<li id=\"bold\">State Exam $counter</li>
<li>$state</li>
<li>$taken</li>
<li>$result</li>
</ul>
</div>";

    return $stateExamstring;

  }
