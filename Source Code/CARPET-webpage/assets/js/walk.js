//for mouse click
$("#btn_forward").mousedown(function(){
  $("#result").html ("forward");
  sendDirection("forward");
});
$("#btn_right").mousedown(function(){
  $("#result").html ("right");
  sendDirection("right");
});
$("#btn_left").mousedown(function(){
  $("#result").html ("left");
  sendDirection("left");
});
 $("#btn_back").mousedown(function(){
  $("#result").html ("backward");
  sendDirection("backward");
});

 $("#btn_forward, #btn_right, #btn_left, #btn_back").mouseup(function(){
	$("#result").html ("stop");
	sendDirection("stop");
});
 

// for keybort press(arror keys)
document.addEventListener("keydown", function(event){
 	if(event.which === 38){
 		$("#result").html ("forward");
		sendDirection("forward");
 	}
 	else if(event.which === 39){
 		$("#result").html ("right");
		sendDirection("right");
 	}
 	else if(event.which === 37){
 		$("#result").html ("left");
		sendDirection("left");
 	}
 	else if(event.which === 40){
 		$("#result").html ("backward");
		sendDirection("backward");
 	}
 });


document.addEventListener("keyup", function(event){
	$("#result").html ("stop");
	sendDirection("stop");
});



// for touch screen
$("#btn_forward").bind('touchstart', function(){
    $("#result").html ("forward");
    sendDirection("forward");
});
$("#btn_right").bind('touchstart', function(){
    $("#result").html ("right");
    sendDirection("right");
});
$("#btn_left").bind('touchstart', function(){
    $("#result").html ("left");
    sendDirection("left");
});
$("#btn_back").bind('touchstart', function(){
    $("#result").html ("backward");
    sendDirection("backward");
});

$("#btn_forward, #btn_right, #btn_left, #btn_back").bind('touchend', function(){
    $("#result").html ("stop");
    sendDirection("stop");
});


////////////////////////////

function sendDirection(direction) {
	$.getJSON('/set_car_direction?direction=' + direction, function(data) {		
	});
}

function loadA(){
	setTimeout(function(){
		console.log('A');
		document.getElementById('imgA').style.display = "initial";
		var b = document.getElementById('imgB');
		b.style.display="none";
		b.src='/camera?'+Date.now();
	}, 300);
}

function loadB(){
	setTimeout(function(){
		console.log('B');
		document.getElementById('imgB').style.display = "initial";
		var a = document.getElementById('imgA');
		a.style.display= "none";
		a.src='/camera?'+Date.now();
	}, 300);
}
//$(document).ready(function(){
//
//		streaming();
//
//});

//function streaming() {
//	console.log(this);
//	
//	$.get('/camera', function(data) {
//		$('#camera').html(data);
//	});
//}
//var btn_f = document.querySelector('#btn_forward');
//var txt = document.querySelector('#result');

// $("#btn_back").on('click', function()
// 	$("#result").html ("forward");
// );


// function updateBtn() {
// 	if(btn.value ==='FORWARD'){
// 		txt.textContent = 'forward';
// 	}
// 	else if(btn.value ==='RIGHT'){
// 		txt.textContent = 'right';
// 	}
// 	else if(btn.value ==='LEFT'){
// 		txt.textContent = 'left';
// 	}
// 	else if(btn.value ==='BACK'){
// 		txt.textContent = 'back';
// 	}

// }


  // if (btn.value === 'FORWARD') {
  //   btn.value = 'forward';
  //   txt.textContent = 'forward';
  // } else {
  //   btn.value = 'Start machine';
  //   txt.textContent = 'The machine is stopped.';
  // }
