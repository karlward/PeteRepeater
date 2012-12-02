/*
 * Transport - Generic Audio/Sequencer Transport for Arduino
 * Copyright 2012 Karl Ward
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

#ifndef Transport_h
#define Transport_h

#include "Arduino.h"

// These are used in _transport_state
static const byte STOPPED = 1; 
static const byte RECORDING = 2; 

// These are used in _direction
static const byte FORWARD = 11
static const byte REVERSED = 12; 

// These are used in _data_state
static const byte EMPTY = 21; 
static const byte LOADED = 22; 

// These are used to determine when state transitions occur
static const byte NO_TRANSITION = 31; 
static const byte TRANSITION = 32; 

class Transport {
  public:
    Transport(); // constructor
    byte record();
    byte stop();
    byte forward();
    byte reverse();
    byte state();
    byte direction();
  private:
    byte _transport_state; // is transport recording, stopped, etc? 
    byte _direction; // which way is transport set to play (forward/backward)? 
    byte _data_state; // is there any sound/data loaded in transport now? 
};


#endif

