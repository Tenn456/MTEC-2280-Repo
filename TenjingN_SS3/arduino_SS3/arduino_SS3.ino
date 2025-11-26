const int adcPin = 1; //sensor hooked up to GPIO Pin 1
int adcRead = 0;  //variable to store our Analog-to-Digital Conversion value

//software timer variables
int lastTime = 0;
int currentTime = 0;
int timerInterval = 2;

void setup() 
{
  Serial.begin(9600);     // Start serial communication @ 9600 baud rate
  analogReadResolution(8);  //adjust adc read range to 0-255, 1-byte, 8-bit
}

void loop() 
{
  //we don't want or need to send updates to serial port so often, so use a timer:
  currentTime = millis(); //read current elapsed time
  if (currentTime - lastTime >= timerInterval)  //if we have reached our timer interval...
  {
    lastTime = currentTime; //store current time as last time so we know when timer last occured
    adcRead = analogRead(adcPin); //read sensor and assign to variable called adcRead

    Serial.write(adcRead);  //to send binary data to UART
  }
}