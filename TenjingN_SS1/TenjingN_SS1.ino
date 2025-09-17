const int ledPin = 4;
const int ledPin2 = 7;
const int ledPin3 = 8;
const int ledPin4 = 9;
int loopCount = 0;
int ms = 1000;
bool ledState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

void loop() {
  if (loopCount == 0)
  {
    digitalWrite(ledPin, 1);
    digitalWrite(ledPin2, 0);
    digitalWrite(ledPin3, 0);
    digitalWrite(ledPin4, 0);
  }
  else if (loopCount == 1)
  {
    digitalWrite(ledPin, 0);
    digitalWrite(ledPin2, 1);
    digitalWrite(ledPin3, 0);
    digitalWrite(ledPin4, 0);
  }
  else if (loopCount == 2)
  {
    digitalWrite(ledPin, 0);
    digitalWrite(ledPin2, 0);
    digitalWrite(ledPin3, 1);
    digitalWrite(ledPin4, 0);
  }
  else if (loopCount == 3)
  {
    digitalWrite(ledPin, 0);
    digitalWrite(ledPin2, 0);
    digitalWrite(ledPin3, 0);
    digitalWrite(ledPin4, 1);
  }
  else if (loopCount == 4)
  {
    digitalWrite(ledPin, 1);
    digitalWrite(ledPin2, 0);
    digitalWrite(ledPin3, 1);
    digitalWrite(ledPin4, 0);
  }
  else if (loopCount == 5)
  {
    digitalWrite(ledPin, 0);
    digitalWrite(ledPin2, 1);
    digitalWrite(ledPin3, 0);
    digitalWrite(ledPin4, 1);

    loopCount = -1;
  }

  delay(ms);

  loopCount++;
}
