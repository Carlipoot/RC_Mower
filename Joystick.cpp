/***************************************************************************************************
** File:    Joystick.cpp
** Author:  Carl Hansen
** Version: 0.0.1
** Purpose: Defines the functions of a joystick.
***************************************************************************************************/

#include "Joystick.h"

Joystick::Joystick() {
  direction = DIRECTION_NONE;
  currentLevel = 0;
  previousLevel = 0;
}

void Joystick::setInput(int pin) {
  inputPin = pin;
}

void Joystick::update() {
  // Do stuff
}

int Joystick::getDirection() {
  return (direction);
}

int Joystick::getLevel() {
  return (currentLevel);
}
