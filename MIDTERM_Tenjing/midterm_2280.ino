// Pushbutton Debounce Tutorial: https://www.youtube.com/watch?v=DfKAwrBievM&t=10s

const int ledPin = 9;
const int buttonPin = 4;
const int potPin = 1;
const int numReads = 16;

int reading[numReads];
int count = 0;

bool lastButtonState;
bool onState;

unsigned long lastTimeButtonStateChanged = millis();
unsigned long debounceDuration = 50;

void setup() {
  // put your setup code here, to run once:
  analogReadResolution(11); //reduce the ADC bit depth to 11-bit
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (millis() - lastTimeButtonStateChanged >= debounceDuration)
  {
    bool buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState)
    {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (buttonState == LOW) 
      {
       onState = !onState;
       Serial.println("Pressed");
      }
    }
  }

  reading[count] = analogRead(potPin); //store current ADC read in array at index of count
  count++;

  if (count >= numReads)  //if count is greater than or equal to number of reads...
  {
    count = 0;    //...reset count
  }

  int sum = 0;    //declare empty sum variable

  for (int i = 0; i < numReads; i++)  //for every reading in array...
  {
    sum += reading[i];  //add all the readings up and store in sum
  }

  int analogValue = sum / numReads; //calculate average reading and store in analogValue
  
  //map(input value, input low, input high, output low, output high)
  int mapVal = map(analogValue, 0, 2047, 20, 255);   //use map() to scale value to 0-255 range

  // if project is ON
  if (onState)
  {
    analogWrite(ledPin, mapVal);
  }
  // if project is OFF
  else
  {
    analogWrite(ledPin, 0);
  }

  Serial.printf("ADC raw = %i \t ADC averaged = %i \t ADC mapped = %i \n", analogRead(potPin), analogValue, mapVal); 
}
