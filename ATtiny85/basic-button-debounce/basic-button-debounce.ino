/**
   ATtiny85 Button Switch With Debounce
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Switch an LED when button is pushed.

   IDE: 1.8.5
   Core: https://github.com/SpenceKonde/ATTinyCore

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//      (D 3) PB3  2|    |7  PB2 (D 2)
//      (D 4) PB4  3|    |6  PB1 (D 1) button
//            GND  4|    |5  PB0 (D 0) led
//                  +----+

const int led = 0;
const int button = 1;
int led_state = LOW;

// Button states and debounce
int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(button);
  if (reading != lastButtonState)
    lastDebounceTime = millis();

  if ((millis() - lastDebounceTime) > 50) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        led_state = !led_state;
      }
    }
  }

  lastButtonState = reading;

  digitalWrite(led, led_state);
}
