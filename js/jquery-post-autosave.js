/**
 * @author: Andrew Browning
 * @company: Aner Group
 * @client: Vista Staffing Solutions
 * @date: December 26th, 2012
 * @notes: All code on this page executes after the autosave executes 
*/

(function ($) {
	Drupal.behaviors.post_autosave = {
		attach: function(context, settings){
			$checkNotApplicableIntern();
			$checkNotApplicableRes1();
			$checkNotApplicableRes2();
			$checkNotApplicableAffil();
			$checkNotCertified();
			$phoneNotReq();
			$checkNotApplicableFcvs();
			$checkNotApplicableDea();	
			$checkSelectAll();
			
			$('#edit-internship-na', context).change(function() {
				$checkNotApplicableIntern();
     });
     
     	$('#edit-residency1-na', context).change(function() {
				$checkNotApplicableRes1();
     });
     
      $('#edit-residency2-na', context).change(function() {
				$checkNotApplicableRes2();
     });
     
      $('#edit-affiliations-na', context).change(function() {
				$checkNotApplicableAffil();
     });
     
      $('#edit-not-board-cert', context).change(function() {
				$checkNotCertified();
     });
     
      $('#edit-licensure-na', context).change(function() {
				$checkNotApplicableFcvs();
     });
     
      $('#edit-deareg-0-na', context).change(function() {
				$checkNotApplicableDea();
     });
     
      $('#edit-deareg-0-schedules-all', context).change(function() {
				$checkSelectAll();
     });     
   }
 };
})(jQuery);


/*
 * Shut off the internship form validation if 'Not Applicable' is checked
 */

(function ($) {
	$checkNotApplicableIntern = function(){
		if($('#edit-internship-na').attr('checked')){
			var legend = $('#edit-internship-na').parentsUntil('legend', 'fieldset');
    	$('.form-required', legend).css('color', 'white');
    	$('.required', legend).removeClass("required");
  	}
  	else{
    	$("label[for = 'edit-internship-type'] .form-required").css("color", "red");
    	$("label[for = 'edit-internship-institution'] .form-required").css("color", "red");
    	$("label[for = 'edit-internship-country'] .form-required").css("color", "red");
    	$("label[for = 'edit-internship-state'] .form-required").css("color", "red");
    	$("label[for = 'edit-internship-city'] .form-required").css("color", "red");
    	$("label[for = 'edit-internship-date-from'] .form-required").css("color", "red");
    	$("label[for = 'edit-internship-date-to'] .form-required").css("color", "red");
    	$("label[for = 'edit-internship-prog-dir'] .form-required").css("color", "red");
  	}
  }	
}) (jQuery);



/*
 * Shut off the residency form validation if 'Not Applicable' is checked
 */

(function ($) {
	$checkNotApplicableRes1 = function(){
		if($('#edit-residency1-na').attr('checked')){
			var legend = $('#edit-residency1-na').parentsUntil('legend', 'fieldset');
    	$('.form-required', legend).css('color', 'white');
    	$('.required', legend).removeClass("required");
  	}
  	else{
    	$("label[for = 'edit-residency1-type'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency1-institution'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency1-country'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency1-state'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency1-city'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency1-date-from'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency1-date-to'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency1-prog-dir'] .form-required").css("color", "red");
  	}
  }	
}) (jQuery);


/*
 * Shut off the residency2 form validation if 'Not Applicable' is checked
 */

(function ($) {
	$checkNotApplicableRes2 = function(){
		if($('#edit-residency2-na').attr('checked')){
			var legend = $('#edit-residency2-na').parentsUntil('legend', 'fieldset');
    	$('.form-required', legend).css('color', 'white');
    	$('.required', legend).removeClass("required");
  	}
  	else{
    	$("label[for = 'edit-residency2-type'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency2-institution'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency2-country'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency2-state'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency2-city'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency2-date-from'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency2-date-to'] .form-required").css("color", "red");
    	$("label[for = 'edit-residency2-prog-dir'] .form-required").css("color", "red");
  	}
  }	
}) (jQuery);


/*
 * Shut off the affiliations form validation if 'Not Applicable' is checked
 */

(function ($) {
	$checkNotApplicableAffil = function(){
		if($('#edit-affiliations-na').attr('checked')){
			var legend = $('#edit-affiliations-na').parentsUntil('legend', 'fieldset');
    	$('.form-required', legend).css('color', 'white');
    	$('.required', legend).removeClass("required");
  	}
  	else{
    	$("label[for = 'edit-affiliations-type'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-institution'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-country'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-state'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-city'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-date-from'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-date-to'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-address'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-facility'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-zip'] .form-required").css("color", "red");
    	$("label[for = 'edit-affiliations-capacity'] .form-required").css("color", "red");
  	}
  }	
}) (jQuery);

/*
 * Shut off the certification form validation if 'Not Board Certified' is checked
 */

(function ($) {
	$checkNotCertified = function(){
		if($('#edit-not-board-cert').attr('checked')){
			var legend = $('#edit-not-board-cert').parentsUntil('legend', 'fieldset');
    	$('.form-required', legend).css('color', 'white');
    	$('.required', legend).removeClass("required");
  	}
  	else{
    	$("label[for = 'edit-board-status'] .form-required").css("color", "red");
    	$("label[for = 'edit-board'] .form-required").css("color", "red");
    	$("label[for = 'edit-certrecert'] .form-required").css("color", "red");
    	$("label[for = 'edit-specialty'] .form-required").css("color", "red");
    	$("label[for = 'edit-date'] .form-required").css("color", "red");
    	$("label[for = 'edit-certnum'] .form-required").css("color", "red");
  	}
  }	
}) (jQuery);

