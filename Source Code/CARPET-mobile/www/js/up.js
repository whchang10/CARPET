var audio = new Audio('res/sound/deepbark.mp3');


// $("#w").hover(function(){
// 	$(".ww").fadeToggle();
// 	audio.play()
// });

var mySocket = new WebSocket("ws://carpet.plumblem.com:50766","echo-protocol");

mySocket.onmessage=function(e){
	if(e.data === 'yes'){
		$(".ww").fadeToggle();
		audio.play();
		console.log('wwef');
		$(".ww").fadeOut();
	}
}
