#include <Bounce2.h>

/* 
  North Coast Modular Collective Washtenaw Wave Morpher 
  ---------------------------------------------------------
  Copyright 2018 North Coast Modular Collective
  MIT License:
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
  documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
  the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and 
  to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of 
  the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  ----------------------------------------------------------
   
  Note: Make sure "MIDI" is selected from the "Tools > USB Type" menu in the Arduino IDE
  so that it shows up as a MIDI interface. 
*/

//set debouncing object
Bounce ScrubDebounce = Bounce();
Bounce Samp1Debounce = Bounce();
Bounce RampDebounce = Bounce();
Bounce TriangleDebounce = Bounce();
Bounce SineDebounce = Bounce();
Bounce SquareDebounce = Bounce();
Bounce Samp2Debounce = Bounce();

// the MIDI channel number to send messages
const int channel = 1;

// MIDI CC Mapping of knobs/faders
const int SampleRate1 = 11; 
const int Scrub = 14; 
const int SampleRate2 = 28; 
const int Sample1 = 21;
const int Ramp = 16;
const int Triangle = 17;
const int Sine = 18;
const int Square = 19;
const int Sample2 = 27;

//MIDI CC Mapping of buttons
const int ScrubButton = 34; 
const int Sample1Button = 35;
const int RampButton = 36;
const int TriangleButton = 37;
const int SineButton = 38;
const int SquareButton = 39;
const int Sample2Button = 40;

//MIDI CC Mapping of CV inputs
const int Sample1CV = 41;
const int RampCV = 29;
const int TriangleCV = 30;
const int SineCV = 31;
const int SquareCV = 32;
const int Sample2CV = 33;


//Button and LED toggle states
int ScrubButtonState = LOW;
int LastScrubButtonState = LOW;
int ScrubButtonCounter = 0;

int Sample1ButtonState = LOW;
int LastSample1ButtonState = LOW;
int Sample1ButtonCounter = 1;

int RampButtonState = LOW;
int LastRampButtonState = LOW;
int RampButtonCounter = 1;

int TriangleButtonState = LOW;
int LastTriangleButtonState = LOW;
int TriangleButtonCounter = 1;

int SineButtonState = LOW;
int LastSineButtonState = LOW;
int SineButtonCounter = 1;

int SquareButtonState = LOW;
int LastSquareButtonState = LOW;
int SquareButtonCounter = 1;

int Samp2ButtonState = LOW;
int LastSamp2ButtonState = LOW;
int Samp2ButtonCounter = 1;


void setup() {

//BUTTONS
pinMode(15, INPUT_PULLUP); //scrub button
ScrubDebounce.attach(15);
ScrubDebounce.interval(5); //in ms
pinMode(9, INPUT_PULLUP); //Samp1 button
Samp1Debounce.attach(9);
Samp1Debounce.interval(5); //in ms
pinMode(10, INPUT_PULLUP); //Ramp button
RampDebounce.attach(10);
RampDebounce.interval(5); //in ms
pinMode(11, INPUT_PULLUP); //Triangle button
TriangleDebounce.attach(11);
TriangleDebounce.interval(5); //in ms
pinMode(12, INPUT_PULLUP); //Sine button
SineDebounce.attach(12);
SineDebounce.interval(5); //in ms
pinMode(14, INPUT_PULLUP); //Samp2 button
Samp2Debounce.attach(14);
Samp2Debounce.interval(5); //in ms
pinMode(24, INPUT_PULLUP); //Square button
SquareDebounce.attach(24);
SquareDebounce.interval(5); //in ms



//LEDs
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
}
// store previously sent values, to detect changes
//Knobs&Faders
int previousSampleRate1 = -1; 
int previousScrub = -1; 
int previousSampleRate2 = -1; 
int previousSample1 = -1; 
int previousRamp = -1;
int previousTriangle = -1;
int previousSine = -1;
int previousSquare = -1;
int previousSample2 = -1;
int previousSample1CV = -1;
int previousRampCV = -1;
int previousTriangleCV = -1;
int previousSineCV = -1;
int previousSquareCV = -1;
int previousSample2CV = -1;

elapsedMillis msec = 0;


