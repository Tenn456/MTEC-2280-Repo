let serial; // variable for instance of the serialport library
let portName = 'COM4'; // fill in your serial port name
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code

let rxFlag = false; // flag to indicate when new data has been received
let firstContact = false; // flag to indicate when the first contact has been made with the serial port
let sensors = [0, 0]; // declare array to hold incoming sensor data, and initialize with zeros
let pot1 = 0; // variable to hold potentiometer value
let button1 = 0; // variable to hold button value

let bullets = [];


function setup() 
{
  //P5 Sketch Setup
  createCanvas(500, 500);
  textAlign(CENTER, CENTER);
  textSize(24);
  strokeWeight(4);
  stroke(127);

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
}

function draw() 
{
  background(0);
  stroke(127);

  if (!firstContact)  //if we have not yet received any data...
  {
  // display Starting page
    background(0);
    fill(255);
    noStroke();
    text("Click Circle to Begin", width/2, height/4);
    circle(width/2, height/2, 140);
    fill(0);
    text("START", width/2, height/2);
  }
  else  //if we have established contact with the serial port, start game
  {
    // If button is pressed...
    if (button1 > 0) {
      // Create a bullet
      bullets.push(new Bullet(pot1 + 25, 400, 5));
    }

    // If bullets exist...
    if (bullets) {
      // Spawn bullets
      for (let i = 0; i < bullets.length; i++) {
        bullets[i].display();
        bullets[i].update();

        // If bullet goes offscreen
        if (bullets[i].off) {
          // "Delete" bullet
          bullets.splice[i, 1];
        }
      }
    }

    // Player
    push();
    fill(255, 0, 0);
    rect(pot1, 400, 50, 50);
    pop();
  }
}

function mousePressed() //if mouse is pressed...
{
  if (dist(mouseX, mouseY, width/2, height/2) < 70) // if mouse postion is within the radius of the circle button...
  {
    rxFlag = !rxFlag; // toggle the rxFlag

    if (rxFlag) //if rxFlag is true, we want to receive data, so...
    {
      serial.write('A'); // send 'A' to the serial port to indicate that we want to receive data
    }
    else  //if rxFlag is false, we want to pause receiving data, so...
    {
      serial.write('B'); // send 'B' to the serial port to indicate that we want to pause receiving data
    }
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
  if (!firstContact)  //if we have not yet received any data, this is our first contact with the serial port, so...
  {
    print("FIRST CONTACT"); //print "FIRST CONTACT" to the console
    firstContact = true;  //set firstContact flag to true
  }
  
  if(rxFlag)  //if rxFlag is true, we want to receive data, so...
  {
    let inString = serial.readStringUntil('\n'); // read the incoming string until you get a newline character
    if (inString.length > 0) 
    {
      print("Rx String: " + inString); // print the incoming string to the console
      sensors = split(inString, ','); // split the string into an array of sensor values
    
      if(sensors.length >= 2) // check if we have all 3 sensor values before trying to access them
      {
        print(sensors); // print the array of sensor values to the console

        button1 = Number(sensors[0]); // convert the first sensor value to an integer
        button1 = map(button1, 0, 1, 0, 255); // map the button value from boolean true/false to 0-255
        
        pot1 = Number(sensors[1]); // convert the second sensor value to an integer
        pot1 = map(pot1, 0, 1023, 450, 0);
        pot1 = floor(pot1); // round the potentiometer value to an integer
        
        print("Button 1: " + button1 + " Pot 1: " + pot1);  //print mapped sensor values to the console

        //now that we're done processing the incoming data, we can "call out" to our microcontroller, which respond with latest sensor data.
        serial.write('A');  // send 'A' to the serial port to indicate that we want the latest sensor data
      }
    }
  }
  else
  {
    let inString = serial.readStringUntil('\n'); // read the incoming string until you get a newline character
    print(inString); // print the incoming string to the console
  }
}

function serialError(err) //gets called when there's an error
{
  print('SERIAL ERROR: ' + err);
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERIAL SERVER");
}

class Bullet {
  constructor(x, y, speed) {
    this.x = x;
    this.y = y;
    this.speed = speed;
    this.off = false;
  }

  display() {
    push();
    fill(255);
    noStroke();
    circle(this.x, this.y, 10);
    pop();
  }

  update() {
    this.y -= this.speed; // move upwards

    // If offscreen...
    if (this.y < -10) {
      this.off = true;
    }
  }
}