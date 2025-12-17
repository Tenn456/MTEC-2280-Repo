let serial;                                 // variable for instance of the serialport library
let portName = 'COM4'; // fill in your serial port name
let options = { baudRate: 115200};            // change the baud rate to match your Arduino code

let button1;
let button2;
let button3;
let button4;

let marioImg;
let rickImg;
let pirateImg;
let tetrisImg;
let brunoImg;

let rickGif;
let marioGif;
let pirateGif;
let tetrisGif;


let firstRoll = true;
let playingRoll = false;
let playingMario = false;
let playingPirate = false;
let playingTetris = false;

let inData;

let particles = [];

function setup() 
{
  createCanvas(1000, 600);
  strokeWeight(2);

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

  for (let i = 0; i < 50; i++) {
    particles.push(new Particle());
  }

  // Initialize Song Buttons
  button1 = new Button(25, 200, 1);
  button2 = new Button(525, 200, 2);
  button3 = new Button(25, 400, 3);
  button4 = new Button(525, 400, 4);

  marioImg = loadImage('mario.png');
  rickImg = loadImage('rick.jpg');
  pirateImg = loadImage('pirate.jpg');
  tetrisImg = loadImage('tetris.jpg');
  rickGif = loadImage('rickroll.gif');
  brunoImg = loadImage('bruno.jpg');
  marioGif = loadImage('marioLevel.gif');
  pirateGif = loadImage('pirateZoom.gif');
  tetrisGif = loadImage('tetrisGame.gif');
}

function draw() 
{
  background(0);

  if (playingRoll) {
    push();
    imageMode(CENTER);
    image(rickGif, width/2, height/2, 950, 700);
    pop();
  }
  else if (playingMario) {
    push();
    imageMode(CENTER);
    image(marioGif, width/2, height/2, 950, 700);
    pop();
  }
  else if (playingPirate) {
    push();
    imageMode(CENTER);
    image(pirateGif, width/2, height/2, 950, 700);
    pop();
  }
  else if (playingTetris) {
    push();
    imageMode(CENTER);
    image(tetrisGif, width/2, height/2, 950, 700);
    pop();
  }

  for (let p of particles) {
    p.update();
    p.display();
  }

  push();
  textAlign(CENTER);
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
  let newColor;

  // Check if mouse is on the button
  if (mouseX > 25 && mouseX < 25 + 450 && mouseY > 200 && mouseY < 200 + 150) {
    console.log("Button clicked");
    newColor = color(255, 171, 217, 100);

    if (firstRoll) {
      playingRoll = true;
      firstRoll = false;
      playingMario = false;
      playingPirate = false;
      playingTetris = false;
    }

    if (!playingRoll) {
      playingRoll = true;
      playingMario = false;
      playingPirate = false;
      playingTetris = false;
    }


    serial.write('A');
  }
  else if (mouseX > 525 && mouseX < 525 + 450 && mouseY > 200 && mouseY < 200 + 150) {
    console.log("Button 2 clicked");
    newColor = color(255, 0, 0, 100);

    if (!playingMario) {
      playingMario = true;
      playingRoll = false;
      playingPirate = false;
      playingTetris = false;
    }

    serial.write('B');
  }
  else if (mouseX > 25 && mouseX < 25 + 450 && mouseY > 400 && mouseY < 400 + 150) {
    console.log("Button 3 clicked");
    newColor = color(0, 51, 255, 100);

    if (!playingPirate) {
      playingPirate = true;
      playingRoll = false;
      playingMario = false;
      playingTetris = false;
    }

    serial.write('C');
  }
  else if (mouseX > 525 && mouseX < 525 + 450 && mouseY > 400 && mouseY < 400 + 150) {
    console.log("Button 4 clicked");
    newColor = color(255, 194, 89, 100);

    if (!playingTetris) {
      playingTetris = true;
      playingRoll = false;
      playingMario = false;
      playingPirate = false;
    }

    serial.write('D');
  }

  // Tell each particle to lerp toward color
  for (let p of particles) {
    p.setTargetColor(newColor);
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
  //print(inData);

  inData = Number(serial.read());

}

function serialError(err) //gets called when there's an error
{
  print('ERROR: ' + err);
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERVER");
}