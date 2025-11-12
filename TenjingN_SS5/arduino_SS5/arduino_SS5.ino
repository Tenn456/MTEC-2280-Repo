const int LED = 4; // LED 1 pin
byte val; // store byte received from serial port

void setup() 
{
  pinMode(LED, OUTPUT); // set pin as output
  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() 
{
  if (Serial.available()) // If data is available to read
  { 
    val = Serial.read(); // read it and store it in val
  }

  digitalWrite(LED, val);
}