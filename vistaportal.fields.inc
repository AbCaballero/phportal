<?php
/**
 * Author: Andrew Browning
 * Company: Aner Group
 * Client: Vista Staffing Solutions
 * Date: November 19th, 2012
 * Notes: This file contains all of the form field functions 
 */


/*
 * textfield function
 */
function textfield($title, $size = 60, $maxlength = null) {
  $element = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t($title),
    '#size' => $size,
    '#maxlength' => $maxlength,
    '#filters' => array('trim'),
  );
  return $element;
}

/*
 * email field function
 */
function email($title, $size = 40) {
  $element = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t($title),
    '#maxlength' => 100,
    '#attributes' => array('class' => array('textfield-email')),
    '#rules' => array('email'),
    '#filters' => array('trim'),
    '#size' => $size,
  );
  return $element;
}

/*
 * state field function
 */
function state($title) {
  $element = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('AK', 'AL', 'AR', 'AZ', 'CA', 'CO', 'CT', 'DC', 'DE', 'FL', 'GA', 'HI', 'IA', 'ID', 'IL', 'IN', 'KS', 'KY', 'LA', 'MA', 'MD', 'ME', 'MI', 'MN', 'MO', 'MS', 'MT', 'NC', 'ND', 'NE', 'NH', 'NJ', 'NM', 'NV', 'NY', 'OH', 'OK', 'OR', 'PA', 'RI', 'SC', 'SD', 'TN', 'TX', 'UT', 'VA', 'VT', 'WA', 'WI', 'WV', 'WY')),
    '#attributes' => array('class' => 'select_state'),
    '#rules' => array('not_none'),
  );
  return $element;
}

/*
 * country field function
 * @TODO put these values in the database
 */
function country($title) {
  $element = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('Afghanistan','Aland Islands','Albania','Algeria',
			'American Samoa','Andorra','Angola','Anguilla','Antarctica','Antigua And Barbuda',
			'Argentina','Armenia','Aruba','Australia','Austria','Azerbaijan','Bahamas','Bahrain',
			'Bangladesh','Barbados','Belarus','Belgium','Belize','Benin','Bermuda','Bhutan',	'Bolivia',
			'Bosnia And Herzegovina','Botswana','Bouvet Island','Brazil','British Indian Ocean Territory',
			'Brunei Darussalam','Bulgaria','Burkina Faso','Burundi','Cambodia','Cameroon','Canada',
			'Cape Verde','Cayman Islands','Central African Republic','Chad','Chile','China',
			'Christmas Island','Cocos (Keeling) Islands','Colombia','Comoros','Congo',
			'Congo, The Democratic Republic Of The','Cook Islands','Costa Rica',"Cote D'Ivoire",'Croatia',
			'Cuba','Cyprus','Czech Republic','Denmark','Djibouti','Dominica','Dominican Republic','Ecuador',
			'Egypt','El Salvador','Equatorial Guinea','Eritrea','Estonia','Ethiopia',
			'Falkland Islands (Malvinas)','Faroe Islands','Fiji','Finland','France','French Guiana',
			'French Polynesia','French Southern Territories','Gabon','Gambia','Georgia','Germany','Ghana',
			'Gibraltar','Greece','Greenland','Grenada','Guadeloupe','Guam','Guatemala','Guernsey','Guinea',
			'Guinea-Bissau','Guyana','Haiti','Heard Island And Mcdonald Islands',
			'Holy See (Vatican City State)','Honduras','Hong Kong','Hungary','Iceland','India','Indonesia',
			'Iran, Islamic Republic Of','Iraq','Ireland','Isle Of Man','Israel','Italy','Jamaica','Japan',
			'Jersey','Jordan','Kazakhstan','Kenya','Kiribati',"Korea, Democratic People's Republic Of",
			'Korea, Republic Of','Kuwait','Kyrgyzstan',"Lao People's Democratic Republic",'Latvia',
			'Lebanon','Lesotho','Liberia','Libyan Arab Jamahiriya','Liechtenstein','Lithuania','Luxembourg',
			'Macao','Macedonia, The Former Yugoslav Republic Of','Madagascar','Malawi','Malaysia','Maldives',
			'Mali','Malta','Marshall Islands','Martinique','Mauritania','Mauritius','Mayotte','Mexico',
			'Micronesia, Federated States Of','Moldova, Republic Of','Monaco','Mongolia','Montserrat',
			'Morocco','Mozambique','Myanmar','Namibia','Nauru','Nepal','Netherlands','Netherlands Antilles',
			'New Caledonia','New Zealand','Nicaragua','Niger','Nigeria','Niue','Norfolk Island',
			'Northern Mariana Islands','Norway','Oman','Pakistan','Palau','Palestinian Territory','Panama',
			'Papua New Guinea','Paraguay','Peru','Philippines','Pitcairn','Poland','Portugal','Puerto Rico',
			'Qatar','Reunion','Romania','Russian Federation','Rwanda','Saint Helena','Saint Kitts And Nevis',
			'Saint Lucia','Saint Pierre And Miquelon','Saint Vincent And The Grenadines','Samoa','San Marino',
			'Sao Tome And Principe','Saudi Arabia','Senegal','Serbia And Montenegro','Seychelles',
			'Sierra Leone','Singapore','Slovakia','Slovenia','Solomon Islands','Somalia','South Africa',
			'South Georgia And The South Sandwich Islands','Spain','Sri Lanka','Sudan','Suriname',
			'Svalbard And Jan Mayen','Swaziland','Sweden','Switzerland','Syrian Arab Republic','Taiwan', 
			'Province Of China','Tajikistan','Tanzania, United Republic Of','Thailand','Timor-Leste',
			'Togo','Tokelau','Tonga','Trinidad And Tobago','Tunisia','Turkey','Turkmenistan',
			'Turks And Caicos Islands','Tuvalu','Uganda','Ukraine','United Arab Emirates','United Kingdom',
			'United States','United States Minor Outlying Islands','Uruguay','Uzbekistan','Vanuatu',
			'Venezuela','Viet Nam','Virgin Islands, British','Virgin Islands, U.S.','Wallis And Futuna',
			'Western Sahara','Yemen','Zambia','Zimbabwe')),
    '#attributes' => array('class' => 'select_country'),
    '#rules' => array('not_none'),
  );
  return $element;
}

