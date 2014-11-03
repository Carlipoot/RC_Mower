#ifndef Joystick_h
#define Joystick_h
/***************************************************************************************************
** File:    Joystick.h
** Author:  Carl Hansen
** Version: 0.0.1
** Purpose: Defines the functions of a joystick.
***************************************************************************************************/

#define DIRECTION_UL    1  // Joystick is in the up or left position
#define DIRECTION_DR   -1  // Joystick is in the down or right position
#define DIRECTION_NONE  0  // Joystick is in centre

class Joystick {
public:
  Joystick();
  
  void update();  // Reads input and updates values
  void setInput(int);
  int getDirection();  // Returns the direction
  int getLevel();  // Returns the level the joystick is at
  
private:
  int inputPin;
  int currentLevel;
  int previousLevel;
  int direction;
};

#endif
