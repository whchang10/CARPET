var audio = new Audio('assets/sound/deepbark.mp3');



var mySocket = new WebSocket("ws://carpet.plumblem.com:50766", "echo-protocol");

mySocket.onmessage = function(e) {
  if(e.data === 'yes') {
	  $(".ww").fadeToggle();
	  audio.play();
	  console.log('wwef');
	  $(".ww").fadeOut();
  }
}
