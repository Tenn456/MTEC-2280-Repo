// Pushbutton Debounce Tutorial: https://www.youtube.com/watch?v=DfKAwrBievM&t=10s
// Buzzer Pitch and Song Library: https://github.com/hibit-dev/buzzer/tree/master

#include "pitches.h" 

const int ledPin = 9;
const int ledPin2 = 7;
const int buttonPin = 4;
const int buttonPin2 = 15;
const int buttonPin3 = 16;
const int potPin = 1;
const int numReads = 16;
const int buzzer = 6;

int reading[numReads];
int count = 0;
int onSong = 1;
int mapVal2;

int currentNote = 0;
unsigned long noteStartTime = 0;

bool songPlaying = false;

int rickRoll[] = {
  NOTE_A4, REST, NOTE_B4, REST, NOTE_C5, REST, NOTE_A4, REST,
  NOTE_D5, REST, NOTE_E5, REST, NOTE_D5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
  NOTE_D5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_D5, REST,
  NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
  NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
  NOTE_D5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_G5, NOTE_B4, REST,
  NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
  NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,

  NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_E5, REST,
  NOTE_G5, NOTE_F5, NOTE_E5, REST,

  NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST
};

int rickRollDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 8, 2, 2,

  8, 8, 8, 8, 2, 8, 8,
  2, 8,

  8, 8, 8, 8, 2, 8, 8,
  4, 8, 8, 8, 8,

  8, 8, 8, 8, 2, 8, 8,
  2, 8, 4, 8, 8, 8, 8, 8, 1, 4,

  8, 8, 8, 8, 2, 8, 8,
  2, 8,

  8, 8, 8, 8, 2, 8, 8,
  2, 8, 8, 8, 8,

  8, 8, 8, 8, 2, 8, 8,
  4, 8, 3, 8, 8, 8, 8, 8, 1, 4,

  2, 6, 2, 6, 4, 4, 2, 6, 2, 3,
  8, 8, 8, 8,

  2, 6, 2, 6, 2, 1
};

int mario[] = {
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST, 
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  
  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST,
  
  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST,
  
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
  REST, 
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST, 
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
  
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
  
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
  
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
  REST,
  
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST, 
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
  
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
  
  // Game over sound
  NOTE_C5, NOTE_G4, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_AS4, NOTE_GS4,
  NOTE_G4, NOTE_D4, NOTE_E4
};

int marioDurations[] = {
  8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4, 
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4,8, 8, 4,
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4,8, 8, 4,
  
  
  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,
  
  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,
  
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  
  8, 4, 8, 8, 8, 8, 8,
  1, 
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4, 
  4, 8, 4, 4,
  
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,
  
  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,
  
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,
  
  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8, 8,
  1,
  
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4, 
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,
  
  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,
  
  //game over sound
  4, 4, 4,
  8, 8, 8, 8, 8, 8,
  8, 8, 2
};

int pirates[] = {
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  
  NOTE_A4, NOTE_A4,
  //Repeat of first part
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  //End of Repeat
  
  NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4,
  
  NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4
};

int piratesDurations[] = {
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  
  4, 8,
  //Repeat of First Part
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  //End of Repeat
  
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 2,
  
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 2
};

int tetris[] = {
  NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5,
  
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, REST, 
  
  NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5,
  
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, REST, 
  
  NOTE_E5, NOTE_C5,
  NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_A4,
  NOTE_GS4, NOTE_B4, REST, 
  NOTE_E5, NOTE_C5,
  NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_E5, NOTE_A5,
  NOTE_GS5
};

int tetrisDurations[] = {
  4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8,
  4, 8, 4, 4,
  4, 4, 8, 4, 8, 8,
  
  4, 8, 4, 8, 8,
  4, 8, 4, 8, 8,
  4, 8, 8, 4, 4,
  4, 4, 4, 4,
  
  4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8,
  4, 8, 4, 4,
  4, 4, 8, 4, 8, 8,
  
  4, 8, 4, 8, 8,
  4, 8, 4, 8, 8,
  4, 8, 8, 4, 4,
  4, 4, 4, 4,
  
  2, 2,
  2, 2,
  2, 2,
  2, 4, 8, 
  2, 2,
  2, 2,
  4, 4, 2,
  2
};


bool lastButtonState;
bool lastButtonState2;
bool lastButtonState3;
bool onState = true;

int size;

unsigned long lastTimeButtonStateChanged = millis();
unsigned long lastTimeButtonStateChanged2 = millis();\
unsigned long lastTimeButtonStateChanged3 = millis();
unsigned long debounceDuration = 50;

int PotRead = 0;
int inByte = 0;

