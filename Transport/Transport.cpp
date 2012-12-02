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

#include "Arduino.h"
#include "Transport.h"

// Constructor
Transport::Transport() {
  _transport_state = STOPPED;
  _direction = FORWARD; 
  _data_state = EMPTY;
}

byte Transport::record() {
  byte old = _transport_state; 
  _transport_state = RECORDING; 
  _data_state = LOADED; 
  if (old == _transport_state) { 
    return(NO_TRANSITION); 
  } 
  else { return(TRANSITION); }
}


byte Transport::stop() {
  byte old = _transport_state; 
  _transport_state = STOPPED; 
  if (old == _transport_state) { 
    return(NO_TRANSITION); 
  } 
  else { return(TRANSITION); }
}

byte Transport::forward() {
  byte old = _direction; 
  _direction = FORWARD; 
  if (old == _direction) { 
    return(NO_TRANSITION); 
  } 
  else { return(TRANSITION); }
}

byte Transport::reverse() {
  byte old = _direction; 
  _direction = REVERSE; 
  if (old == _direction) { 
    return(NO_TRANSITION); 
  } 
  else { return(TRANSITION); }
}

byte Transport::state() {
  return(_transport_state); 
}

byte Transport::direction() {
  return(_direction); 
}