/*Remove the red asterisk for phone numbers*/

(function ($) {
	$phoneNotReq = function(){
    	$("label[for = 'edit-phone'] .form-required").css("color", "white");
  }	
}) (jQuery);

/*
 * Shut off FCVS if 'Not Applicable' is checked
 */

(function ($) {
	$checkNotApplicableFcvs = function(){
		if($('#edit-licensure-na').attr('checked')){
			var legend = $('#edit-licensure-na').parentsUntil('legend', 'fieldset');
    	$('.form-required', legend).css('color', 'white');
    	$('.required', legend).removeClass("required");
  	}
  	else{
    	$("label[for = 'edit-licensure-fcvs'] .form-required").css("color", "red");
  	}
  }	
}) (jQuery);

/*
 * Shut off the DEA Registration form validation if 'Not Applicable' is checked
 */

(function ($) {
	$checkNotApplicableDea = function(){
		if($('#edit-deareg-0-na').attr('checked')){
			var legend = $('#edit-deareg-0-na').parentsUntil('legend', 'fieldset');
    	$('.form-required', legend).css('color', 'white');
    	$('.required', legend).removeClass("required");
  	}
  	else{
    	$("label[for = 'edit-deareg-0-dea-country'] .form-required").css("color", "red");
    	$("label[for = 'edit-deareg-0-dea-lic-num'] .form-required").css("color", "red");
    	$("label[for = 'edit-deareg-0-dea-date-issued'] .form-required").css("color", "red");
    	$("label[for = 'edit-deareg-0-dea-date-expired'] .form-required").css("color", "red");
  	}
  }	
}) (jQuery);

/*
 * Select all schedules if 'All' is checked on DEA Registration form
 * TODO, Must find a way to loop through instead of using explicit
 * index references
 */

(function ($) {
	$checkSelectAll = function(){
		if($('#edit-deareg-0-schedules-all').attr('checked')){
    	$('#edit-deareg-0-schedules-2').attr('checked', 'checked');
    	$('#edit-deareg-0-schedules-3').attr('checked', 'checked');
    	$('#edit-deareg-0-schedules-4').attr('checked', 'checked');
    	$('#edit-deareg-0-schedules-2n').attr('checked', 'checked');
    	$('#edit-deareg-0-schedules-3n').attr('checked', 'checked');
    	$('#edit-deareg-0-schedules-5').attr('checked', 'checked');
  	}
  	else{
  		if(!$('#edit-deareg-0-schedules-all').attr('checked')){
  			$('#edit-deareg-0-schedules-2').attr('checked', false);
    		$('#edit-deareg-0-schedules-3').attr('checked', false);
    		$('#edit-deareg-0-schedules-4').attr('checked', false);
    		$('#edit-deareg-0-schedules-2n').attr('checked', false);
    		$('#edit-deareg-0-schedules-3n').attr('checked', false);
    		$('#edit-deareg-0-schedules-5').attr('checked', false);
  		}
  	}
  	
		if($('#edit-deareg-1-schedules-all').attr('checked')){
    	$('#edit-deareg-1-schedules-2').attr('checked', 'checked');
    	$('#edit-deareg-1-schedules-3').attr('checked', 'checked');
    	$('#edit-deareg-1-schedules-4').attr('checked', 'checked');
    	$('#edit-deareg-1-schedules-2n').attr('checked', 'checked');
    	$('#edit-deareg-1-schedules-3n').attr('checked', 'checked');
    	$('#edit-deareg-1-schedules-5').attr('checked', 'checked');
  	}
  	else{
  		if(!$('#edit-deareg-1-schedules-all').attr('checked')){
  			$('#edit-deareg-1-schedules-2').attr('checked', false);
    		$('#edit-deareg-1-schedules-3').attr('checked', false);
    		$('#edit-deareg-1-schedules-4').attr('checked', false);
    		$('#edit-deareg-1-schedules-2n').attr('checked', false);
    		$('#edit-deareg-1-schedules-3n').attr('checked', false);
    		$('#edit-deareg-1-schedules-5').attr('checked', false);
  		}
  	}
  	
		if($('#edit-deareg-2-schedules-all').attr('checked')){
    	$('#edit-deareg-2-schedules-2').attr('checked', 'checked');
    	$('#edit-deareg-2-schedules-3').attr('checked', 'checked');
    	$('#edit-deareg-2-schedules-4').attr('checked', 'checked');
    	$('#edit-deareg-2-schedules-2n').attr('checked', 'checked');
    	$('#edit-deareg-2-schedules-3n').attr('checked', 'checked');
    	$('#edit-deareg-2-schedules-5').attr('checked', 'checked');
  	}
  	else{
  		if(!$('#edit-deareg-2-schedules-all').attr('checked')){
  			$('#edit-deareg-2-schedules-2').attr('checked', false);
    		$('#edit-deareg-2-schedules-3').attr('checked', false);
    		$('#edit-deareg-2-schedules-4').attr('checked', false);
    		$('#edit-deareg-2-schedules-2n').attr('checked', false);
    		$('#edit-deareg-2-schedules-3n').attr('checked', false);
    		$('#edit-deareg-2-schedules-5').attr('checked', false);
  		}
  	}  	  	
  }	
}) (jQuery);
