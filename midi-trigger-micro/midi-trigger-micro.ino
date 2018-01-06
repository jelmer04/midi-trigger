// python-build-start
// install-library "MIDI Library"
// verify
// arduino:avr:leonardo
// /dev/ttyACM0
// python-build-end

/*!
 *  Author: 	Jon Elmer
 *  Date:			27/11/2017
 *  Project:	Midi Trigger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <MIDI.h>
#include "button.cpp"
#include "LED.cpp"

MIDI_CREATE_DEFAULT_INSTANCE();

Button internal(1);
Button external(2);

LED led(3, 100, 70, 2000, 4, 25);    // Pin, Flash duration, Flash brightness, Glow period, Glow dark, Glow light

const int debounceDelay = 3;         // Time to wait before sending a message

void send_command () {
		MIDI.sendControlChange(16, 17, 1);
}

void setup () {
		
		MIDI.begin();                      // Launch MIDI

}

void loop() {

  internal.update();
  if (internal.pressed()) {
		send_command();
    led.flash();
  }

  external.update();
  if (external.pressed()) {
		send_command();
    led.flash();
  }
  
  led.update();
  delay(debounceDelay);

}



