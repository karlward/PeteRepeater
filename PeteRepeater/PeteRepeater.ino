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

// # include <MIDI.h> // use MIDI library to send notes, instead of writing MIDI manually
#include "SuperSensor.h" // must be installed in Arduino libraries folder
#include "Transport.h" // must be installed in Arduino libraries folder

byte velocity = 100; // all MIDI notes we send will have this arbitraty velocity (loudness)
const byte CHANNEL = 1; 
const byte RECORD_CMD = 1; // send MIDI note 1 to send record command to looper
const byte STOP_CMD = 2; // send MIDI note 2 to send stop command to looper
const byte REVERSE_CMD = 3; // send MIDI note 3 to send reverse command to looper
const byte CLEAR_CMD = 4; // send MIDI note 4 to send clear command to looper

SuperSensor forward(A0); // data related to forward sensor
SuperSensor reverse(A1); // data related to reverse sensor
Transport looper; // keeps track of the state of the looper 

void setup() { 
  //MIDI.begin(CHANNEL); // initialize soft_serial for MIDI communication
  begin(CHANNEL); 
  //MIDI.setInputChannel(MIDI_CHANNEL_OFF); 
  //MIDI.turnThruOff(); 
} 

void loop() { 
  int f = forward.read(); // the actual value of the sensor
  int f_mean = forward.mean(); // the mean value of the sensor 
  delay(30);
  int r = reverse.read();
  delay(30);  

  // 10K resistor has analogRead value 53
  //if (f > 43 && f < 63 && r < 10) { // piece in forward
  if (f_mean > 5) { 
    if (looper.direction() == REVERSE) { 
      looper.forward(); 
      //MIDI.sendNoteOn(REVERSE_CMD, velocity, CHANNEL);
      sendNoteOn(REVERSE_CMD, velocity, CHANNEL);
    }
    // start recording on the looper 
    if (looper.record() == TRANSITION) { // was not recording, so send r
      //MIDI.sendNoteOn((byte) RECORD_CMD, velocity, CHANNEL);
      sendNoteOn((byte) RECORD_CMD, velocity, CHANNEL);
    } 
  }
  else if (r > 5) { // piece in backward
    if (looper.direction() == FORWARD) { 
      looper.reverse(); 
      //MIDI.sendNoteOn(REVERSE_CMD, velocity, CHANNEL);
      sendNoteOn(REVERSE_CMD, velocity, CHANNEL);
    }
    if (looper.record() == TRANSITION) {
      //MIDI.sendNoteOn(RECORD_CMD, velocity, CHANNEL);    
      sendNoteOn(RECORD_CMD, velocity, CHANNEL);    
    }
  } 
  else { // piece not in
    // stop the looper
    if (looper.stop() == TRANSITION) { // was not stopped, so send stop command
      //MIDI.sendNoteOn((byte) STOP_CMD, velocity, CHANNEL);
      sendNoteOn((byte) STOP_CMD, velocity, CHANNEL);
    } 
  }
}

void begin(byte channel) { 
  Serial.begin(31250);
} 

void sendNoteOn(byte note, byte velocity, byte channel) { 

   Serial.write(0x90); // channel 1
   Serial.write(note); 
   Serial.write(0x45); // velocity
}


