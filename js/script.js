$(document).ready(function() {
    console.log("ready!");
    $('.burger').on('click', function() {
        $(this).toggleClass('active');
        if ($(this).hasClass('active')) {
            $('.my-desktop-menu').addClass('active');
        } else {
            $('.my-desktop-menu').removeClass('active');
        }

    });
    $('.my-desktop-menu a').on('click', function(){
        $('.my-desktop-menu').removeClass('active');
        $('.burger').removeClass('active');
    });

    //Reveal gnu linux hidden menu
    var trigger = $('.trigger-hidden-menu');
    var hiddenSection = $('.hidden-section');
    hiddenSection.show(); 
    trigger.on('click', function(e) {
        e.preventDefault();
        // alert('je suis cliqué');
        hiddenSection.toggleClass('active');
        hiddenSection.slideToggle();
        if (hiddenSection.hasClass('active')) {

                $('html, body').animate({
                    scrollTop: $(".hidden-section").offset()
                        .top - 104
                }, 1000);
           
        } else {}
    });

    //Using Waypoints
    $(".menu a:contains('services')").on('click', function(event) {
        console.log('services is cliqued');
        event.preventDefault();
        // $(".menu a").removeClass('active');        
        // $(this).toggleClass('active');
        $('html, body').animate({
            scrollTop: $("#services").offset()
                .top - 64
        }, 1000);
    }); 
    //On scroll current section get his respective menu link activated    
    var directionWaypoint = new Waypoint({
      element: $('.services'),
      handler: function(direction) {
        if (direction === 'down') {
            console.log(direction + ' ' + '= bas');
            $(".menu a").removeClass('active');
        $(".menu a:contains('services')").addClass('active'); 
        } else {
            console.log(direction + ' ' + '= haut');
            $(".menu a").removeClass('active');
        }                    
      },
      offset: 66      
    });
   
    
    $(".menu a:contains('features')").on('click', function(event) {
        console.log('features is cliqued');
        event.preventDefault();
        // $(".menu a").removeClass('active');
        // $(this).toggleClass('active');
        $('html, body').animate({
            scrollTop: $("#features").offset()
                .top - 64
        }, 1000);
    });
    //On scroll current section get his respective menu link activated
    
    var directionWaypoint = new Waypoint({
      element: $('.features'),
      handler: function(direction) {
        if (direction === 'down') {
            console.log(direction + ' ' + '= bas');
            $(".menu a").removeClass('active');
            $(".menu a:contains('features')").addClass('active'); 
        } else {
            console.log(direction + ' ' + '= haut');
            $(".menu a").removeClass('active');
            $(".menu a:contains('services')").addClass('active');
        }                    
      },
      offset: 66      
    }); 
    

    $(".menu a:contains('downloads')").on('click', function(event) {
        console.log('downloads is cliqued');
        event.preventDefault();
        // $(".menu a").removeClass('active');
        // $(this).toggleClass('active');
        $('html, body').animate({
            scrollTop: $("#downloads").offset()
                .top - 64
        }, 1000);
    });
    // On scroll current section get his respective menu link activated
    // $('.downloads').waypoint(function() {
    //     $(".menu a").removeClass('active');  
    //     $(".menu a:contains('downloads')").addClass('active');       
    // }, { offset: 100 }); 
    var directionWaypoint = new Waypoint({
      element: $('.downloads'),
      handler: function(direction) {
        if (direction === 'down') {
            console.log(direction + ' ' + '= bas');
            $(".menu a").removeClass('active');
            $(".menu a:contains('downloads')").addClass('active'); 
        } else {
            console.log(direction + ' ' + '= haut');
            $(".menu a").removeClass('active');
            $(".menu a:contains('features')").addClass('active');
        }                    
      },
      offset: 66      
    }); 

    $(".menu a:contains('contributing')").on('click', function(event) {
        console.log('contributing is cliqued');
        event.preventDefault();        
        $('html, body').animate({
            scrollTop: $("#contribution").offset()
                .top - 64
        }, 1000);
        // $(".menu a").removeClass('active');
        // $(this).toggleClass('active');
    });

    var directionWaypoint = new Waypoint({
      element: $('.contribution'),
      handler: function(direction) {
        if (direction === 'down') {
            console.log(direction + ' ' + '= bas');
            $(".menu a").removeClass('active');
            $(".menu a:contains('contributing')").addClass('active'); 
        } else {
            console.log(direction + ' ' + '= haut');
            $(".menu a").removeClass('active');
            $(".menu a:contains('downloads')").addClass('active');
        }                    
      },
      offset: 66      
    }); 


    //GNU/ linux link in downloads on click > go to hidden section 

    //go-to-dl
    $(".features a:contains('app')").on('click', function(event) {
        console.log('downloads is cliqued');
        event.preventDefault();
        $('html, body').animate({
            scrollTop: $("#downloads").offset()
                .top - 64
        }, 1000);
    });
    // Logo home
    $(".logo-home").on('click', function(event) {
        console.log('home is cliqued');        
        event.preventDefault();
        $(".menu a").removeClass('active');
        $('html, body').animate({
            scrollTop: $("body").offset()
                .top - 72
        }, 1000);
    });

    $(".go-up").on('click', function(event) {
        console.log('home is cliqued');
        event.preventDefault();
        $('html, body').animate({
            scrollTop: $("body").offset()
                .top - 72
        }, 1000);
    });

    /* Dynamic top menu positioning
     *
     */

    var num = 1; //number of pixels before modifying styles

    $(window).bind('scroll', function () {
        if ($(window).scrollTop() > num) {
            $('nav').addClass('fixed');
        } else {
            $('nav').removeClass('fixed');
        }
    });


    // Show go-up button when page is at 600px
    var Mynum = 600 //number of pixels before modifying styles

    $(window).bind('scroll', function () {
        if ($(window).scrollTop() > Mynum) {
            $('.go-up').addClass('show');
        } else {
            $('.go-up').removeClass('show');
        }
    });

    //animation on the go-up button when mouseover
    $(".go-up").on('mouseover', function(event) {
        console.log('go-up is on hover');
        event.preventDefault();
        $(this).addClass('active');
        $(this).on('mouseout',function(){
             $(this).removeClass('active');
        });
    });



    // on scroll down elements fadeIn 

    // hide our element on page load
    $('.services').children().css('opacity', 0);
     
    $('.services').waypoint(function() {
        $('.services h1, .services > p').addClass('fadeInDown animated');
        $('.services ul').addClass('fadeIn animated');
    }, { offset: '50%' });  


    $('.features h1, .features li img, .features li h2, .features li p, .features li a, .compare-table').css('opacity', 0);    
     
    $('.features').waypoint(function() {
        $('.features h1').addClass('fadeInDown animated');
        $('.features li h2, .features li p, .features li a').addClass('fadeInLeft animated');
        $('.features li img, .compare-table').addClass('bounceIn animated');        
    }, { offset: '50%' }); 

    $('.downloads h1, .downloads > p, .downloads li img, .downloads li p').css('opacity', 0);    
     
    $('.downloads').waypoint(function() {
        $('.downloads h1, .downloads > p').addClass('fadeInDown animated');
        $('.downloads li p').addClass('fadeInLeft animated');
        $('.downloads li img').addClass('bounceIn animated');        
    }, { offset: '50%' }); 

    $('.contribution h1, .contribution p, .contribution a').css('opacity', 0);    
     
    $('.contribution').waypoint(function() {
        $('.contribution h1').addClass('fadeInDown animated');
        $('.contribution p, .contribution a').addClass('fadeInLeft animated');      
    }, { offset: '50%' }); 




});