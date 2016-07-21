$(document).ready(function() {
    // burger code for responsive version
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
    hiddenSection.hide(); 
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

    var directionWaypoints = [];

    function enableDirectionWaypoints(enable) {
        for(var i = 0; i < directionWaypoints.length; i++) {
            if(enable) {
                directionWaypoints[i].enable();
            }
            else {
                directionWaypoints[i].disable();
            }
        }
    }

    function handleMenuItemClick(thisElement, itemName) {
        enableDirectionWaypoints(false);
        event.preventDefault();        
        $(".menu a").removeClass('active');        
        $(thisElement).toggleClass('active');
        $('html, body').animate({
            scrollTop: $("#" + itemName).offset().top - 64}, 500, 'swing', 
            function(){
                enableDirectionWaypoints(true);});
    };

    //Using Waypoints
    $(".menu a:contains('services')").on('click', function(event) {
        handleMenuItemClick(this, 'services');
    });

    //On scroll current section get his respective menu link activated
    
    directionWaypoints.push(new Waypoint({
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
    }));
   
    
    $(".menu a:contains('features')").on('click', function(event) {
        handleMenuItemClick(this, 'features');
    });
    //On scroll current section get his respective menu link activated
    // $('.features').waypoint(function() {
    //     $(".menu a").removeClass('active');  
    //     $(".menu a:contains('features')").addClass('active');       
    // }, { offset: 100 });
    directionWaypoints.push(new Waypoint({
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
    })); 
    

    $(".menu a:contains('downloads')").on('click', function(event) {
        handleMenuItemClick(this, 'downloads');
    });

    // On scroll current section get his respective menu link activated

    directionWaypoints.push(new Waypoint({
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
    })); 

    

    $(".menu a:contains('contributing')").on('click', function(event) {
        handleMenuItemClick(this, 'contribution');
    });

    directionWaypoints.push(new Waypoint({
      element: $('#contribution'),
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
    }));     

    //go-to-dl
    $(".features a:contains('app')").on('click', function(event) {
        console.log('downloads is cliqued');
        event.preventDefault();
        $('html, body').animate({
            scrollTop: $("#downloads").offset()
                .top - 64
        }, 500);
    });
    // Logo home
    $(".logo-home").on('click', function(event) {
        enableDirectionWaypoints(false);
        console.log('home is cliqued');        
        event.preventDefault();
        $(".menu a").removeClass('active');
        $('html, body').animate({
            scrollTop: $("body").offset().top - 72}, 500, 'swing', 
            function(){
                enableDirectionWaypoints(true);});
    });

    $(".go-up").on('click', function(event) {
        enableDirectionWaypoints(false);
        console.log('home is cliqued');
        event.preventDefault();
        $('.menu a').removeClass('active');
        $('html, body').animate({
            scrollTop: $("body").offset().top - 72}, 500, 'swing', 
            function(){
                enableDirectionWaypoints(true);});
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