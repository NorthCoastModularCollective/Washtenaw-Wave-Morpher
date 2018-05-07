#include <Bounce2.h>

Bounce NotReserved01 = Bounce();



void setup() {
  // put your setup code here, to run once:
pinMode(13, INPUT_PULLUP); //Square button
NotReserved01.attach(13);
NotReserved01.interval(5); //in ms

pinMode(14, INPUT_PULLUP);

//LEDs
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);

digitalWrite(2, HIGH);
}

void loop() {
  NotReserved01.update();
//Check button state
int SquareButtonState = NotReserved01.read();
    if (SquareButtonState == LOW) { //Button is being pressed
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    } else { //Button is being released
      digitalWrite(6, HIGH);
      digitalWrite(8, HIGH);
     //nothing to do
    }

//Check button state
int Samp2ButtonState = digitalRead(14);
    if (Samp2ButtonState == LOW) { //Button is being pressed
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    } else { //Button is being released
      digitalWrite(6, HIGH);
      digitalWrite(8, HIGH);
     //nothing to do
    }

}
