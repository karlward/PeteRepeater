/*
 * PeteRepeater
 * Copyright 2012 Jon Wasserman and Karl Ward
 * See the file CREDITS for details on external code referenced/incorporated
 * See the file COPYING for details on software licensing
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <MIDI.h>
#include "SuperSensor.h" // must be installed in Arduino libraries folder

byte note; 
byte velocity = 100; 
const byte CHANNEL = 1; 
const byte RECORD = 1;
const byte STOP = 2;
const byte REVERSE = 3;

SuperSensor forward(A0); // data related to forward sensor
SuperSensor reverse(A1); // data related to reverse sensor
Transport looper; // keeps track of the state of the looper 

void setup() { 
  MIDI.begin(CHANNEL); 
  MIDI.setInputChannel(MIDI_CHANNEL_OFF); 
  MIDI.turnThruOff(); 
} 

void loop() { 
  int f = forward.read(); // the actual value of the sensor
  int f_mean = forward.mean(); // the mean value of the sensor 
  delay(30);
  //int r = reverse.read();
  //delay(30);  

  // 10K resistor has analogRead value 53
  //if (f > 43 && f < 63 && r < 10) { // piece in forward
  if (f_mean > 43) { 
    // start recording on the looper 
    if (looper.record() == TRANSITION) { // was not recording, so send record command
      MIDI.sendNoteOn(RECORD, velocity, CHANNEL);
    } 
  }
  //else if (r > 43 && r < 63 && f < 10) { // piece in backward
  //  MIDI.sendNoteOn(REVERSE, velocity, CHANNEL);
  //  MIDI.sendNoteOn(RECORD, velocity, CHANNEL);    
  //} 
  else { // piece not in
    // stop the looper
    if (looper.stop() == TRANSITION) { // was not stopped, so send stop command
      MIDI.sendNoteOn(STOP, velocity, CHANNEL);
    } 
  }
}
