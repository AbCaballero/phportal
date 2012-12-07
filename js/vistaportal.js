/**
 * @author: Andrew Browning
 * @company: Aner Group
 * @client: Vista Staffing Solutions
 * @date: November 19th, 2012
 * @notes: This file contains behaviors for the vistaportal.module
 * including the U.S phone number field formatting, social security
 * number field formatting and email validation. 
*/
(function ($) {
	Drupal.behaviors.format = {
		attach: function(context, settings){
			/*
			 * This formats U.S. phone numbers
			 */	
  			$('.form-item .textfield-phone').keyup(function() {
        		var val = this.value.replace(/\D/g, '');
        		var newVal = '';
        		if (val.length > 3) {
          			newVal += val.substr(0, 3) + '-';
          			val = val.substr(3);
        		}
    			if(this.value.length > 7){
             		newVal += val.substr(0, 3) + '-';
         			val = val.substr(3);
    			}
        		newVal += val;
        		this.value = newVal;    
  			});
		}
	};
})(jQuery);

/*
 * To be added later if needed
*/

/*
* This function ensures that both email addresses match
*/
/*$('.form-item .textfield-email').change(function(){
	if($('#edit-email-conf').val() != $('edit-email').val()){
  		alert('Email addresses do not match');
  	}
});*/
  		
/*$('.ssn-field .form-text').autotab_magic().autotab_filter('numeric');*/