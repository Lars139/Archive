// grab the leap data
var webSocket = require('ws'),
    ws = new webSocket('ws://127.0.0.1:6437'),
    five = require('johnny-five'),
    //For Claw
    board = new five.Board(),
    palm_range = [113,67], // mm range of leap motion to use

    //For Servos
    leap_range_hor = [180,-180], // mm range of leap motion to use
    leap_range_ver = [100,380], // mm range of leap motion to use
    leap_range_tw = [-80,60], // mm range of leap motion to use
    frame, palm, joints, grab_margin;

//Initial value of the claw
var palm_avg = [palm, palm, palm, palm, palm];
palm =40;
grab_margin = 0;

//Once the Arduino is read
board.on('ready', function() {
	//////////////////// Setting PINx/PORTx Values  /////////////////////////
	/////   ** Servos ** /////
	//Wrist Servo @ PIN6
	servo4 = new five.Servo({
		pin: 6,
	       range: [10, 169] // dependent on servo
	});

	//Vertical Servo @ PIN9
	servo2 = new five.Servo({
		pin: 9,
	       range: [9, 169] // dependent on servo
	});

	//Horizontal Servo @ PIN10
	servo3 = new five.Servo({
		pin: 10,
	       range: [10, 169] // dependent on servo
	});

	//Claw Grip @ PIN11
	servo1 = new five.Servo({
		pin: 11,
	       range: [35, 105]  
	});

	/////   ** Sensors **   /////
	//Left Claw Finger @ PIN7
	finger_l = new five.Button(7);

	//Right Claw Finger @ PIN8
	finger_r = new five.Button(8);



	///////////////////////// Setting Initial Values /////////////////////////
	//Claw Grip @ 105 degree -- mid range
	servo1.to(105);

	//Vertical Servo @ 90 degree
	servo2.to(90);

	//Horizontal Servo @ 90 degree
	servo3.to(90);

	//Wrist Servo @ 90 degree
	servo4.to(10);

	//Claw Sensors are pre-set once Button() is called

	////////////////////////// Receiving/Data Processing // /////////////////////////
	ws.on('message', function(data, flags) {
		frame = JSON.parse(data);
		// if only one hand is present
		if (frame.hands && frame.hands.length == 1) {
			///  ** Claw **   ///
			//Making sure that both of fingers are not pressed
			//that it would move freely
			finger_l.on("release", function(){
				finger_r.on("release", function(){
					//Reading Claw data from Leap, 
					//and smoothening it w/ pseudo-exponential smoothing algorithm
					palm = 0.89*frame.hands[0].sphereRadius + (0.11)*palm; 
					//	console.log(palm);       
					servo1.to(map1(palm));
				});
			});

			//if both of the button are pressed (hold for 500ms )
			finger_l.on("hold", function(){
				finger_r.on("hold", function(){
					//Reading Claw data from Leap 
					//and smoothening it w/ pseudo-exponential smoothing algorithm
					//Taking a snap shot of the grib strength
					if(grab_margin == 0)
					grab_margin = palm;
				//Polling the palm value
				palm = 0.89*frame.hands[0].sphereRadius + (0.11)*palm; 
				//If you're trying to release the grab
				if(palm < grab_margin)
					servo1.to(map1(palm));
				//If you're trying to tighten the grab,do nothing, just hold the object
				if(palm >= grab_margin)
					servo1.to(map1(grab_margin));
				//	console.log(palm);       
				});
			});

			///   ** Joints **  ///
			//Reading Joints data from Leap,
			//Interpolate the palmPosition w/ Joint Servo Range 
			joints = frame.hands[0].palmPosition;
			servo2.to(map2(joints[1]));
			servo3.to(map3(joints[0]));

			//Interpolate the palmNormal w/ Wrist Servo Range 
			wrist = frame.hands[0].palmNormal[0]*100;
			servo4.to(map4(wrist));
			console.log("palmNorm: "+frame.hands[0].palmNormal[0]);
			console.log("Wrist: "+wrist);
		}
	});
});

////////////////////////// Input -> Servo Range Interpolation ///////////////////////////
//Claw Range Interpolation
function map1(input) {

	var pos1 =  Math.round(  // round to integer
			( servo1.range[1] -
			  ( (servo1.range[1]-servo1.range[0]) / (palm_range[1]-palm_range[0]) )
			  * (input - palm_range[0])
			) + servo1.range[0]
			);

	// bounds checking
	pos1 = pos1 > servo1.range[1] ? servo1.range[1] : pos1;
	pos1 = pos1 < servo1.range[0] ? servo1.range[0] : pos1;

	return pos1;
}

//Vertical Range Interpolation
function map2(input) {

	var pos2 =  Math.round(  // round to integer
			( servo2.range[1] -  ( (servo2.range[1]-servo2.range[0]) / (leap_range_ver[1]-leap_range_ver[0]) )  
			  * (input - leap_range_ver[0])
			) + servo2.range[0]
			);

	// bounds checking
	pos2 = pos2 > servo2.range[1] ? servo2.range[1] : pos2;
	pos2 = pos2 < servo2.range[0] ? servo2.range[0] : pos2;

	return pos2;
}

//Horizontal Range Interpolation
function map3(input) {

	var pos3 =  Math.round(  // round to integer
			( servo3.range[1] -  ( (servo3.range[1]-servo3.range[0]) / (leap_range_hor[1]-leap_range_hor[0]) )  
			  * (input - leap_range_hor[0])
			) + servo3.range[0]
			);

	// bounds checking
	pos3 = pos3 > servo3.range[1] ? servo3.range[1] : pos3;
	pos3 = pos3 < servo3.range[0] ? servo3.range[0] : pos3;

	return pos3;
}

//Twist Wrist Interpolation
function map4(input) {

	var pos4 =  Math.round(  // round to integer
			( servo4.range[1] -  ( (servo4.range[1]-servo4.range[0]) / ((leap_range_tw[1])-(leap_range_tw[0])) )  
			  * (input - leap_range_tw[0])
			) + servo4.range[0]
			);

	// bounds checking
	pos4 = pos4 > servo4.range[1] ? servo4.range[1] : pos4;
	pos4 = pos4 < servo4.range[0] ? servo4.range[0] : pos4;

	return pos4;
}

