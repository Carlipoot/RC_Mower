/***************************************************************************************************
** File:    Robot.ino
** Author:  Carl Hansen
** Version: 0.0.1
** Purpose: Takes inputs from an RC and converts it into signals to control a robot.
***************************************************************************************************/


/***************************************************************************************************
** Libraries
***************************************************************************************************/
#include <Servo.h>


/***************************************************************************************************
** Constants
***************************************************************************************************/
#define DEBUG_MODE  1  // Used to print debug information

#define MODE_PLAYSTATION  1  // Controls tracks and throttle by different joysticks
#define MODE_SKIDSTICK    2  // Controls each track by the joysticks

#define SERVO_PULSE_WIDTH_MIN  1.0  // The minimum width (ms) of a PWM pulse. Also 0.7
#define SERVO_PULSE_WIDTH_MAX  2.0  // The maximum width (ms) of a PWM pulse. Also 2.3

#define DEFAULT_TRACK_POSITION   1.0  // Default track position
#define DEFAULT_DECK_HEIGHT      1.0  // Default deck height
#define DEFAULT_ENGINE_THROTTLE  1.0  // Default throttle position

#define JOYSTICK_READ_FREQUENCY  1000  // The frequency to read each joystick

#define DIRECTION_UL    1  // Joystick is in the up or left position
#define DIRECTION_DR   -1  // Joystick is in the down or right position
#define DIRECTION_NONE  0  // Joystick is in centre



/***************************************************************************************************
** Pin Definitions
***************************************************************************************************/
#define IN1  13
#define IN2  12
#define IN3  11
#define IN4  10
#define IN5  50
#define IN6  51
#define IN7  52
#define IN8  53

#define OUT1 12
#define OUT2 11
#define OUT3 8
#define OUT4 7
#define OUT5 6
#define OUT6 3
#define OUT7 2
#define OUT8 5


/***************************************************************************************************
** Input Pins
***************************************************************************************************/
#define I_CONTROLLER_MODE_SELECT  IN7  // Switch that determines controller mode
#define I_SAFETY_OVERRIDE         IN8  // Button to override safety stop

#define I_LEFT_JOYSTICK_HORIZONTAL   A0  // Horizontal axis of the left joystick
#define I_LEFT_JOYSTICK_VERTICAL     A1  // Vertical axis of the left joystick
#define I_RIGHT_JOYSTICK_HORIZONTAL  A2  // Horizontal axis of the right joystick
#define I_RIGHT_JOYSTICK_VERTICAL    A3  // Vertical axis of the right joystick


/***************************************************************************************************
** Output Pins
***************************************************************************************************/
#define O_LEFT_TRACK_SERVO   OUT1  // Pin connected to the left track servo
#define O_RIGHT_TRACK_SERVO  OUT2  // Pin connected to the right track servo
#define O_DECK_SERVO         OUT7  // Pin that controls the deck height servo
#define O_ENGINE_SERVO       OUT8  // Pin that controls engine throttle servo


/***************************************************************************************************
** Macros
***************************************************************************************************/
#define SERVO_PERCENTAGE_TO_PULSE(x)  (((SERVO_PULSE_WIDTH_MAX - SERVO_PULSE_WIDTH_MIN) * x) + SERVO_PULSE_WIDTH_MIN)


/***************************************************************************************************
** Structures
***************************************************************************************************/
typedef struct {
    int inputPin;
    int currentLevel;
    int previousLevel;
    int direction;
} Joystick;


/***************************************************************************************************
** Global Variables
***************************************************************************************************/
unsigned long time;  // The current time of the board

int mode;  // The current mode of the controller

double trackSpeedLookup[2][6] = {
{0,   1,   2,   3,   4,   5},     // Joystick level
{0.0, 0.1, 0.2, 0.4, 0.7, 1.0}};  // Servo percentage

double deckHeightLookup[2][6] = {
{  0,   1,   2,   3,   4,   5},   // Joystick level
{0.0, 0.2, 0.4, 0.6, 0.8, 1.0}};  // Servo percentage

Joystick leftHoriJS;  // The joysticks
Joystick leftVertJS;
Joystick rightHoriJS;
Joystick rightVertJS;






/***************************************************************************************************
** setup()
** This will set everything to it's default position and ready to mower for operation.
***************************************************************************************************/
void setup() {
  // Initialise Serial port
  if ( DEBUG_MODE ) Serial.begin(115200);
  if ( DEBUG_MODE ) Serial.println("Beginning setup");
  
  // Set pins to be input or output
  if ( DEBUG_MODE ) Serial.println("Assigning pin modes");
  
  // Set up other variables
  if ( DEBUG_MODE ) Serial.println("Initialising variables");
  leftHoriJS.inputPin = I_LEFT_JOYSTICK_HORIZONTAL;
  leftVertJS.inputPin = I_LEFT_JOYSTICK_VERTICAL;
  rightHoriJS.inputPin = I_RIGHT_JOYSTICK_HORIZONTAL;
  rightVertJS.inputPin = I_RIGHT_JOYSTICK_VERTICAL;
  leftHoriJS.currentLevel = leftVertJS.currentLevel = rightHoriJS.currentLevel = rightVertJS.currentLevel = 0;
  leftHoriJS.previousLevel = leftVertJS.previousLevel = rightHoriJS.previousLevel = rightVertJS.previousLevel = 0;
  leftHoriJS.direction = leftVertJS.direction = rightHoriJS.direction = rightVertJS.direction = DIRECTION_NONE;
  
  // Set servos to their default position
  if ( DEBUG_MODE ) Serial.println("Defaulting servos");
  
  // Let things settle by waiting
  delay(2000);
  
  if ( DEBUG_MODE ) Serial.println("Starting main loop");
}


/***************************************************************************************************
** loop()
** The main loop will constantly reads input from the RC and modify the output according to
** the values read.
***************************************************************************************************/
void loop() {
  time = millis();
  
  // Calculate which joystick to read
  long x = time / JOYSTICK_READ_FREQUENCY;
  long joystickSelect = x % 4;
  
  // At 25Hz intervals read from each of the multiplexed inputs
  switch(joystickSelect) {
    case 0:  // Left joystick L/R

      break;
    case 1:  // Left joystick U/D

      break;
    case 2:  // Right joystick L/R

      break;
    case 3:  // Right joystick U/D

      break;
    default:
      break;
  }

  // Read from other inputs when needed
}






/***************************************************************************************************
** readJoystickDirection()
** Reads the value of the joystick input corresponding to the direction.
** Returns 0 for Up or Left, 1 for Down or Right.
***************************************************************************************************/
int readJoystickDirection() {
  // Read the input pin for direction
}


/***************************************************************************************************
** readJoystickLevel()
** Reads the values of the joystick input corresponding to the desired level.
** Returns values from 0 to 4 depending on how far the joystick has been pushed.
***************************************************************************************************/
int readJoystickLevel() {

}







/***************************************************************************************************
** Notes
** 
** The function map() may be useful to convert a value to 255
** May need to sleep between changing outputs
** 
** 
** 
** 
***************************************************************************************************/