void setup() {
  // put your setup code here, to run once:
  analogReadResolution(11); //reduce the ADC bit depth to 11-bit
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH); // Light LED
  if (Serial.available()) {
    inByte = Serial.read(); // Read Serial

    // If recieving A...
    if (inByte == 'A') {
      songPlaying = false;
      onSong = 1;
      size = sizeof(rickRoll) / sizeof(int);
      initializeSong();
      Serial.println('A'); //to send human-readable data to Arduino Serial Monitor
    } // If recieving B...
    else if (inByte == 'B') {
      songPlaying = false;
      size = sizeof(mario) / sizeof(int);
      onSong = 2;
      initializeSong();
      Serial.println('B'); //to send human-readable data to Arduino Serial Monitor
    }
    else if (inByte == 'C') {
      songPlaying = false;
      onSong = 3;
      size = sizeof(pirates) / sizeof(int);
      initializeSong();
      Serial.println('C'); //to send human-readable data to Arduino Serial Monitor
    }
    else if (inByte == 'D') {
      songPlaying = false;
      onSong = 4;
      size = sizeof(tetris) / sizeof(int);
      initializeSong();
      Serial.println('B'); //to send human-readable data to Arduino Serial Monitor
    }
    else if (inByte == 'E') {
      digitalWrite(ledPin2, LOW);
      noTone(buzzer);
      songPlaying = false;
    }


    // else // if project is OFF
    // {
    //   analogWrite(ledPin, 0);
    //   digitalWrite(ledPin2, LOW);
    //   noTone(buzzer);
    //   songPlaying = false;
    // }
  }

  playSong();

  // Potentiometer stuff
  reading[count] = analogRead(potPin); //store current ADC read in array at index of count
  count++;

  if (count >= numReads)  // if count is greater than or equal to number of reads
  {
    count = 0; // reset count
  }

  int sum = 0; // declare empty sum variable

  for (int i = 0; i < numReads; i++) //for every reading in array
  {
    sum += reading[i]; //add all the readings up and store in sum
  }

  int analogValue = sum / numReads; //calculate average reading and store in analogValue
  
  int mapVal = map(analogValue, 2047, 0, 20, 255); //use map() to scale value to 0-255 range

  mapVal2 = map(analogValue, 0, 2047, 1, 3); // for buzzer

  //Serial.printf("ADC raw = %i \t ADC averaged = %i \t ADC mapped = %i \n", analogRead(potPin), analogValue, mapVal); 
}

void initializeSong() {
  currentNote = 0; // Reset song
  songPlaying = true;
  noteStartTime = millis();
  playNote(currentNote);
}

void playNote(int index) {
  if (onSong == 1)
  {
    int duration = 1000 / rickRollDurations[index];
    tone(buzzer, rickRoll[index], duration);

    // If current note doesn not play sound, LED stays off
    if (rickRoll[index] != REST){
      digitalWrite(ledPin2, HIGH);
    }
  }
  else if (onSong == 2)
  {
    int duration = 1000 / marioDurations[index];
    tone(buzzer, mario[index], duration);

    // If current note doesn not play sound, LED stays off
    if (mario[index] != REST){
      digitalWrite(ledPin2, HIGH);
    }
  }
  else if (onSong == 3)
  {
    int duration = 1000 / piratesDurations[index];
    tone(buzzer, pirates[index], duration);

    // If current note doesn not play sound, LED stays off
    if (pirates[index] != REST){
      digitalWrite(ledPin2, HIGH);
    }
  }
  else if (onSong == 4)
  {
    int duration = 1000 / tetrisDurations[index];
    tone(buzzer, tetris[index], duration);

    // If current note doesn not play sound, LED stays off
    if (tetris[index] != REST){
      digitalWrite(ledPin2, HIGH);
    }
  }

  noteStartTime = millis();
}

void playSong() {
  if (!songPlaying) return;

  unsigned long currentTime = millis();

  if (onSong == 1) 
  {
    int duration = 1000 / rickRollDurations[currentNote];
    int pause = duration * mapVal2; // The inbetween time between notes, dependent on pot

    if (currentTime - noteStartTime >= duration) {
      // Turns LED off after note finishes playing
      digitalWrite(ledPin2, LOW);
    }

    // Waits for the pause to finish before playing new note
    if (currentTime - noteStartTime >= pause) {
      currentNote++;

      if (currentNote < size) {
        // Play next note
        playNote(currentNote);
      } else {
        // If reached the end of the song
        noTone(buzzer);
        songPlaying = false; // Done
        Serial.println("Song finished!");
      }
    }
  }
  else if (onSong == 2) 
  {
    int duration = 1000 / marioDurations[currentNote];
    int pause = duration * mapVal2; // The inbetween time between notes, dependent on pot

    if (currentTime - noteStartTime >= duration) {
      // Turns LED off after note finishes playing
      digitalWrite(ledPin2, LOW);
    }

    // Waits for the pause to finish before playing new note
    if (currentTime - noteStartTime >= pause) {
      currentNote++;

      if (currentNote < size) {\
        // Play next note
        playNote(currentNote);
      } else {
        // If reached the end of the song
        noTone(buzzer);
        songPlaying = false;
        Serial.println("Song finished!");
      }
    }
  }
  else if (onSong == 3) 
  {
    int duration = 1000 / piratesDurations[currentNote];
    int pause = duration * mapVal2; // The inbetween time between notes, dependent on pot

    if (currentTime - noteStartTime >= duration) {
      // Turns LED off after note finishes playing
      digitalWrite(ledPin2, LOW);
    }

    // Waits for the pause to finish before playing new note
    if (currentTime - noteStartTime >= pause) {
      currentNote++;

      if (currentNote < size) {\
        // Play next note
        playNote(currentNote);
      } else {
        // If reached the end of the song
        noTone(buzzer);
        songPlaying = false;
        Serial.println("Song finished!");
      }
    }
  }
  else if (onSong == 4) 
  {
    int duration = 1000 / tetrisDurations[currentNote];
    int pause = duration * mapVal2; // The inbetween time between notes, dependent on pot

    if (currentTime - noteStartTime >= duration) {
      // Turns LED off after note finishes playing
      digitalWrite(ledPin2, LOW);
    }

    // Waits for the pause to finish before playing new note
    if (currentTime - noteStartTime >= pause) {
      currentNote++;

      if (currentNote < size) {\
        // Play next note
        playNote(currentNote);
      } else {
        // If reached the end of the song
        noTone(buzzer);
        songPlaying = false;
        Serial.println("Song finished!");
      }
    }
  }
}