/*
P5.JS SERIAL SEND LED PWM

An example p5.js sketch that uses the p5.serialport library to send data across serial port one byte at a time.
Sends 8-bit PWM values to dim LED on microcontroller. Mouse X position changes sent value.

This code is designed to work with the "Arduino_Serial_LED_PWM" example sketch.

NOTES:
- You must run and establish a serial connection with p5.serialcontrol app to use this code:
  https://github.com/p5-serial/p5.serialcontrol/releases/tag/0.1.2

- Remember to add the p5.serialport library to your index.html file. Add this line below <script src="libraries/p5.min.js"></script>:

    <script language="javascript" type="text/javascript" src="https://cdn.jsdelivr.net/npm/p5.serialserver@0.0.28/lib/p5.serialport.js"></script>

- Make sure the baud rate in options matches the baud rate in your Arduino code.
- Remember to change the portName variable to match your own serial port.
*/

let serial; // variable for instance of the serialport library
let portName = 'COM4'; // fill in your serial port name
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code
let outByte = 0;  // 8-bit data to send to microcontroller
let state = "OFF";
let r = 255;
let g = 0;
let b = 0;

function setup() 
{
  createCanvas(800, 400);
  textAlign(CENTER, CENTER);
  textSize(36);
  background(0);

  //P5 SerialPort Setup
  serial = new p5.SerialPort();             // make a new instance of the serialport library
  serial.on('list', printList);             // set a callback function for the serialport list event
  serial.on('connected', serverConnected);  // set callback for connecting to the server
  serial.on('open', portOpen);              // set callback for the port opening
  serial.on('data', serialEvent);           // set callback for when new data received
  serial.on('error', serialError);          // set callback for errors
  serial.on('close', portClose);            // set callback for closing the port
  serial.list();                            // list the serial ports
  serial.open(portName, options);           // open a serial port

  serial.write(outByte); //send outByte across serial port
}

function draw() 
{
  background(0);

  push();
  fill(r, g, b);
  circle(width/2, height/2, 300);
  pop();

  push();
  fill(50, 50, 50);
  circle(width/2, height/2, 200);
  pop();

  // On/Off
  push();
  rectMode(CENTER);
  fill(r, g, b);
  rect(width/2, height/2, 100);
  pop();

  push();
  fill(0);
  textAlign(CENTER);
  text(state, width/2, height/2);
  pop();


  
}

function keyPressed(){
  if (key === 'o' || 'O'){
    if (state == "OFF"){
      state = "ON";
      outByte = 1;

      //color
      r = 0;
      g = 255;
      b = 0;
    }
    else {
      state = "OFF";
      outByte = 0;

      //color
      r = 255;
      g = 0;
      b = 0;
    }
  }
  serial.write(outByte); //send outByte across serial port
}

function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");
}

function portClose() //gets called when the serial port closes
{
  print("SERIAL PORT CLOSED");
}

function printList(portList) // gets called when the serial.list() function is called
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); //print list of available serial ports to console
  }
}

function serialEvent() // gets called when new serial data arrives
{
  //only sending data to microcontroller in this sketch, so not being used
}

function serialError(err) //gets called when there's an error
{
  print('ERROR: ' + err);
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERVER");
}