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

#include <SoftwareSerial.h> // keep the hardware serial port free for debugging
#include <MIDI.h> // use MIDI library to send notes, instead of writing MIDI manually
#include "SuperSensor.h" // must be installed in Arduino libraries folder
#include "Transport.h" // must be installed in Arduino libraries folder

SoftwareSerial soft_serial(10,11); // RX pin is 10, TX pin is 11
// redefine MIDI serial port from hardware to a SoftwareSerial port
#define USE_SERIAL_PORT soft_serial // originally defined in MIDI.h

byte velocity = 100; // all MIDI notes we send will have this arbitraty velocity (loudness)
const byte CHANNEL = 1; 
const byte RECORD_CMD = 1; // send MIDI note 1 to send record command to looper
const byte STOP_CMD = 2; // send MIDI note 2 to send stop command to looper
const byte REVERSE_CMD = 3; // send MIDI note 3 to send reverse command to looper

SuperSensor forward(A0); // data related to forward sensor
//SuperSensor reverse(A1); // data related to reverse sensor
Transport looper; // keeps track of the state of the looper 

void setup() { 
  Serial.begin(9600); // initialize hardware serial port for debugging
  MIDI.begin(CHANNEL); // initialize soft_serial for MIDI communication
  MIDI.setInputChannel(MIDI_CHANNEL_OFF); 
  MIDI.turnThruOff(); 
} 

void loop() { 
  int f = forward.read(); // the actual value of the sensor
  int f_mean = forward.mean(); // the mean value of the sensor 
  Serial.print("forward sensor val = ");
  Serial.print(f); 
  Serial.print(", mean = "); 
  Serial.println(f_mean);  
  delay(30);
  //int r = reverse.read();
  //delay(30);  

  // 10K resistor has analogRead value 53
  //if (f > 43 && f < 63 && r < 10) { // piece in forward
  if (f_mean > 43) { 
    // start recording on the looper 
    if (looper.record() == TRANSITION) { // was not recording, so send record command
      MIDI.sendNoteOn(RECORD_CMD, velocity, CHANNEL);
      Serial.println("setting looper to record"); 
    } 
  }
  //else if (r > 43 && r < 63 && f < 10) { // piece in backward
  //  MIDI.sendNoteOn(REVERSE_CMD, velocity, CHANNEL);
  //  MIDI.sendNoteOn(RECORD_CMD, velocity, CHANNEL);    
  //} 
  else { // piece not in
    // stop the looper
    if (looper.stop() == TRANSITION) { // was not stopped, so send stop command
      MIDI.sendNoteOn(STOP_CMD, velocity, CHANNEL);
      Serial.println("setting looper to stop");
    } 
  }
}
