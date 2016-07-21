$(document).ready(function() {


	function createTheCopyTrick(textToCopy) {		

		// Styling textare to be invisible
		$('.copy-trick').css({'background-color':'transparent','width':'0px','height':'0px','color':'transparent','border-color':'transparent'});

		//Create a textarea and set its contents to the text you want copied to the clipboard.	
		var thisTextInsideCodeTag = $(textToCopy).text().replace('$ ', ''); 
		console.log('thisTextInsideCodeTag');

		// Append the textarea to the dom.
		$('body').append('<textarea class="copy-trick"></textarea>');

		// Select the text in the textarea.
		$('.copy-trick').html(thisTextInsideCodeTag).select();	

		try {
		    // call the commande below
			document.execCommand("copy");
			console.log('copied !');
		}
		catch(err) {
		    console.log('Le code n as pu être copié');
		}
		

		// Remove textarea from the DOM	
		$('.copy-trick').remove();
		console.log('textarea removed');
	};

	$('#kaos .copy-button').on('click', function(e){
		e.preventDefault();
		createTheCopyTrick('#kaos code');
	});

	$('#archlinux .copy-button').on('click', function(e){
		e.preventDefault();
		createTheCopyTrick('#archlinux code');
	});

	$('#other-distributions > div > div:nth-child(1) > a').on('click', function(e){
		e.preventDefault();
		createTheCopyTrick('#other-distributions > div > div:nth-child(1) > code');
	});

	$('#other-distributions > div > div:nth-child(2) > a').on('click', function(e){
		e.preventDefault();
		createTheCopyTrick('#other-distributions > div > div:nth-child(2) > code');
	});

	$('#other-distributions > div > div:nth-child(3) > a').on('click', function(e){
		e.preventDefault();
		createTheCopyTrick('#other-distributions > div > div:nth-child(3) > code');
	});

	


});