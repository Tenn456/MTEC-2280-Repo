let serial; // declare variable for an instance of the serialport library
let portName = 'COM4';  // fill in your serial port name here
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code

let inData; // declare variable for storing incoming serial data
let circleX;
let circleY;
let velX;
let velY;
 
function setup() //setup function runs once at beginning
{
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

  //TYPICAL P5.JS SETUP
  createCanvas(400, 400); //set size of canvas
  textSize(72); // set text size
  textAlign(CENTER, CENTER);  // set text alignment

  circleX = width/2;
  circleY = height/2;

  velX = random(-1, 2);
  velY = random(-1, 2);
}

function draw() //  draw function loops forever at frame rate
{
  background(inData);  // clear frame with background color each draw loop

  let inDataReverse = inData = map(inData, 0, 255, 255, 0);

  fill(inDataReverse); // set fill color using incoming serial data
  let diameter = map(inData, 0, 255, 10, width - 10); // scale incoming data from 0 to 255 into circle diameter
  circle(circleX, circleY, diameter);  // draw circle in center of canvas with diameter based on serial data

  circleX += velX;
  circleY += velY;

  if (circleX <= 0 || circleX >= width) {
    velX *= -1;
  }
  if (circleY <= 0 || circleY >= height) {
    velY *= -1;
  }
}
 

function printList(portList) // gets called when the serial.list() function is called
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); //print list of available serial ports to console
  }
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERVER");
}
 
function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");
}
 
function serialEvent() //gets called when new data arrives
{
  inData = Number(serial.read()); //Store incoming data as a number
  //print(inData);
}
 
function serialError(err) //gets called when there's an error
{
  print('ERROR: ' + err);
}
 
function portClose() //gets called when the serial port closes
{
  print("*____SERIAL PORT CLOSED");
}