/*
 * radios yes/no field function
 */ 
function radios_yesno($title) {
  $element = array(
    '#type' => 'radios',
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('Yes', 'No')),
    '#required' => TRUE,
    '#attributes' => array('class' => array('radios-yes-no')),
  );
  return $element;
}

/*
 * phone field function
 */
function phone($title) {
   $element = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t($title),
    '#size' => 24,
    '#attributes' => array('class' => array('textfield-phone')),
  );
  return $element;
} 

/*
 * zip code field function
 */
function zip($title) {
  $element = textfield('Zip Code', 5);
  $element['#rules'] = array('numeric', 'length[5]');
	$element['#title'] = t($title);
  return $element;
}

/*
 * ssn field function
 */ 
function textfield_ssn($title) {
  $element = array(
    '#prefix' => '<div class="ssn-field cf">',
    '#suffix' => '<div class="cf"></div></div>',
    '#title' => t($title),
    '#tree' => TRUE,
  );
  $el = array(
    '#type' => 'textfield',
    '#rules' => array('numeric'),
    '#filters' => array('trim'),
    '#required' => TRUE,
  );
  $element[] = $el;
  $element[0]['#title'] = t('Social Security Number');
  $element[0]['#size'] = $element[0]['#maxlength'] = 3;
  $element[] = $el;
  $element[1]['#size'] = $element[1]['#maxlength'] = 2;
  $element[] = $el;
  $element[2]['#size'] = $element[2]['#maxlength'] = 4;
  return $element;
}

/*
 * Date field popup
 */ 
function date_popup($title, $format = 'm-d-Y') {
  $element = array(
    '#type' => 'date_popup',
    '#date_format' => $format,
    '#prefix' => '<div class="date-popup">',
    '#title' => t($title),
    '#suffix' => '</div>',
    '#size' => 13,
    '#required' => TRUE,
  );
  return $element;
}

/*
 * radios board status field function
 */ 
function radios_board_status($title) {
  $element = array(
    '#type' => 'radios',
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('Certified', 'Prepared')),
    '#required' => TRUE,
    '#attributes' => array('class' => array('radios_board_status')),
  );
  return $element;
}

/*
 * checkbox field function
 */
function checkbox($title) {
  $element = array(
    '#type' => 'checkbox',
    '#title' => t($title),
    '#required' => TRUE,
  );
  return $element;
}

/*
 * licensure field function
 */
function lic($title) {
  $element = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('USMLE', 'NBME/NBOME', 'FLEX', 'COMLEX', 'Other')),
    //'#attributes' => array('class' => 'select-licence'),
    '#rules' => array('not_none'),
  );
  return $element;
}

/*
 * radios board status field function
 */ 
function radios_active_inactive_status($title) {
  $element = array(
    '#type' => 'radios',
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('Active', 'Inactive')),
    '#required' => TRUE,
    '#attributes' => array('class' => array('active_inactive_status')),
  );
  return $element;
}

/*
 * terms field function
 */ 
function terms_1($desc) {
  $element = array(
    '#type' => 'checkbox',
    '#required' => TRUE,
    '#title' => t($title),
    '#prefix' => '<div class="oa-terms-field">'. $desc,
    '#suffix' => '</div>',
  );
  return $element;
}

/*
 * checkboxes field function
 */
function checkboxes($title, $choices, $map = FALSE) {
  $element = array(
    '#type' => 'checkboxes',
    '#title' => t($title),
    '#options' => ($map) ? drupal_map_assoc($choices) : $choices,
    '#required' => TRUE,
    '#pdf_type' => 'oap_pdf_item_checkboxes',
  );
  return $element;
} 

/*
 * Allow for markup
 */
function markup($value) {
  return array('#value' => t($value));
}

/*
 * Create a fieldset
 */
function fieldset($title, $description = NULL) {
  $element = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t($title),
    '#description' => $description,
    '#collapsible' => TRUE,
  );
  return $element;
}

/*
 * This is the education dropdown
 */
function edu($title) {
  $element = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('High School diploma', 
    	'Associates degree', 'Bachelors degree', 'Master degree', 'Ph.D')),
    '#attributes' => array('class' => 'select_education'),
    '#rules' => array('not_none'),
  );
  return $element;
}

/*
 * children field function
 */
function children($title) {
  $element = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'other')),
    '#attributes' => array('class' => 'select_children'),
    '#rules' => array('not_none'),
  );
  return $element;
} 

/*
 * marital field function
 */
function marital_status($title) {
  $element = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t($title),
    '#options' => drupal_map_assoc(array('-Select-','Single', 'Married', 'Divorced', 'Widowed')),
    '#attributes' => array('class' => 'select_state'),
    '#rules' => array('not_none'),
  );
  return $element;
}

 