void loop() {  //=============MAIN LOOP=================
  
//update the buttons
ScrubDebounce.update();
Samp1Debounce.update();
RampDebounce.update();
TriangleDebounce.update();
SineDebounce.update();
SquareDebounce.update();
Samp2Debounce.update();

  if (msec >= 20) {
      // only check the analog inputs 50 times per second, to prevent a flood of MIDI messages
  msec = 0;
  
//Check button state
int ScrubButtonState = ScrubDebounce.read();
if (ScrubButtonState != LastScrubButtonState)
  { 
    if (ScrubButtonState == LOW) { //Button is being pressed
      ScrubButtonCounter++;
    }
    
    } else { //Button is being released
     //nothing to do
    }
LastScrubButtonState = ScrubButtonState;
//Set LED/MIDI for button based on state
  if (ScrubButtonCounter % 2 == 0) {
    digitalWrite(8, LOW);
      //Send MIDI low here
      usbMIDI.sendControlChange(ScrubButton, 0, channel);
  } else {
   digitalWrite(8, HIGH);
      //Send MIDI high here
      usbMIDI.sendControlChange(ScrubButton, 127, channel);
  }
  

//Check button state
int Sample1ButtonState = Samp1Debounce.read();
if (Sample1ButtonState != LastSample1ButtonState)
  { 
    if (Sample1ButtonState == LOW) { //Button is being pressed
      Sample1ButtonCounter++;
    }
    
    } else { //Button is being released
     //nothing to do
    }
LastSample1ButtonState = Sample1ButtonState;
//Set LED/MIDI for button based on state
  if (Sample1ButtonCounter % 2 == 0) {
    digitalWrite(2, LOW);
    //Send MIDI low here
          usbMIDI.sendControlChange(Sample1Button, 0, channel);
  } else {
   digitalWrite(2, HIGH);
   //Send MIDI high here
         usbMIDI.sendControlChange(Sample1Button, 127, channel);
  }

//Check button state
int RampButtonState = RampDebounce.read();
if (RampButtonState != LastRampButtonState)
  { 
    if (RampButtonState == LOW) { //Button is being pressed
      RampButtonCounter++;
    }
    
    } else { //Button is being released
     //nothing to do
    }
LastRampButtonState = RampButtonState;
//Set LED/MIDI for button based on state
  if (RampButtonCounter % 2 == 0) {
    digitalWrite(3, LOW);
    //Send MIDI low here
    usbMIDI.sendControlChange(RampButton, 0, channel);
    
  } else {
   digitalWrite(3, HIGH);
   //Send MIDI high here
   usbMIDI.sendControlChange(RampButton, 127, channel);
  }  

//Check button state
int TriangleButtonState = TriangleDebounce.read();
if (TriangleButtonState != LastTriangleButtonState)
  { 
    if (TriangleButtonState == LOW) { //Button is being pressed
      TriangleButtonCounter++;
    }
    
    } else { //Button is being released
     //nothing to do
    }
LastTriangleButtonState = TriangleButtonState;
//Set LED/MIDI for button based on state
  if (TriangleButtonCounter % 2 == 0) {
    digitalWrite(4, LOW);
    //Send MIDI low here
    usbMIDI.sendControlChange(TriangleButton, 0, channel);
  } else {
   digitalWrite(4, HIGH);
   //Send MIDI high here
   usbMIDI.sendControlChange(TriangleButton, 127, channel);
  } 

//Check button state
int SineButtonState = SineDebounce.read();
if (SineButtonState != LastSineButtonState)
  { 
    if (SineButtonState == LOW) { //Button is being pressed
      SineButtonCounter++;
    }
    
    } else { //Button is being released
     //nothing to do
    }
LastSineButtonState = SineButtonState;
//Set LED/MIDI for button based on state
  if (SineButtonCounter % 2 == 0) {
    digitalWrite(5, LOW);
    //Send MIDI low here
    usbMIDI.sendControlChange(SineButton, 0, channel);
  } else {
   digitalWrite(5, HIGH);
   //Send MIDI high here
   usbMIDI.sendControlChange(SineButton, 127, channel);
  }   


//Check button state
int Sample2ButtonState = Samp2Debounce.read();
if (Sample2ButtonState != LastSamp2ButtonState)
  { 
    if (Sample2ButtonState == LOW) { //Button is being pressed
      Samp2ButtonCounter++;
    }
    
    } else { //Button is being released
     //nothing to do
    }
LastSamp2ButtonState = Sample2ButtonState;
//Set LED/MIDI for button based on state
  if (Samp2ButtonCounter % 2 == 0) {
    digitalWrite(7, LOW); //was 7
    //Send MIDI low here
    usbMIDI.sendControlChange(Sample2Button, 0, channel);
  } else {
   digitalWrite(7, HIGH); //was 7
   //Send MIDI high here
   usbMIDI.sendControlChange(Sample2Button, 127, channel);
  }   

//Check button state
int SquareButtonState = SquareDebounce.read();
if (SquareButtonState != LastSquareButtonState)
  { 
    if (SquareButtonState == LOW) { //Button is being pressed
      SquareButtonCounter++;
    }
    
    } else { //Button is being released
     //nothing to do
    }
LastSquareButtonState = SquareButtonState;
//Set LED/MIDI for button based on state
  if (SquareButtonCounter % 2 == 0) {
    digitalWrite(6, LOW); //was 6
    //Send MIDI low here
    usbMIDI.sendControlChange(SquareButton, 0, channel);
  } else {
   digitalWrite(6, HIGH); //was 6
   //Send MIDI high here
   usbMIDI.sendControlChange(SquareButton, 127, channel);
  }   

  

 





//Get current values from inputs
//---Faders/knobs--- 
    int SampleRate1Value = map(analogRead(A18), 0, 1023, 0, 127);
    int ScrubValue = map(analogRead(A8), 0, 1023, 127, 0);
    int SampleRate2Value = map(analogRead(A19), 0, 1023, 0, 127);
    int Sample1Value = map(analogRead(A2), 0, 1023, 127, 0);
    int RampValue = map(analogRead(A3), 0, 1023, 127, 0);
    int TriangleValue = map(analogRead(A4), 0, 1023, 127, 0);
    int SineValue = map(analogRead(A5), 0, 1023, 127, 0); 
    int Sample2Value = map(analogRead(A21), 0, 1023, 127, 0);  
    int SquareValue = map(analogRead(A6), 0, 1023, 127, 0); 
//---CV Inputs---
    int Samp1CVValue = map(analogRead(A9), 0, 900, 0, 127);
    int RampCVValue = map(analogRead(A12), 0, 900, 0, 127);
    int TriCVValue = map(analogRead(A13), 0, 900, 0, 127);
    int SineCVValue = map(analogRead(A14), 0, 900, 0, 127);
    int SquareCVValue = map(analogRead(A15), 0, 900, 0, 127);
    int Samp2CVValue = map(analogRead(A16), 0, 900, 0, 127);


//Transmit values over MIDI. Only transmit MIDI messages if analog input changed 

//Knobs and faders
    if ((SampleRate1Value > previousSampleRate1 +1) || (SampleRate1Value < previousSampleRate1 - 1)) {
      usbMIDI.sendControlChange(SampleRate1, SampleRate1Value, channel);
      previousSampleRate1 = SampleRate1Value;
    }

    if ((ScrubValue > previousScrub +1) || (ScrubValue < previousScrub - 1)) {
      usbMIDI.sendControlChange(Scrub, ScrubValue, channel);
      previousScrub = ScrubValue;
    }

    if ((SampleRate2Value > previousSampleRate2 +1) || (SampleRate2Value < previousSampleRate2 - 1)) {
      usbMIDI.sendControlChange(SampleRate2, SampleRate2Value, channel);
      previousSampleRate2 = SampleRate2Value;
    }

    if ((Sample1Value > previousSample1 +1) || (Sample1Value < previousSample1 - 1)) {
      usbMIDI.sendControlChange(Sample1, Sample1Value, channel);
      previousSample1 = Sample1Value;
    }

    if ((RampValue > previousRamp +1) || (RampValue < previousRamp - 1)) {
      usbMIDI.sendControlChange(Ramp, RampValue, channel);
      previousRamp = RampValue;
    }
    
    if ((TriangleValue > previousTriangle +1) || (TriangleValue < previousTriangle - 1)) {
      usbMIDI.sendControlChange(Triangle, TriangleValue, channel);
      previousTriangle = TriangleValue;
    }

    if ((SineValue > previousSine +1) || (SineValue < previousSine - 1)) {
      usbMIDI.sendControlChange(Sine, SineValue, channel);
      previousSine = SineValue;
    }

    if ((SquareValue > previousSquare +1) || (SquareValue < previousSquare - 1)) {
      usbMIDI.sendControlChange(Square, SquareValue, channel);
      previousSquare = SquareValue;
    }

    if ((Sample2Value > previousSample2 +1) || (Sample2Value < previousSample2 - 1)) {
      usbMIDI.sendControlChange(Sample2, Sample2Value, channel);
      previousSample2 = Sample2Value;
    }

//CV Inputs
      usbMIDI.sendControlChange(Sample1CV, Samp1CVValue, channel);
      usbMIDI.sendControlChange(RampCV, RampCVValue, channel);
      usbMIDI.sendControlChange(TriangleCV, TriCVValue, channel);
      usbMIDI.sendControlChange(SineCV, SineCVValue, channel);
      usbMIDI.sendControlChange(SquareCV, SquareCVValue, channel);
      usbMIDI.sendControlChange(Sample2CV, Samp2CVValue, channel);

  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

