let serial;                                 // variable for instance of the serialport library
let portName = 'COM4'; // fill in your serial port name
let options = { baudRate: 115200};            // change the baud rate to match your Arduino code

let button1;
let button2;
let button3;
let button4;

function setup() 
{
  createCanvas(1000, 600);
  strokeWeight(2);
  textAlign(CENTER);

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

  // Initialize Song Buttons
  button1 = new Button(100, 200, 1);
  button2 = new Button(550, 200, 2);
  button3 = new Button(100, 400, 3);
  button4 = new Button(550, 400, 4);
}

function draw() 
{
  background(0);

  push();
  fill(255);
  textSize(50);
  text("Music Player", width/2, 100);
  pop();

  button1.display();
  button2.display();
  button3.display();
  button4.display();
}

function mousePressed() //when a key is pressed...
{
  // Check if mouse is on the button
  if (mouseX > 100 && mouseX < 100 + 350 && mouseY > 200 && mouseY < 200 + 150) {
    console.log("Button clicked");

    serial.write('A');
  }
  else if (mouseX > 550 && mouseX < 550 + 350 && mouseY > 200 && mouseY < 200 + 150) {
    console.log("Button 2 clicked");

    serial.write('B');
  }
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