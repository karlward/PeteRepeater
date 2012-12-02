/*
 * SuperSensor - Sensor reading with moving average baked-right-in!
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
#include "SuperSensor.h"

// Constructor
SuperSensor::SuperSensor(int pin) {
  _pin = pin;
  _values_count = 0; // no values stored yet
}

int SuperSensor::read() {
  _value = analogRead(_pin); 
  _update(); 
  _average_values();
  return(_average_values()); 
}

void SuperSensor::_update() { 
  for (int i = (sizeof(_values) / sizeof(int)) - 1; i > 0; i--) { 
    _values[i] = _values[i-1]; // shift everything over 1 position, discarding last position
  } 
  _values[0] = _value; // set position 1 to current value
  if (_values_count < 10) { 
    _values_count++; 
  }
}

int SuperSensor::_average_values() { 
  int sum = 0;
  for (int i=0; i < _values_count; i++) { 
    sum = sum + _values[i]; 
  }
  _average = (int) (sum / _values_count); 
  return(_average); 
}

