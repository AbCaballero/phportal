<?php

  function get_disciplinaryString($med_lic, $other_lic, 
  $dea_reg, $academic_apt, $med_staff_apt, $clinical_priv, 
  $perogatives, $affiliation, $board_cert, $pro_office, 
  $other_sanction, $convicted, $malpractice, $insurance, 
  $med_condition, $treatment, $other) {

    $disciplinaryString = "<div id=\"disciplinary\">
<h3>DISCIPLINARY ACTIONS</h3>
<p>Have any of the following ever been or are currently in the process of being
investigated, denied, revoked, suspended, reduced, limited, placed on probation,
not renewed, been subject to disciplinary action or voluntarily relinquished? If yes,
please provide full explanation.</p>
<ul>
<li>Medical license in any jurisdiction?</li>
<li id=\"dis-answer\">$med_lic</li>
</ul>
<ul>
<li>Other professional registration/license?</li>
<li id=\"dis-answer\">$other_lic</li>
</ul>
<ul>
<li>DEA registration?</li>
<li id=\"dis-answer\">$dea_reg</li>
</ul>
<ul>
<li>Academic discipline or appointment?</li>
<li id=\"dis-answer\">$academic_apt</li>
<li id=\"dis-answer\">Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis
nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu
fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in
culpa qui officia deserunt mollit anim id est laborum.</li>
</ul>
<ul>
<li>Membership on any hospital medical staff?</li>
<li id=\"dis-answer\">$med_staff_apt</li>
<li id=\"dis-answer\">Attached: Megan_Johnson_prerogatives_explanation.pdf</li>
</ul>
<ul>
<li>Clinical privileges?</li>
<li id=\"dis-answer\">$clinical_priv</li>
</ul>
<ul>
<li>Prerogatives/rights on any medical staff?</li>
<li id=\"dis-answer\">$perogatives</li>
</ul>
<ul>
<li>Any medical organization or other institutional affiliation or status there?</li>
<li id=\"dis-answer\">$affiliation</li>
</ul>
<ul>
<li>Professional society membership or fellowship/Board Certification?</li>
<li id=\"dis-answer\">$board_cert,</li>
</ul>
<ul>
<li>Professional office?</li>
<li id=\"dis-answer\">$pro_office</li>
</ul>
<ul>
<li>Any other type of professional sanction or discipline, including by Medicare/
Medicaid or private insurance company?</li>
<li id=\"dis-answer\">$other_sanction</li>
</ul>
<ul>
<li>Have you ever been convicted of a misdemeanor (other than minor traffic violation)
or a felony?</li>
<li id=\"dis-answer\">$convicted</li>
</ul>
<ul>
<li>Have there ever been or are there currently pending, any malpractice claims, suits,
settlements or arbitration proceedings involving your professional practice?</li>
<li id=\"dis-answer\">$malpractice</li>
</ul>
<ul>
<li>Any other type of professional sanction or discipline, including by Medicare/
Medicaid or private insurance company?</li>
<li id=\"dis-answer\">$insurance</li>
</ul>
<ul>
<li>Do you currently have any medical condition or use any chemical substance which
impairs or limits your ability to practice medicine with reasonable skill and safety?
If yes, provide evidence that such conditions do not currently impair or limit your
ability to practice medicine in your specialty with reasonable skill and safety.</li>
<li id=\"dis-answer\">$med_condition</li>
</ul>
<ul>
<li>Within the past two years, have you received treatment for alcoholism, drug abuse,
or for any infectious disease, mental illness or psychiatric problem which could
impair or limit your ability to practice medicine in your specialty with reasonable skill
and safety? If yes, provide evidence that such conditions do not currently impair
or limit your ability to practice medicine in your specialty with reasonable skill and
safety.</li>
<li id=\"dis-answer\">$treatment</li>
</ul>
<ul>
<li>Other than those circumstances noted above, is there anything in your personal
or professional background that may surface during our credentials verification
process that may be construed as derogatory or negative?</li>
<li id=\"dis-answer\">$other</li>
</ul>
</div>";

    return $disciplinaryString;
  }
