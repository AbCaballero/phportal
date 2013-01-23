/**
 * @author: Andrew Browning
 * @company: Aner Group
 * @client: Vista Staffing Solutions
 * @date: December 26th, 2012
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
 * @notes: All code on this page executes after the autosave executes
 */
 
(function($) {
  Drupal.behaviors.post_autosave = {
    attach : function(context, settings) {
      $checkNotApplicableIntern();
      $checkNotApplicableRes();
      $checkNotApplicableFel();
      $checkNotApplicableAffil();
      $checkNotCertified();
      $phoneNotReq();
      $checkNotApplicableFcvs();
      $checkNotApplicableDea();
      $checkNotApplicableDea2();
      $checkSelectAll();
      $checkValidIndefYes();
      $checkValidIndefNo();
      $checkNotApplicableCert();
      $checkNotApplicableExam();
	  
	  /*This is for EXAM PAGE*/

      $('[class*="examtimes"]', context).change(function() {
        $selectExamFields();
      });
	  

      $('#edit-internship-na', context).change(function() {
        $checkNotApplicableIntern();
      });

      $('#edit-residency-0-na', context).change(function() {
        $checkNotApplicableRes();
      });

      $('#edit-fellowship-0-na', context).change(function() {

        $checkNotApplicableFel();
      });

      $('#edit-affiliations-not-applicable', context).change(function() {
        $checkNotApplicableAffil();
      });

      $('#edit-not-board-cert', context).change(function() {
        $checkNotCertified();
      });

      $('#edit-licensure-na', context).change(function() {
        $checkNotApplicableFcvs();
      });

      $('#edit-deareg-na', context).change(function() {
        $checkNotApplicableDea();
      });

      $('#edit-deareg-0-not0', context).change(function() {
        $checkNotApplicableDea2();
      });

      $('#edit-med-0-valid-indef0-yes', context).change(function() {
        $checkValidIndefYes();
      });

      $('#edit-med-0-valid-indef0-no', context).change(function() {
        $checkValidIndefNo();
      });

      $('#edit-certifications-board-0-not-applicable0', context).change(function() {
        $checkNotApplicableCert();
      });

      $('#edit-exams-state-cntr-not-applicable', context).change(function() {
        $checkNotApplicableExam();
      });

    }
  };
})(jQuery);

/*
 * Shut off the internship form validation if 'Not Applicable' is checked
 */

(function($) {
  $checkNotApplicableIntern = function() {

    if ($('#edit-internship-na').attr('checked')) {
      var legend = $('#edit-internship-na').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#internship-fieldset-wrapper input, #internship-fieldset-wrapper select').not(".form-checkbox, #edit-internship-na").attr('disabled', 'disabled');
    }
    else {
      $('#internship-fieldset-wrapper input, #internship-fieldset-wrapper select').not(".form-checkbox, #edit-internship-na").attr('disabled', false);
      $("label[for = 'edit-internship-0-type0'] .form-required").css("color", "red");
      $("label[for = 'edit-internship-0-institution0'] .form-required").css("color", "red");
      $("label[for = 'edit-internship-0-country0'] .form-required").css("color", "red");
      $("label[for = 'edit-internship-0-state0'] .form-required").css("color", "red");
      $("label[for = 'edit-internship-0-city0'] .form-required").css("color", "red");
      $("label[for = 'edit-internship-0-date-from0'] .form-required").css("color", "red");
      $("label[for = 'edit-internship-0-date-to0'] .form-required").css("color", "red");
      $("label[for = 'edit-internship-0-prog-dir0'] .form-required").css("color", "red");
    }
  }
})(jQuery);

/*
 * Shut off the residency form validation if 'Not Applicable' is checked
 */

/*(function ($) {
 $checkNotApplicableRes1 = function(){
 if($('#edit-residency1-na').attr('checked')){
 var legend = $('#edit-residency1-na').parentsUntil('legend', 'fieldset');
 $('.form-required', legend).css('color', 'white');
 $('.required', legend).removeClass("required");
 }
 else{
 $("label[for = 'edit-residency1-type'] .form-required").css("color", "red");
 $("label[for = 'edit-residency1-institution'] .form-required").css("color",
 "red");
 $("label[for = 'edit-residency1-country'] .form-required").css("color", "red");
 $("label[for = 'edit-residency1-state'] .form-required").css("color", "red");
 $("label[for = 'edit-residency1-city'] .form-required").css("color", "red");
 $("label[for = 'edit-residency1-date-from'] .form-required").css("color",
 "red");
 $("label[for = 'edit-residency1-date-to'] .form-required").css("color", "red");
 $("label[for = 'edit-residency1-prog-dir'] .form-required").css("color", "red");
 }
 }
 }) (jQuery);*/

/*
 * Shut off the residency2 form validation if 'Not Applicable' is checked
 */

