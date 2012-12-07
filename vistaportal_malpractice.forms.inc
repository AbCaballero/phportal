<?php
/*
 * Form callback for application for malpractice insurance coverage
 * @TODO duplicate field names where possible
 */
function vistaportal_malpractice_insurance_form($form, &$form_state){
	$form = array();
	//liability carrier history
	$form['liability']['desc_1'] = '<p>Application for Malpractice Insurance Coverage
		Part I<br />Professional Liability Carrier History<br />
		HCP MUST CONDUCT CLAIMS-HISTORY VERIFICATIONS FROM ALL PROFESSIONAL LIABILITY CARRIERS<br />
		List ALL carriers for the last five (5) years if you are seeking locum tenens opportunities 
		in commercial facilities<br />If you are seeking locum tenens work in government facilities, 
		carrier history covering ten (10) years is to be added on the “Application Addendum”<br />
		(You may submit copies of policy declaration pages for each carrier covering all periods 
		of time)<br /></p>';
	$ins_fields['company_name'] = textfield('Company Name');
	$ins_fields['policy_num'] = textfield('Policy Number');
	$ins_fields['limits'] = textfield('Limits of Liability');	
	$ins_fields['covered_from'] = date_popup('Covered From');
	$ins_fields['covered_to'] = date_popup('Covered To');
	$ins_fields['claims'] = textfield('Claims-Made Policy?');
	$ins_fields['retro'] = date_popup('Retro Exclusion Date for Prior Acts');
	$form['liability']['carrier'] = '<p>IF YOUR COVERAGE WAS/IS THROUGH AN EMPLOYER’S OR LOCUM 
		TENENS ORGANIZATION’S CARRIER, BUT YOU DO NOT KNOW THE CARRIER INFORMATION, LIST EMPLOYER 
		OR LOCUM TENENS COMPANY NAME AND THE PERIODS YOU WERE/ARE COVERED.</p>';
	$coverage_fields['name'] = textfield('Employer or Company Name');
	$coverage_fields['date'] = date_popup('Dates you were covered');	
	$form['liability'][0]['ins_counter']['#type'] = "hidden";
	$form['liability'][0]['ins_counter']['#default_value'] = -1;
	$form['liability'][0]['add_ins'] = vistaportal_set($ins_fields, 
		'Add another carrier', 'Remove another carrier', 3);
	$form['liability'][0]['coverage_counter']['#type'] = "hidden";
	$form['liability'][0]['coverage_counter']['#default_value'] = -1;
	$form['liability'][0]['add_cov'] = vistaportal_set($coverage_fields, 
		'Add another employer', 'Remove another employer', 3);
	$form['liability'][0]['history'] = radios_yesno('Have there ever been, or are there currently pending
		any malpractice claims, suits, settlements or arbitration proceedings involving your 
		professional practice? If “yes”, complete a Supplemental Claim History for each claim or suit.
		(If you have history of more than three claims or suits you may print additional Supplemental 
		Claim History forms to complete.)');
	$form['liability'][0]['suit'] = radios_yesno('Are you aware of any acts, errors, omissions or 
	circumstances which may result in a malpractice claim or suit being made or brought against you?
	If “yes”, complete a Supplemental Claim History sheet for each occurrence.');	
	
	$form['liability'][0]['application_terms'] = terms_1($terms_desc); //@TODO
	$form['liability'][0]['application_terms']['#attributes']['class'] .= 
		'edit-liability-application-terms required';
	$form['liability'][0]['application_terms']['#title'] = 'I Accept Terms';
	$form['liability'][0]['application_terms']['#rules'] = array( 
		array('rule' => 'chars[1]', 'error' => 'You must accept the Terms to continue.'));
	
	$form['liability']['desc_2'] = '<p>Application for Malpractice Insurance Coverage
		Part II<br />Supplemental Claims History<br />Please provide the following regarding 
		any incident, claim, or suit or incident which may give rise to a claim whether dismissed,
		settled out of court, judgment or pending. Answer all questions completely.This form should 
		be photocopied for use with each claim. Please type or print clearly.<br /></p>';
		
	$form['liability'][1]['defendant'] = textfield("Defendant's Name");
	$form['liability'][1]['plaintiff'] = textfield("Claimant (Plaintiff’s) ID:");
	$form['liability'][1]['location'] = textfield("Where did incident/alleged error occur?");
	$form['liability'][1]['filed'] = checkbox('Claim Filed');
	$form['liability'][1]['reported'] = checkbox('Incident that has been reported to insurer');
	$form['liability'][1]['suit'] = textfield('If Suit Filed, County/State where case filed:');
	$form['liability'][1]['suit']['case_num'] = textfield('Case Number');
	$form['liability'][1]['attorney'] = textfield('Defendant Attorney Name/Address/Phone:');	
	$form['liability'][1]['judgement'] = '<p>Please upload copies of final judgment, 
		settlement & release or other final disposition.<p>';
	$form['liability'][1]['status'] = fieldset('STATUS OF COMPLAINT');
	$form['liability'][1]['if_closed'] = checkboxes('If CLOSED:', array(
		'Court Judgement', 'Finding For You', 'Finding For Plaintiff', 'Determined By Judge',
		'Determined By Jury', 'Out OF Court Settlement', 'Case Dismissed', 'Against You',
		'Against All Defendants'));
	$form['liability'][1]['defendant_amount'] = textfield('Amount paid on your behalf:');
	$form['liability'][1]['total_amount'] = textfield('Total Settlement against all parties:');
	$form['liability'][1]['date_closed'] = date_popup('Date of closure, settlement, or dismissal');
	$form['liability'][1]['if_open'] = radios_yesno('Claim in suit');
	$form['liability'][1]['description'] = '<p><u>DESCRIPTION OF CLAIM</u> Provide enough information 
		to allow evaluation:</p>';
	$form['liability'][1]['description']['error'] = textfield('Alleged act, error or omission 
		upon which Claimant bases claim:');
	$form['liability'][1]['description']['extent'] = textfield('Description of type and 
		extent of injury or damage allegedly sustained:');
	$form['liability'][1]['description']['condition_start'] = textfield('Patient’s Condition 
		at point of your involvement:');
	$form['liability'][1]['description']['condition_end'] = textfield('Patient’s Condition at 
		end of your treatment?');
	$form['liability'][1]['description']['narration'] = textarea('Provide a narration of the case, 
		relating events in chronological order emphasizing the dates of service and stating in 
		detail what was done each time the patient was seen professionally. You may use a separate 
		sheet to complete, sign and date.');
	$form['liability'][1]['application_terms_supplemental'] = terms_1($terms_desc);//@TODO
	$form['liability'][1]['application_terms_supplemental']['#attributes']['class'] .= 
		'edit-liability-application-terms_supplemental required';
	$form['liability'][1]['application_terms_supplemental']['#title'] = 'I Accept Terms';
	$form['liability'][1]['application_terms_supplemental']['#rules'] = array( 
		array('rule' => 'chars[1]', 'error' => 'You must accept the Terms to continue.'));
	
	$form['liability']['desc_3'] = '<p>Please provide the following regarding any incident, 
		claim, or suit or incident which may give rise to a claim whether dismissed, settled 
		out of court, judgment or pending. Answer all questions completely. This form should 
		be photocopied for use with each claim. Please type or print clearly.</p>';
	$form['liability'][2]['defendant_name'] = textfield("Defendant's Name");
	$form['liability'][2]['plaintiff_id'] = textfield('Claimant (Plaintiff’s) ID:');
	$form['liability'][2]['error_date'] = date_popup('Date of alleged error:');
	$form['liability'][2]['location'] = textfield('Where did incident/alleged error occur?');
	$form['liability'][2]['filed'] = checkbox('Claim Filed');
	$form['liability'][2]['reported'] = checkbox('Incident that has been reported to insurer');
	$form['liability'][2]['company_name'] = textfield('Name of Insurer');
	$form['liability'][2]['suit'] = textfield('If Suit Filed, County/State where case filed:');
	$form['liability'][2]['suit']['case_num'] = textfield('Case Number');
	$form['liability'][2]['attorney'] = textfield('Defendant Attorney Name/Address/Phone:');
	$form['liability'][2]['judgement'] = '<p>Please upload copies of final judgment, 
		settlement & release or other final disposition.<p>';
	$form['liability'][2]['status'] = fieldset('STATUS OF COMPLAINT');	
	$form['liability'][2]['if_closed'] = checkboxes('If CLOSED:', array(
		'Court Judgement', 'Finding For You', 'Finding For Plaintiff', 'Determined By Judge',
		'Determined By Jury', 'Out OF Court Settlement', 'Case Dismissed', 'Against You',
		'Against All Defendants'));
	$form['liability'][2]['if_open'] = radios_yesno('Claim in suit');
	$form['liability'][2]['description'] = '<p><u>DESCRIPTION OF CLAIM</u> Provide enough information 
		to allow evaluation:</p>';
	$form['liability'][2]['description']['error'] = textfield('Alleged act, error or omission 
		upon which Claimant bases claim:');
	$form['liability'][2]['description']['extent'] = textfield('Description of type and 
		extent of injury or damage allegedly sustained:');
	$form['liability'][2]['description']['condition_start'] = textfield('Patient’s Condition 
		at point of your involvement:');
	$form['liability'][2]['description']['condition_end'] = textfield('Patient’s Condition at 
		end of your treatment?');
	$form['liability'][2]['description']['narration'] = textarea('Provide a narration of the case, 
		relating events in chronological order emphasizing the dates of service and stating in 
		detail what was done each time the patient was seen professionally. You may use a separate 
		sheet to complete, sign and date.');
	$form['liability'][2]['application_terms_supplemental'] = terms_1($terms_desc);//@TODO
	$form['liability'][2]['application_terms_supplemental']['#attributes']['class'] .= 
		'edit-liability-application-terms_supplemental required';
	$form['liability'][2]['application_terms_supplemental']['#title'] = 'I Accept Terms';
	$form['liability'][2]['application_terms_supplemental']['#rules'] = array( 
		array('rule' => 'chars[1]', 'error' => 'You must accept the Terms to continue.'));	
									
return $form;
	
}