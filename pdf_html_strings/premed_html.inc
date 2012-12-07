<?php

/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: December 5th, 2012
 * Notes: This is a test html string for the 
 * vistaportal premed form
 */

//include_once ('../vistaportal_premed.forms.inc');
function getpremed_html($school, $degree, $city, $state, $country, $startDate, $endDate){
/*foreach ($paramsEdu['edu'] AS $key => $value) {
		if ($paramsEdu['edu'][$key]['rdo_grad_status'] == 'Yes') {
			$grad_status_yes[$key] = "checked='checked'";
		} elseif ($paramsEdu['edu'][$key]['rdo_grad_status'] == 'No') {
			$grad_status_no[$key] = "checked='checked'";
		}
	}
	if ($paramsExp['chk_recent_grad'] == 1) {
		$chk_recent_grad_yes = "checked";
	} elseif ($paramsExp['chk_recent_grad'] == 0) {
		$chk_recent_grad_no = "checked";
	}

	foreach ($paramsExp['exp'] AS $key => $value) {
		if ($paramsExp['exp'][$key]['chk_present'] == 1) {
			$chk_present_yes[$key] = "checked='checked'";
		}

		if ($paramsExp['exp'][$key]['rdo_salary_period'] == 'annual') {
			$rdo_salary_annual[$key] = "checked='checked'";
		} elseif ($paramsExp['exp'][$key]['rdo_salary_period'] == 'hourly') {
			$rdo_salary_hourly[$key] = "checked='checked'";
		}

		if ($paramsExp['exp'][$key]['rdo_may_contact'] == 'Yes') {
			$rdo_may_contact_yes[$key] = "checked='checked'";
		} elseif ($paramsExp['exp'][$key]['rdo_may_contact'] == 'No') {
			$rdo_may_contact_no[$key] = "checked='checked'";
		}
		if ($paramsExp['exp'][$key]['empdatefrom'] != "") {
			$start_date[$key] = getformatted_date_from_timestamp($paramsExp['exp'][$key]['empdatefrom']);
		}
		if ($paramsExp['exp'][$key]['empdateto'] != "") {
			$end_date[$key] = getformatted_date_from_timestamp($paramsExp['exp'][$key]['empdateto']);
		} else {
			$end_date[$key] = "";
		}
	}

	/*'Contract', 'Contract to hire', 'Direct Hire'*/
	/*foreach ($paramsPref['chk_type'] AS $key => $value) {
		if ($key === $value) {
			$paramsPref['chk_type'][$key] = "checked='checked'";
		} else {
			$paramsPref['chk_type'][$key] = " ";
		}
	}*/

	/*'Any', 'M', 'T', 'W', 'Th', 'F', 'S', 'Su'*/
/*	foreach ($paramsPref['chk_work_days'] AS $key => $value) {
		if ($key === $value) {
			$paramsPref['chk_work_days'][$key] = "checked='checked'";
		} else {
			$paramsPref['chk_work_days'][$key] = " ";
		}
	}

	/*'Any', 'Days', 'Nights', 'Evenings', 'Weekends'*/
/*	foreach ($paramsPref['chk_shifts'] AS $key => $value) {
		if ($key === $value) {
			$paramsPref['chk_shifts'][$key] = "checked='checked'";
		} else {
			$paramsPref['chk_shifts'][$key] = " ";
		}
	}

	/*$chk_ptft 'Either', 'Part-time', 'Full-time' */
/*	foreach ($paramsPref['chk_ptft'] AS $key => $value) {
		if ($key === $value) {
			$paramsPref['chk_ptft'][$key] = "checked='checked'";
		} else {
			$paramsPref['chk_ptft'][$key] = " ";
		}
	}

	/*$rdo_legal_right*/
/*	if ($paramsPref['rdo_legal_right'] == 'Yes') {
		$rdo_legal_right_yes = "checked";
	} elseif ($paramsPref['rdo_legal_right'] == 'No') {
		$rdo_legal_right_no = "checked";
	}

	/*$rdo_drug_alcohol_screen*/
/*	if ($paramsPref['rdo_drug_alcohol_screen'] == 'Yes') {
		$rdo_drug_alcohol_screen_yes = "checked";
	} elseif ($paramsPref['rdo_drug_alcohol_screen'] == 'No') {
		$rdo_drug_alcohol_screen_no = "checked";
	}

	$distance = $paramsPref['distance'] . " " . $paramsPref['rdo_trv'];

	$date = date('m/j/Y');

	/*Add education dynamically*/
/*	$education_header = "<table style=\"overflow: wrap\">
		<tr>
		<td height=\"0\" colspan=\"4\" class=\"subheader\">Education</td>
		</tr>";
	$valid_education_counter = 1;
	foreach ($paramsEdu['edu'] as $key => $value) {
		if ($paramsEdu['edu'][$key]['school'] == '') {
			continue;
		} else {*/
			$education_string = "<tr>	
          <td class=\"subheaderSmall\" colspan=\"4\">Education 
          </td>
          </tr>
          <tr><td class=\"question\">School:</td>
					<td class=\"answer\" colspan=\"3\">$school</td></tr>
					<tr><td class=\"question\">Did you graduate:</td>
					<td class=\"answer\">
					<form>
					<input type=\"checkbox\" name=\"form\" value=\"yes\"  />yes
					<input type=\"checkbox\" name=\"form\" value=\"no\"  />No
					</form> 
					</td>
					<td class=\"question\">Year:</td>
					<td class=\"answer\" >$endDate</td>
					</tr>
					<tr><td class=\"question\">Degree Earned:</td>
					<td class=\"answer\" colspan=\"3\">$degree</td></tr>
					<tr><td class=\"question\">City:</td>
					<td class=\"answer\">$city</td>
					<td class=\"question\">State:</td>
					<td class=\"answer\">$state</td></tr>
					<tr><td class=\"question\">Major:</td>
					<td class=\"answer\" colspan=\"3\"></td></tr>
					<tr><td class=\"question\">Minor:</td>
					<td class=\"answer\" colspan=\"3\"></td></tr>
					<tr><td class=\"question\">Relevent Course Work:</td>
					<td class=\"answer\" colspan=\"3\"></td></tr>";
//		}
//	}
/*	foreach ($paramsEdu['edu'] as $key => $value) {
		if ($paramsEdu['edu'][$key]['coursework2'] == '') {
			continue;
		} else {
			$coursework2_string = $coursework2_string . "<tr><td class=\"question\"></td>
					<td class=\"answer\" colspan=\"3\">{$paramsEdu['edu'][$key]['coursework2']}</td></tr>";
		}
	}
	foreach ($paramsEdu['edu'] as $key => $value) {
		if ($paramsEdu['edu'][$key]['coursework3'] == '') {
			continue;
		} else {
			$coursework3_string = $coursework3_string . "<tr><td class=\"question\"></td>
					<td class=\"answer\" colspan=\"3\">{$paramsEdu['edu'][$key]['coursework3']}</td></tr>";
		}
	}
	foreach ($paramsEdu['edu'] as $key => $value) {
		if ($paramsEdu['edu'][$key]['coursework4'] == '') {
			continue;
		} else {
			$coursework3_string = $coursework3_string . "<tr><td class=\"question\"></td>
					<td class=\"answer\" colspan=\"3\">{$paramsEdu['edu'][$key]['coursework4']}</td></tr>";
		}

		//$valid_education_counter+=1;
	}
	$education_string = $education_header . $education_template . $coursework2_string . $coursework3_string . 
		$coursework4_string . "</table><div style=\"font-size:10px; page-break-after:auto; text-align:right; margin-top:0px;\"></div>";

	/*Add experience dynamically*/
/*	$experience_header = "<div id=\"wrapper\">
		<table style=\"overflow: wrap\">
		<tr><td class=\"subheader\" colspan=\"4\">Experience</td></tr>
		<tr><td class=\"question\">Did you recently graduate college?</td>
		<td class=\"answer\" colspan=\"3\">
		<form>
		<input type=\"checkbox\" name=\"form\" value=\"yes\" checked=$chk_recent_grad_yes />Yes
		<input type=\"checkbox\" name=\"form\" value=\"no\" checked=$chk_recent_grad_no />No
		</form> 
		</td></tr>";
	$valid_experience_counter = 1;
	foreach ($paramsExp['exp'] as $key => $value) {
		if ($paramsExp['exp'][$key]['employer'] == '') {
			continue;
		} else {
			$experience_template = $experience_template . "<tr>	
          <td class=\"subheaderSmall\" colspan=\"4\">Experience $valid_experience_counter</td></tr>
					<tr><td class=\"questionApplication\">Employer:</td>
					<td class=\"answerApplication\" colspan=\"3\">{$paramsExp['exp'][$key]['employer']}</td></tr>
					<tr><td class=\"question\">City:</td>
					<td class=\"answer\">{$paramsExp['exp'][$key]['city']}</td>
					<td class=\"question\">State:</td>
					<td class=\"answer\">{$paramsExp['exp'][$key]['state']}</td></tr>
					<tr><td class=\"question\">Start Date:</td>
					<td class=\"answer\" colspan=\"3\">$start_date[$key]</td></tr>
					<tr><td class=\"question\">End Date:</td>
					<td class=\"answer\" colspan=\"3\">
					<form>$end_date[$key]
					<input type=\"checkbox\" name=\"form\" value=\"present\" $chk_present_yes[$key] />Working there presently
					</form>
					</td></tr>
					<tr><td class=\"question\">Title:</td>
					<td class=\"answer\" colspan=\"3\">{$paramsExp['exp'][$key]['posheld']}</td></tr>
					<tr><td class=\"question\">Salary:</td>
					<td class=\"answer\">{$paramsExp['exp'][$key]['salary']}</td><td class=\"question\">Annual or Hourly:</td>
					<td class=\"answer\">
					<form>
					<input type=\"checkbox\" name=\"form\" value=\"annual\" $rdo_salary_annual[$key] />Annual
					<input type=\"checkbox\" name=\"form\" value=\"hourly\" $rdo_salary_hourly[$key] />Hourly
					</form>
					</td></tr>
					<tr><td class=\"question\">Description:</td>
					<td class=\"answer\" colspan=\"3\">{$paramsExp['exp'][$key]['description']}</td></tr>
					<tr><td class=\"question\">Immediate Supervisor:</td>
					<td class=\"answer\" colspan=\"3\">{$paramsExp['exp'][$key]['supname']}</td></tr>
					<tr><td class=\"question\">May we contact?</td>
					<td class=\"answer\" colspan=\"3\">
					<form>
					<input type=\"checkbox\" name=\"form\" value=\"yes\" $rdo_may_contact_yes[$key] />Yes
					<input type=\"checkbox\" name=\"form\" value=\"no\" $rdo_may_contact_no[$key] />No
					</form>
					</td></tr>
					<tr><td class=\"question\">Reason for leaving:</td>
					<td class=\"answer\" colspan=\"3\">{$paramsExp['exp'][$key]['reason']}</td></tr>";

			$valid_experience_counter += 1;
		}
		$experience_string = $experience_header . $experience_template . "</table><div style=\"font-size:10px; page-break-after:avoid; text-align:right; margin-top:0px;\"></div>";
	}

	$candidate_referral = $candidate -> profile -> referral; */
	$header_string = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
<title>HC Application</title>
<link href=\"../css/hcdmsform4app.css\" rel=\"stylesheet\" type=\"text/css\" />
</head>

<body>
<div id=\"wrapper\">

<table cellpadding=\"0\" cellspacing=\"0\" class=\"header\">
<tr>
<td width=\"265\" valign=\"top\"><img src=\"../img/HC-dms-logo-72dpi.jpg\" width=\"180\" /></td>
<td width=\"423\" class=\"formTitle\" valign=\"top\">
   Application</td></tr>
<tr>
 <td class=\"line\">

     <br />
NAME: Andrew
</td><td align=\"right\" class=\"line\"><br />
ID: 1 </td>
    </tr>
    </table>
<br />
<br />
<br />
<br />
<br />";

/*	$contact_string = "<table style=\"overflow: wrap\">
  <tr>
<td class=\"subheader\" colspan=\"4\">Contact Information
</td>
</tr>
<tr>
<td class=\"question\">First Name:
</td>
<td class=\"answer\">$fname</td>

<td class=\"question\">Middle Initial:</td>
<td class=\"answer\">$mname</td>
</tr>
<tr>
<td class=\"question\">Last Name:</td>
<td class=\"answer\" colspan=\"3\">$lname</td>
</tr>
<tr>
<td class=\"question\">Address:</td>
<td class=\"answer\" colspan=\"3\">$add1</td>
</tr>
<tr>
<td class=\"question\">Address:</td>
<td class=\"answer\" colspan=\"3\">$add2</td>
</tr>


<tr><td class=\"question\">City:</td>
<td class=\"answer\" colspan=\"3\">$city</td></tr>
<tr><td class=\"question\">State:</td>
<td class=\"answer\">$state</td><td class=\"question\">Zip Code:</td>
<td class=\"answer\">$postal</td></tr>
<tr>
<td class=\"question\">Home Phone:</td>
<td class=\"answer\" colspan=\"3\">$homephone</td></tr>
<tr><td class=\"question\">Cell Phone:</td>
<td class=\"answer\" colspan=\"3\">$cellphone</td></tr>
<tr><td class=\"question\">Email:</td>
<td class=\"answer\" colspan=\"3\">$email</td></tr>
<tr><td class=\"question\">Emergency Contact 1 Name:</td>
<td class=\"answer\">{$paramsEmrg['emerg1_name']}</td><td class=\"question\"> Phone:</td>
<td class=\"answer\">{$paramsEmrg['emerg1_phone']}</td>
</tr>
<tr>
<td class=\"question\">Emergency Contact 2 Name:</td>
<td class=\"answer\">{$paramsEmrg['emerg2_name']}</td>
<td class=\"question\">Phone:</td>
<td class=\"answer\">{$paramsEmrg['emerg2_phone']}</td></tr>
</table>";
	$preferences_string = "<div style=\"font-size:10px; page-break-after:auto; text-align:right; margin-top:0px;\"></div>
<div id=\"wrapper\">
<table  style=\"overflow: wrap\">
<tr><td class=\"subheader\" colspan=\"4\">Employment Questions</td></tr>
<tr>
  <td class=\"question\">How far are you willing to commute?</td>
<td class=\"answer\">$distance</td></tr>
<tr>
<td class=\"question\">Preferred employment type:</td>
<td class=\"answer\"> 
<form>
<input type=\"checkbox\" name=\"form\" value=\"Contract\" {$paramsPref['chk_type']['Contract']} />Contract
<input type=\"checkbox\" name=\"form\" value=\"Contract-to-hire\" {$paramsPref['chk_type']['Contract to hire']} />Contract-to-hire
<input type=\"checkbox\" name=\"form\" value=\"Direct Hire\" {$paramsPref['chk_type']['Direct Hire']} />Direct Hire
</form>
</td></tr>
<tr><td class=\"question\">Days you are willing to work:</td>
<td class=\"answer\">
<form>
<input type=\"checkbox\" name=\"form\" value=\"Mon\" {$paramsPref['chk_work_days']['M']} />Mon
<input type=\"checkbox\" name=\"form\" value=\"Tues\" {$paramsPref['chk_work_days']['T']} />Tues
<input type=\"checkbox\" name=\"form\" value=\"Wed\" {$paramsPref['chk_work_days']['W']} />Wed
<input type=\"checkbox\" name=\"form\" value=\"Thur\" {$paramsPref['chk_work_days']['Th']} />Thur
<input type=\"checkbox\" name=\"form\" value=\"Fri\" {$paramsPref['chk_work_days']['F']} />Fri
<input type=\"checkbox\" name=\"form\" value=\"Sat\" {$paramsPref['chk_work_days']['S']} />Sat
<input type=\"checkbox\" name=\"form\" value=\"Sun\" {$paramsPref['chk_work_days']['Su']} />Sun
</form>

</td></tr>
<tr><td class=\"question\">Shifts you are willing to work:</td>
<td class=\"answer\">

<form>
<input type=\"checkbox\" name=\"form\" value=\"Days\" {$paramsPref['chk_shifts']['Days']} />Days
<input type=\"checkbox\" name=\"form\" value=\"Nights\" {$paramsPref['chk_shifts']['Nights']} />Nights
<input type=\"checkbox\" name=\"form\" value=\"Evenings\" {$paramsPref['chk_shifts']['Evenings']} />Evenings
<input type=\"checkbox\" name=\"form\" value=\"Weekends\" {$paramsPref['chk_shifts']['Weekends']} />Weekends
</form>
</td></tr>
<tr><td class=\"question\">Prefer Full-time or Part-time:</td>
<td class=\"answer\">
<form>
<input type=\"checkbox\" name=\"form\" value=\"Full\" {$paramsPref['chk_ptft']['Part-time']} />Full-time
<input type=\"checkbox\" name=\"form\" value=\"part\" {$paramsPref['chk_ptft']['Full-time']} />Part-time
</form>
</td></tr>

<tr>
<td class=\"question\">Can you, after employment, submit verification of your legal right to work in the U.S.?</td>
<td class=\"answerNoHeight\">
<form>
<input type=\"checkbox\" name=\"form\" value=\"yes\" checked=$rdo_legal_right_yes />Yes
<input type=\"checkbox\" name=\"form\" value=\"no\" checked=$rdo_legal_right_no />No
</form>
</td></tr>

<tr>
<td class=\"questionLong\" colspan=\"2\">As a condition of employment, you 
  may be required to take and pass a
  drug and/or alcohol screen. Testing 
  will be done at the company\'s 
  expense and administered by a 
  testing facility designated by the 
  company. Results of any testing will 
  be kept strictly confidential. If 
  requested, are you willing to take the 
  drug and/or alcohol screen?:</td></tr>
<tr>
<td class=\"question\">&nbsp;
</td>
<td class=\"answer\" >
<form>
<input type=\"checkbox\" name=\"form\" value=\"yes\" checked=$rdo_drug_alcohol_screen_yes />Yes
<input type=\"checkbox\" name=\"form\" value=\"no\" checked=$rdo_drug_alcohol_screen_no />No
</form>
</td></tr>
</table>
<table  style=\"overflow: wrap\">
<tr><td class=\"question\">How did you hear about us?</td>
<td class=\"answer\"></td></tr>
<tr><td class=\"question\">Months since last job in Healthcare:</td>
<td class=\"answer\">4</td></tr>
<tr><td class=\"question\">Total years of experience:</td>
<td class=\"answer\">{$paramsPref['experience']}</td></tr>
<tr><td class=\"question\">Primary Langauge:</td>
<td class=\"answer\"></td></tr>
<tr><td class=\"question\">Secondary Langauge:</td>
<td class=\"answer\"></td></tr>
<tr><td class=\"question\">Other Langauge:</td>
<td class=\"answer\"></td></tr>
</table>
<table  style=\"overflow: wrap\">
<tr>
<td class=\"questionLong\" style=\"overflow:wrap\"><br />
On Assignment is an Equal Opportunity Employer, M/F/D/V. All applicants are considered for employment regardless of age, race, gender, religion, national
origin, disability, marital status, or any other factor prohibited by law.<br />
<br />

I understand and agree that if I am offered employment by the Company, it will be on an at-will basis. This means that either I or the Company may terminate
the employment relationship at any time, for any reason, with or without cause. I also understand and agree that only an officer of the Company can enter
into an agreement on any other terms and he/she can only do so in writing signed by him/her and me. I certify the information provided within this submission
is accurate. I understand that the withholding of information or the giving of false information for this submission will result in a refusal to hire or disciplinary
action up to and including termination after employment commences.
</td>
</tr>
</table>
<table width=\"700\">
          <tr>
          <td width=\"425\" class=\"sign\">$fname $lname</td>
          <td width=\"50\">&nbsp;
          </td>
          <td width=\"222\" class=\"sign\">$date</td>
          </tr>
        <tr>         
         <td>
         Signature </td>
         <td><br />
</td>
         <td>Date
         </td>
         </tr>
         </table>
       <!-- <div style=\"font-size:10px;  text-align:right; margin-top:140px; page-break-after:avoid;\"></div> -->*/


$tail = "</body>
</html>";

	$string = $header_string . $education_string . $tail;
	return $string;
}