/*(function ($) {
 $checkNotApplicableRes2 = function(){
 if($('#edit-residency2-na').attr('checked')){
 var legend = $('#edit-residency2-na').parentsUntil('legend', 'fieldset');
 $('.form-required', legend).css('color', 'white');
 $('.required', legend).removeClass("required");
 }

 else{
 $("label[for = 'edit-residency2-type'] .form-required").css("color", "red");
 $("label[for = 'edit-residency2-institution'] .form-required").css("color",
 "red");
 $("label[for = 'edit-residency2-country'] .form-required").css("color", "red");
 $("label[for = 'edit-residency2-state'] .form-required").css("color", "red");
 $("label[for = 'edit-residency2-city'] .form-required").css("color", "red");
 $("label[for = 'edit-residency2-date-from'] .form-required").css("color",
 "red");
 $("label[for = 'edit-residency2-date-to'] .form-required").css("color", "red");
 $("label[for = 'edit-residency2-prog-dir'] .form-required").css("color", "red");
 }
 }
 }) (jQuery);*/

/*
 * When checked asterisks change from red to white.  In addition input and select
 * fields are disable and greyed out
 *-Adam
 */

(function($) {
  $checkNotApplicableRes = function() {
<<<<<<< HEAD
    if ($('#edit-residency-0-na').attr('checked')) {
      var legend = $('#edit-residency-0-na').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#residency-fieldset-wrapper input, #residency-fieldset-wrapper select').not(".form-checkbox, #edit-residency-0-na").attr('disabled', 'disabled');
    }

    else {
      $('#residency-fieldset-wrapper input, #residency-fieldset-wrapper select').not(".form-checkbox, #edit-residency-0-na").attr('disabled', false);
=======
    if ($('#edit-residency-na').attr('checked')) {
      var legend = $('#edit-residency-na').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#residency-fieldset-wrapper input, #residency-fieldset-wrapper select').not(".form-checkbox, #edit-residency-na").attr('disabled', 'disabled');
    }

    else {
      $('#residency-fieldset-wrapper input, #residency-fieldset-wrapper select').not(".form-checkbox, #edit-residency-na").attr('disabled', false);
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
      $("label[for = 'edit-residency-0-type0'] .form-required").css("color", "red");
      $("label[for = 'edit-residency-0-institution0'] .form-required").css("color", "red");
      $("label[for = 'edit-residency-0-country0'] .form-required").css("color", "red");
      $("label[for = 'edit-residency-0-state0'] .form-required").css("color", "red");
      $("label[for = 'edit-residency-0-city0'] .form-required").css("color", "red");
      $("label[for = 'edit-residency-0-date-from0'] .form-required").css("color", "red");
      $("label[for = 'edit-residency-0-date-to0'] .form-required").css("color", "red");
      $("label[for = 'edit-residency-0-prog-dir0'] .form-required").css("color", "red");
    }
  }
})(jQuery);

/*
 * When checked asterisks change from red to white.  In addition input and select
 * fields are disabled and greyed out
 *-Adam
 */

(function($) {
  $checkNotApplicableFel = function() {
<<<<<<< HEAD
    if ($('#edit-fellowship-0-na').attr('checked')) {
      var legend = $('#edit-fellowship-0-na').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#fellowship-fieldset-wrapper input, #fellowship-fieldset-wrapper select').not(".form-checkbox, #edit-fellowship-0-na").attr('disabled', 'disabled');
    }

    else {
      $('#fellowship-fieldset-wrapper input, #fellowship-fieldset-wrapper select').not(".form-checkbox, #edit-fellowship-0-na").attr('disabled', false);
=======
    if ($('#edit-fellowship-na').attr('checked')) {
      var legend = $('#edit-fellowship-na').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#fellowship-fieldset-wrapper input, #fellowship-fieldset-wrapper select').not(".form-checkbox, #edit-fellowship-na").attr('disabled', 'disabled');
    }

    else {
      $('#fellowship-fieldset-wrapper input, #fellowship-fieldset-wrapper select').not(".form-checkbox, #edit-fellowship-na").attr('disabled', false);
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
      $("label[for = 'edit-fellowship-0-type0'] .form-required").css("color", "red");
      $("label[for = 'edit-fellowship-0-institution0'] .form-required").css("color", "red");
      $("label[for = 'edit-fellowship-0-country0'] .form-required").css("color", "red");
      $("label[for = 'edit-fellowship-0-state0'] .form-required").css("color", "red");
      $("label[for = 'edit-fellowship-0-city0'] .form-required").css("color", "red");
      $("label[for = 'edit-fellowship-0-date-from0'] .form-required").css("color", "red");
      $("label[for = 'edit-fellowship-0-date-to0'] .form-required").css("color", "red");
      $("label[for = 'edit-fellowship-0-prog-dir0'] .form-required").css("color", "red");
    }
  }
})(jQuery);
<<<<<<< HEAD
=======
=======
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

>>>>>>> fca29b309f4c68500be076725e1d93310cf929a5
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730

/*
 * Shut off the affiliations form validation if 'Not Applicable' is checked
 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
/*
 *In addition input and select fields are disabled and greyed out
 *-Adam
 */

(function($) {
  $checkNotApplicableAffil = function() {
    if ($('#edit-affiliations-not-applicable').attr('checked')) {
      var legend = $('#edit-affiliations-cntr-0-facility0').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#affiliations-fieldset-wrapper input, #affiliations-fieldset-wrapper select').attr('disabled', 'disabled');
    }
    else {
      $('#affiliations-fieldset-wrapper input, #affiliations-fieldset-wrapper select').attr('disabled', false);
      $("label[for = 'edit-affiliations-cntr-0-facility0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-date-from0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-date-to0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-address0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-country0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-state0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-city0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-zip0'] .form-required").css("color", "red");
      $("label[for = 'edit-affiliations-cntr-0-capacity0'] .form-required").css("color", "red");
    }
  }
})(jQuery);
<<<<<<< HEAD
=======
=======

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
>>>>>>> fca29b309f4c68500be076725e1d93310cf929a5
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730

/*
 * Shut off the certification form validation if 'Not Board Certified' is checked
 */

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
(function($) {
  $checkNotCertified = function() {
    if ($('#edit-not-board-cert').attr('checked')) {
      var legend = $('#edit-not-board-cert').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
    }
    else {
      $("label[for = 'edit-board-status'] .form-required").css("color", "red");
      $("label[for = 'edit-board'] .form-required").css("color", "red");
      $("label[for = 'edit-certrecert'] .form-required").css("color", "red");
      $("label[for = 'edit-specialty'] .form-required").css("color", "red");
      $("label[for = 'edit-date'] .form-required").css("color", "red");
      $("label[for = 'edit-certnum'] .form-required").css("color", "red");
    }
  }
})(jQuery);

/*Remove the red asterisk for phone numbers*/

(function($) {
  $phoneNotReq = function() {
    $("label[for = 'edit-phone'] .form-required").css("color", "white");
  }
})(jQuery);

/*
 * Shut off FCVS if 'Not Applicable' is checked
 *
 * When checked asterisks change from red to white.  In addition input and select
 * fields are disable and greyed out
 *-Adam
 */

(function($) {
  $checkNotApplicableFcvs = function() {
    if ($('#edit-licensure-na').attr('checked')) {
      var legend = $('#edit-licensure-na').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#edit-licensure input, #edit-licensure select').not(".form-checkbox, #edit-licensure-na").attr('disabled', 'disabled');
    }
    else {
      $('#edit-licensure input, #edit-licensure select').not(".form-checkbox, #edit-licensure-na").attr('disabled', false);
      $("label[for = 'edit-licensure-fcvs'] .form-required").css("color", "red");
    }
  }
})(jQuery);

/*
 * Shut off the DEA Registration form validation if 'Not Applicable' is checked
 *
 * When checked asterisks change from red to white.  In addition input and select
 * fields are disabled and greyed out
 *-Adam
 */

(function($) {
  $checkNotApplicableDea = function() {
    if ($('#edit-deareg-na').attr('checked')) {
      var legend = $('#edit-deareg-na').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#deareg-fieldset-wrapper select').not(".form-checkbox, #edit-deareg-na", ".form-checkbox, #edit-deareg-0-pending", ".form-checkbox, #edit-deareg-0-not", ".form-text, #edit-deareg-language-spoken").attr('disabled', 'disabled');
      $('#edit-deareg-0-dea-lic-num').attr('disabled', true);
      $('#edit-deareg-add-another').attr('disabled', true);
    }
    else {
      $('#deareg-fieldset-wrapper select').not(".form-checkbox, #edit-deareg-na", ".form-checkbox, #edit-deareg-0-pending", ".form-checkbox, #edit-deareg-0-not", ".form-text, #edit-deareg-language-spoken").attr('disabled', false);
      $('#edit-deareg-0-dea-lic-num').attr('disabled', false);
      $('#edit-deareg-add-another').attr('disabled', false);
      $("label[for = 'edit-deareg-0-dea-country'] .form-required").css("color", "red");
      $("label[for = 'edit-deareg-0-dea-lic-num'] .form-required").css("color", "red");
      $("label[for = 'edit-deareg-0-dea-date-issued'] .form-required").css("color", "red");
      $("label[for = 'edit-deareg-0-dea-date-expired'] .form-required").css("color", "red");
    }
  }
})(jQuery);
/*
 * This disables and enables the options (All, 2, 3, 4, 2N, 3N, 5) and when
 * disable they are uncheck, vice versa.
 * -Adam
 */
(function($) {
  $checkNotApplicableDea2 = function() {
    if ($('#edit-deareg-0-not0').attr('checked')) {
      $('#edit-deareg-0-all0').attr('disabled', true).attr('checked', false);
      $('#edit-deareg-0-schedules20').attr('disabled', true).attr('checked', false);
      $('#edit-deareg-0-schedules30').attr('disabled', true).attr('checked', false);
      $('#edit-deareg-0-schedules40').attr('disabled', true).attr('checked', false);
      $('#edit-deareg-0-schedules2n0').attr('disabled', true).attr('checked', false);
      $('#edit-deareg-0-schedules3n0').attr('disabled', true).attr('checked', false);
      $('#edit-deareg-0-schedules50').attr('disabled', true).attr('checked', false);
    }
    else {
      if (!$('#edit-deareg-0-not0').attr('checked')) {
        $('#edit-deareg-0-all0').attr('disabled', false).attr('checked', true);
        $('#edit-deareg-0-schedules20').attr('disabled', false).attr('checked', true);
        $('#edit-deareg-0-schedules30').attr('disabled', false).attr('checked', true);
        $('#edit-deareg-0-schedules40').attr('disabled', false).attr('checked', true);
        $('#edit-deareg-0-schedules2n0').attr('disabled', false).attr('checked', true);
        $('#edit-deareg-0-schedules3n0').attr('disabled', false).attr('checked', true);
        $('#edit-deareg-0-schedules50').attr('disabled', false).attr('checked', true);
      }
    }
  }
})(jQuery);
<<<<<<< HEAD
=======
=======
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

>>>>>>> fca29b309f4c68500be076725e1d93310cf929a5
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
/*
 * Select all schedules if 'All' is checked on DEA Registration form
 * TODO, Must find a way to loop through instead of using explicit
 * index references
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
 *
 * When All is checked/unchecked the other options follow.
 * -Adam
 */

(function($) {
  $checkSelectAll = function() {
    if ($('#edit-deareg-0-all').attr('checked')) {
      $('#edit-deareg-0-schedules-2').attr('checked', 'checked');
      $('#edit-deareg-0-schedules-3').attr('checked', 'checked');
      $('#edit-deareg-0-schedules-4').attr('checked', 'checked');
      $('#edit-deareg-0-schedules-2n').attr('checked', 'checked');
      $('#edit-deareg-0-schedules-3n').attr('checked', 'checked');
      $('#edit-deareg-0-schedules-5').attr('checked', 'checked');
    }
    else {
      if (!$('#edit-deareg-0-all').attr('checked')) {
        $('#edit-deareg-0-schedules-2').attr('checked', false);
        $('#edit-deareg-0-schedules-3').attr('checked', false);
        $('#edit-deareg-0-schedules-4').attr('checked', false);
        $('#edit-deareg-0-schedules-2n').attr('checked', false);
        $('#edit-deareg-0-schedules-3n').attr('checked', false);
        $('#edit-deareg-0-schedules-5').attr('checked', false);
      }
    }
    /*if($('#edit-deareg-1-all').attr('checked')){
     $('#edit-deareg-1-schedules-2').attr('checked', 'checked');
     $('#edit-deareg-1-schedules-3').attr('checked', 'checked');
     $('#edit-deareg-1-schedules-4').attr('checked', 'checked');
     $('#edit-deareg-1-schedules-2n').attr('checked', 'checked');
     $('#edit-deareg-1-schedules-3n').attr('checked', 'checked');
     $('#edit-deareg-1-schedules-5').attr('checked', 'checked');
     }
     else{
     if(!$('#edit-deareg-1-all').attr('checked')){
     $('#edit-deareg-1-schedules-2').attr('checked', false);
     $('#edit-deareg-1-schedules-3').attr('checked', false);
     $('#edit-deareg-1-schedules-4').attr('checked', false);
     $('#edit-deareg-1-schedules-2n').attr('checked', false);
     $('#edit-deareg-1-schedules-3n').attr('checked', false);
     $('#edit-deareg-1-schedules-5').attr('checked', false);
     }
     }

     if($('#edit-deareg-2-all').attr('checked')){
     $('#edit-deareg-2-schedules-2').attr('checked', 'checked');
     $('#edit-deareg-2-schedules-3').attr('checked', 'checked');
     $('#edit-deareg-2-schedules-4').attr('checked', 'checked');
     $('#edit-deareg-2-schedules-2n').attr('checked', 'checked');
     $('#edit-deareg-2-schedules-3n').attr('checked', 'checked');
     $('#edit-deareg-2-schedules-5').attr('checked', 'checked');
     }
     else{
     if(!$('#eedit-deareg-2-all').attr('checked')){
     $('#edit-deareg-2-schedules-2').attr('checked', false);
     $('#edit-deareg-2-schedules-3').attr('checked', false);
     $('#edit-deareg-2-schedules-4').attr('checked', false);
     $('#edit-deareg-2-schedules-2n').attr('checked', false);
     $('#edit-deareg-2-schedules-3n').attr('checked', false);
     $('#edit-deareg-2-schedules-5').attr('checked', false);
     }
     }*/
  }
})(jQuery);

/*
 * This removes the asterisk when the radio = yes
 * -Adam
 */
(function($) {
  $checkValidIndefYes = function() {
    if ($('#edit-med-0-valid-indef0-yes').attr('checked')) {
      $("label[for = 'edit-med-0-exp-date0'] .form-required").css("color", "white");
      $("label[for = 'edit-med-0-exp-date0'] .required").removeClass("required");
      $("label[for = 'edit-med-0-exp-date0-month'] .form-required").css("color", "white");
      $("label[for = 'edit-med-0-exp-date0-month'] .required").removeClass("required");
      $("label[for = 'edit-med-0-exp-date0-year'] .form-required").css("color", "white");
      $("label[for = 'edit-med-0-exp-date0-year'] .required").removeClass("required");
    }
    else {
      $("label[for = 'edit-med-0-exp-date0'] .form-required").css("color", "red");
      $("label[for = 'edit-med-0-exp-date0-month'] .form-required").css("color", "red");
      $("label[for = 'edit-med-0-exp-date0-year'] .form-required").css("color", "red");
    }
  }
})(jQuery);

(function($) {
  $checkValidIndefNo = function() {
    if ($('#edit-med-0-valid-indef0-no').attr('checked')) {
      $("label[for = 'edit-med-0-exp-date0'] .form-required").css("color", "red");
      $("label[for = 'edit-med-0-exp-date0-month'] .form-required").css("color", "red");
      $("label[for = 'edit-med-0-exp-date0-year'] .form-required").css("color", "red");
    }
    else {

      $("label[for = 'edit-med-0-exp-date0'] .form-required").css("color", "white");
      $("label[for = 'edit-med-0-exp-date0'] .required").removeClass("required");
      $("label[for = 'edit-med-0-exp-date0-month'] .form-required").css("color", "white");
      $("label[for = 'edit-med-0-exp-date0-month'] .required").removeClass("required");
      $("label[for = 'edit-med-0-exp-date0-year'] .form-required").css("color", "white");
      $("label[for = 'edit-med-0-exp-date0-year'] .required").removeClass("required");
    }
  }
})(jQuery);

/*
 * Shut off the certification form validation if 'Not Applicable' is checked
 */

(function($) {
  $checkNotApplicableCert = function() {

    if ($('#edit-certifications-board-0-not-applicable0').attr('checked')) {
      var legend = $('#edit-certifications-board-0-not-applicable0').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#board-fieldset-wrapper input, #board-fieldset-wrapper select').not(".form-checkbox, edit-certifications-board-0-not-applicable0").attr('disabled', 'disabled');
    }
    else {
      $('#board-fieldset-wrapper input, #board-fieldset-wrapper select').not(".form-checkbox, edit-certifications-board-0-not-applicable0").attr('disabled', false);
      $("label[for = 'edit-certifications-board-0-board-status0-certified'] .form-required").css("color", "red");
      $("label[for = 'edit-certifications-board-0-board-sciences0'] .form-required").css("color", "red");
      $("label[for = 'edit-certifications-board-0-cert-recert0'] .form-required").css("color", "red");
      $("label[for = 'edit-certifications-board-0-cert-number0'] .form-required").css("color", "red");
      $("label[for = 'edit-certifications-board-0-board-exp-date0'] .form-required").css("color", "red");
    }
  }
})(jQuery);



<<<<<<< HEAD
(function($) {
  $checkNotApplicableExam = function() {
    if ($('#edit-exams-state-cntr-not-applicable').attr('checked')) {
      var legend = $('#edit-exams-state-cntr-not-applicable').parentsUntil('legend', 'fieldset');
      $('.form-required', legend).css('color', 'white');
      $('.required', legend).removeClass("required");
      $('#state-exams-fieldset-wrapper input, #state-exams-fieldset-wrapper select').not('.form-checkbox, #edit-exams-state-cntr-not-applicable').attr('disabled', 'disabled');

    }
    else {
      $('#state-exams-fieldset-wrapper input, #state-exams-fieldset-wrapper select').not('.form-checkbox, #edit-exams-state-cntr-not-applicable').attr('disabled', false);
      $("label[for = 'edit-exams-state-cntr-0-state0'] .form-required").css("color", "red");
      $("label[for = 'edit-exams-state-cntr-0-state-exam-date0'] .form-required").css("color", "red");
      $("checkbox[for = 'edit-exams-state-cntr-0-result0'] .form-required").css("color", "red");
    }
  }
})(jQuery); 
=======
/*
 * Hide and show exam score and date fields based upon value of select.
 * @TODO find a better way, i.e., 10 lines of code instead of 437 lines
 */

(function($) {
  $selectExamFields = function() {

    if ($('[class*="examtimes0"]').val() == 1) {
      $('[id*="et-6-0"]').hide();
      $('[id*="et-5-0"]').hide();
      $('[id*="et-4-0"]').hide();
      $('[id*="et-3-0"]').hide();
      $('[id*="et-2-0"]').hide();
      $('[id*="et-1-0"]').hide();
    }

    if ($('[class*="examtimes1"]').val() == 1) {
      $('[id*="et-6-1"]').hide();
      $('[id*="et-5-1"]').hide();
      $('[id*="et-4-1"]').hide();
      $('[id*="et-3-1"]').hide();
      $('[id*="et-2-1"]').hide();
      $('[id*="et-1-1"]').hide();
    }

    if ($('[class*="examtimes2"]').val() == 1) {
      $('[id*="et-6-2"]').hide();
      $('[id*="et-5-2"]').hide();
      $('[id*="et-4-2"]').hide();
      $('[id*="et-3-2"]').hide();
      $('[id*="et-2-2"]').hide();
      $('[id*="et-1-2"]').hide();
    }

    if ($('[class*="examtimes3"]').val() == 1) {
      $('[id*="et-6-3"]').hide();
      $('[id*="et-5-3"]').hide();
      $('[id*="et-4-3"]').hide();
      $('[id*="et-3-3"]').hide();
      $('[id*="et-2-3"]').hide();
      $('[id*="et-1-3"]').hide();
    }

    if ($('[class*="examtimes4"]').val() == 1) {
      $('[id*="et-6-4"]').hide();
      $('[id*="et-5-4"]').hide();
      $('[id*="et-4-4"]').hide();
      $('[id*="et-3-4"]').hide();
      $('[id*="et-2-4"]').hide();
      $('[id*="et-1-4"]').hide();
    }

    if ($('[class*="examtimes5"]').val() == 1) {
      $('[id*="et-6-5"]').hide();
      $('[id*="et-5-5"]').hide();
      $('[id*="et-4-5"]').hide();
      $('[id*="et-3-5"]').hide();
      $('[id*="et-2-5"]').hide();
      $('[id*="et-1-5"]').hide();
    }

    if ($('[class*="examtimes6"]').val() == 1) {
      $('[id*="et-6-6"]').hide();
      $('[id*="et-5-6"]').hide();
      $('[id*="et-4-6"]').hide();
      $('[id*="et-3-6"]').hide();
      $('[id*="et-2-6"]').hide();
      $('[id*="et-1-6"]').hide();
    }

    if ($('[class*="examtimes0"]').val() == 2) {
      $('[id*="et-6-0"]').hide();
      $('[id*="et-5-0"]').hide();
      $('[id*="et-4-0"]').hide();
      $('[id*="et-3-0"]').hide();
      $('[id*="et-2-0"]').hide();
      $('[id*="et-1-0"]').show();
    }
    if ($('[class*="examtimes1"]').val() == 2) {
      $('[id*="et-6-1"]').hide();
      $('[id*="et-5-1"]').hide();
      $('[id*="et-4-1"]').hide();
      $('[id*="et-3-1"]').hide();
      $('[id*="et-2-1"]').hide();
      $('[id*="et-1-1"]').show();
    }

    if ($('[class*="examtimes2"]').val() == 2) {
      $('[id*="et-6-2"]').hide();
      $('[id*="et-5-2"]').hide();
      $('[id*="et-4-2"]').hide();
      $('[id*="et-3-2"]').hide();
      $('[id*="et-2-2"]').hide();
      $('[id*="et-1-2"]').show();
    }

    if ($('[class*="examtimes3"]').val() == 2) {
      $('[id*="et-6-3"]').hide();
      $('[id*="et-5-3"]').hide();
      $('[id*="et-4-3"]').hide();
      $('[id*="et-3-3"]').hide();
      $('[id*="et-2-3"]').hide();
      $('[id*="et-1-3"]').show();
    }

    if ($('[class*="examtimes4"]').val() == 2) {
      $('[id*="et-6-4"]').hide();
      $('[id*="et-5-4"]').hide();
      $('[id*="et-4-4"]').hide();
      $('[id*="et-3-4"]').hide();
      $('[id*="et-2-4"]').hide();
      $('[id*="et-1-4"]').show();
    }

    if ($('[class*="examtimes5"]').val() == 2) {
      $('[id*="et-6-5"]').hide();
      $('[id*="et-5-5"]').hide();
      $('[id*="et-4-5"]').hide();
      $('[id*="et-3-5"]').hide();
      $('[id*="et-2-5"]').hide();
      $('[id*="et-1-5"]').show();
    }

    if ($('[class*="examtimes6"]').val() == 2) {
      $('[id*="et-6-6"]').hide();
      $('[id*="et-5-6"]').hide();
      $('[id*="et-4-6"]').hide();
      $('[id*="et-3-6"]').hide();
      $('[id*="et-2-6"]').hide();
      $('[id*="et-1-6"]').show();
    }

    if ($('[class*="examtimes0"]').val() == 3) {
      $('[id*="et-6-0"]').hide();
      $('[id*="et-5-0"]').hide();
      $('[id*="et-4-0"]').hide();
      $('[id*="et-3-0"]').hide();
      $('[id*="et-2-0"]').show();
      $('[id*="et-1-0"]').show();
    }

    if ($('[class*="examtimes1"]').val() == 3) {
      $('[id*="et-6-1"]').hide();
      $('[id*="et-5-1"]').hide();
      $('[id*="et-4-1"]').hide();
      $('[id*="et-3-1"]').hide();
      $('[id*="et-2-1"]').show();
      $('[id*="et-1-1"]').show();
    }

    if ($('[class*="examtimes2"]').val() == 3) {
      $('[id*="et-6-2"]').hide();
      $('[id*="et-5-2"]').hide();
      $('[id*="et-4-2"]').hide();
      $('[id*="et-3-2"]').hide();
      $('[id*="et-2-2"]').show();
      $('[id*="et-1-2"]').show();
    }

    if ($('[class*="examtimes3"]').val() == 3) {
      $('[id*="et-6-3"]').hide();
      $('[id*="et-5-3"]').hide();
      $('[id*="et-4-3"]').hide();
      $('[id*="et-3-3"]').hide();
      $('[id*="et-2-3"]').show();
      $('[id*="et-1-3"]').show();
    }

    if ($('[class*="examtimes4"]').val() == 3) {
      $('[id*="et-6-4"]').hide();
      $('[id*="et-5-4"]').hide();
      $('[id*="et-4-4"]').hide();
      $('[id*="et-3-4"]').hide();
      $('[id*="et-2-4"]').show();
      $('[id*="et-1-4"]').show();
    }

    if ($('[class*="examtimes5"]').val() == 3) {
      $('[id*="et-6-5"]').hide();
      $('[id*="et-5-5"]').hide();
      $('[id*="et-4-5"]').hide();
      $('[id*="et-3-5"]').hide();
      $('[id*="et-2-5"]').show();
      $('[id*="et-1-5"]').show();
    }

    if ($('[class*="examtimes6"]').val() == 3) {
      $('[id*="et-6-6"]').hide();
      $('[id*="et-5-6"]').hide();
      $('[id*="et-4-6"]').hide();
      $('[id*="et-3-6"]').hide();
      $('[id*="et-2-6"]').show();
      $('[id*="et-1-6"]').show();
    }

    if ($('[class*="examtimes0"]').val() == 4) {
      $('[id*="et-6-0"]').hide();
      $('[id*="et-5-0"]').hide();
      $('[id*="et-4-0"]').hide();
      $('[id*="et-3-0"]').show();
      $('[id*="et-2-0"]').show();
      $('[id*="et-1-0"]').show();
    }

    if ($('[class*="examtimes1"]').val() == 4) {
      $('[id*="et-6-1"]').hide();
      $('[id*="et-5-1"]').hide();
      $('[id*="et-4-1"]').hide();
      $('[id*="et-3-1"]').show();
      $('[id*="et-2-1"]').show();
      $('[id*="et-1-1"]').show();
    }

    if ($('[class*="examtimes2"]').val() == 4) {
      $('[id*="et-6-2"]').hide();
      $('[id*="et-5-2"]').hide();
      $('[id*="et-4-2"]').hide();
      $('[id*="et-3-2"]').show();
      $('[id*="et-2-2"]').show();
      $('[id*="et-1-2"]').show();
    }

    if ($('[class*="examtimes3"]').val() == 4) {
      $('[id*="et-6-3"]').hide();
      $('[id*="et-5-3"]').hide();
      $('[id*="et-4-3"]').hide();
      $('[id*="et-3-3"]').show();
      $('[id*="et-2-3"]').show();
      $('[id*="et-1-3"]').show();
    }

    if ($('[class*="examtimes4"]').val() == 4) {
      $('[id*="et-6-4"]').hide();
      $('[id*="et-5-4"]').hide();
      $('[id*="et-4-4"]').hide();
      $('[id*="et-3-4"]').show();
      $('[id*="et-2-4"]').show();
      $('[id*="et-1-4"]').show();
    }

    if ($('[class*="examtimes5"]').val() == 4) {
      $('[id*="et-6-5"]').hide();
      $('[id*="et-5-5"]').hide();
      $('[id*="et-4-5"]').hide();
      $('[id*="et-3-5"]').show();
      $('[id*="et-2-5"]').show();
      $('[id*="et-1-5"]').show();
    }

    if ($('[class*="examtimes6"]').val() == 4) {
      $('[id*="et-6-6"]').hide();
      $('[id*="et-5-6"]').hide();
      $('[id*="et-4-6"]').hide();
      $('[id*="et-3-6"]').show();
      $('[id*="et-2-6"]').show();
      $('[id*="et-1-6"]').show();
    }

    if ($('[class*="examtimes0"]').val() == 5) {
      $('[id*="et-6-0"]').hide();
      $('[id*="et-5-0"]').hide();
      $('[id*="et-4-0"]').hide();
      $('[id*="et-3-0"]').show();
      $('[id*="et-2-0"]').show();
      $('[id*="et-1-0"]').show();
    }

    if ($('[class*="examtimes1"]').val() == 5) {
      $('[id*="et-6-1"]').hide();
      $('[id*="et-5-1"]').hide();
      $('[id*="et-4-1"]').hide();
      $('[id*="et-3-1"]').show();
      $('[id*="et-2-1"]').show();
      $('[id*="et-1-1"]').show();
    }

    if ($('[class*="examtimes2"]').val() == 5) {
      $('[id*="et-6-2"]').hide();
      $('[id*="et-5-2"]').hide();
      $('[id*="et-4-2"]').hide();
      $('[id*="et-3-2"]').show();
      $('[id*="et-2-2"]').show();
      $('[id*="et-1-2"]').show();
    }

    if ($('[class*="examtimes3"]').val() == 5) {
      $('[id*="et-6-3"]').hide();
      $('[id*="et-5-3"]').hide();
      $('[id*="et-4-3"]').hide();
      $('[id*="et-3-3"]').show();
      $('[id*="et-2-3"]').show();
      $('[id*="et-1-3"]').show();
    }

    if ($('[class*="examtimes4"]').val() == 5) {
      $('[id*="et-6-4"]').hide();
      $('[id*="et-5-4"]').hide();
      $('[id*="et-4-4"]').hide();
      $('[id*="et-3-4"]').show();
      $('[id*="et-2-4"]').show();
      $('[id*="et-1-4"]').show();
    }

    if ($('[class*="examtimes5"]').val() == 5) {
      $('[id*="et-6-5"]').hide();
      $('[id*="et-5-5"]').hide();
      $('[id*="et-4-5"]').hide();
      $('[id*="et-3-5"]').show();
      $('[id*="et-2-5"]').show();
      $('[id*="et-1-5"]').show();
    }

    if ($('[class*="examtimes6"]').val() == 5) {
      $('[id*="et-6-6"]').hide();
      $('[id*="et-5-6"]').hide();
      $('[id*="et-4-6"]').hide();
      $('[id*="et-3-6"]').show();
      $('[id*="et-2-6"]').show();
      $('[id*="et-1-6"]').show();
    }

    if ($('[class*="examtimes0"]').val() == 6) {
      $('[id*="et-6-0"]').hide();
      $('[id*="et-5-0"]').hide();
      $('[id*="et-4-0"]').hide();
      $('[id*="et-3-0"]').show();
      $('[id*="et-2-0"]').show();
      $('[id*="et-1-0"]').show();
    }

    if ($('[class*="examtimes1"]').val() == 6) {
      $('[id*="et-6-1"]').hide();
      $('[id*="et-5-1"]').hide();
      $('[id*="et-4-1"]').hide();
      $('[id*="et-3-1"]').show();
      $('[id*="et-2-1"]').show();
      $('[id*="et-1-1"]').show();
    }

    if ($('[class*="examtimes2"]').val() == 6) {
      $('[id*="et-6-2"]').hide();
      $('[id*="et-5-2"]').hide();
      $('[id*="et-4-2"]').hide();
      $('[id*="et-3-2"]').show();
      $('[id*="et-2-2"]').show();
      $('[id*="et-1-2"]').show();
    }

    if ($('[class*="examtimes3"]').val() == 6) {
      $('[id*="et-6-3"]').hide();
      $('[id*="et-5-3"]').hide();
      $('[id*="et-4-3"]').hide();
      $('[id*="et-3-3"]').show();
      $('[id*="et-2-3"]').show();
      $('[id*="et-1-3"]').show();
    }

    if ($('[class*="examtimes4"]').val() == 6) {
      $('[id*="et-6-4"]').hide();
      $('[id*="et-5-4"]').hide();
      $('[id*="et-4-4"]').hide();
      $('[id*="et-3-4"]').show();
      $('[id*="et-2-4"]').show();
      $('[id*="et-1-4"]').show();
    }

    if ($('[class*="examtimes5"]').val() == 6) {
      $('[id*="et-6-5"]').hide();
      $('[id*="et-5-5"]').hide();
      $('[id*="et-4-5"]').hide();
      $('[id*="et-3-5"]').show();
      $('[id*="et-2-5"]').show();
      $('[id*="et-1-5"]').show();
    }

    if ($('[class*="examtimes6"]').val() == 6) {
      $('[id*="et-6-6"]').hide();
      $('[id*="et-5-6"]').hide();
      $('[id*="et-4-6"]').hide();
      $('[id*="et-3-6"]').show();
      $('[id*="et-2-6"]').show();
      $('[id*="et-1-6"]').show();
    }

    if ($('[class*="examtimes0"]').val() == 7) {
      $('[id*="et-6-0"]').hide();
      $('[id*="et-5-0"]').hide();
      $('[id*="et-4-0"]').hide();
      $('[id*="et-3-0"]').show();
      $('[id*="et-2-0"]').show();
      $('[id*="et-1-0"]').show();
    }

    if ($('[class*="examtimes1"]').val() == 7) {
      $('[id*="et-6-1"]').hide();
      $('[id*="et-5-1"]').hide();
      $('[id*="et-4-1"]').hide();
      $('[id*="et-3-1"]').show();
      $('[id*="et-2-1"]').show();
      $('[id*="et-1-1"]').show();
    }

    if ($('[class*="examtimes2"]').val() == 7) {
      $('[id*="et-6-2"]').hide();
      $('[id*="et-5-2"]').hide();
      $('[id*="et-4-2"]').hide();
      $('[id*="et-3-2"]').show();
      $('[id*="et-2-2"]').show();
      $('[id*="et-1-2"]').show();
    }

    if ($('[class*="examtimes3"]').val() == 7) {
      $('[id*="et-6-3"]').hide();
      $('[id*="et-5-3"]').hide();
      $('[id*="et-4-3"]').hide();
      $('[id*="et-3-3"]').show();
      $('[id*="et-2-3"]').show();
      $('[id*="et-1-3"]').show();
    }

    if ($('[class*="examtimes4"]').val() == 7) {
      $('[id*="et-6-4"]').hide();
      $('[id*="et-5-4"]').hide();
      $('[id*="et-4-4"]').hide();
      $('[id*="et-3-4"]').show();
      $('[id*="et-2-4"]').show();
      $('[id*="et-1-4"]').show();
    }

    if ($('[class*="examtimes5"]').val() == 7) {
      $('[id*="et-6-5"]').hide();
      $('[id*="et-5-5"]').hide();
      $('[id*="et-4-5"]').hide();
      $('[id*="et-3-5"]').show();
      $('[id*="et-2-5"]').show();
      $('[id*="et-1-5"]').show();
    }

    if ($('[class*="examtimes6"]').val() == 7) {
      $('[id*="et-6-6"]').hide();
      $('[id*="et-5-6"]').hide();
      $('[id*="et-4-6"]').hide();
      $('[id*="et-3-6"]').show();
      $('[id*="et-2-6"]').show();
      $('[id*="et-1-6"]').show();
    }
  }
})(jQuery);
=======
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
>>>>>>> fca29b309f4c68500be076725e1d93310cf929a5
>>>>>>> 7375f4bacef708a2cfa4c0f1d4e46f530c54a730
