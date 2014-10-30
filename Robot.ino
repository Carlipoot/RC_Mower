/*******************************************************************************
** File:    RC_Mower.ino
** Author:  Carl Hansen
** Version: 0.0.1
** Purpose: Takes inputs from an RC and converts it into signals to control
**          a mower.
*******************************************************************************/


/*******************************************************************************
** Libraries
*******************************************************************************/
#include <Servo.h>


/*******************************************************************************
** Pins
*******************************************************************************/
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


/*******************************************************************************
** Constants
*******************************************************************************/
#define MODE_PLAYSTATION  1  // Controls tracks and throttle by the joysticks
#define MODE_SKIDSTICK    2  // Controls each track by the joysticks

#define SERVO_WIDTH_MIN  1.0  // The minimum width (ms) of a PWM pulse. Also 0.7
#define SERVO_WIDTH_MAX  2.0  // The maximum width (ms) of a PWM pulse. Also 2.3

#define DEFAULT_LEFT_TRACK       1.0  // Default track position
#define DEFAULT_RIGHT_TRACK      1.0  // Default track position
#define DEFAULT_DECK_HEIGHT      1.0  // Default deck height
#define DEFAULT_ENGINE_THROTTLE  1.0  // Default throttle position

#define JOYSTICK_READ_FREQUENCY  1000  // The frequency to read each joystick
#define N_JOYSTICK_PINS             6  // The number of inputs for the joystick
#define N_JOYSTICK_SELECT_PINS      4  // The number of joysticks to select

#define N_INPUT_PINS  8  // Number of input pins
#define N_OUTPUT_PINS 8  // Number of output pins

#define UP    0  // Defines what direction is... Up
#define DOWN  1  // Down
#define LEFT  0  // Left
#define RIGHT 1  // Right



/*******************************************************************************
** Structures
*******************************************************************************/
typedef struct {
  int verticalInput[N_JOYSTICK_PINS],
      horizontalInput[N_JOYSTICK_PINS];
} Joystick;


/*******************************************************************************
** Global Variables
*******************************************************************************/
unsigned long time;  // The current time of the board

int mode;  // The current mode of the controller

double trackPositionLookup[2][11] = {
{ -5,  -4,  -3,  -2,  -1,   0,   1,   2,   3,   4,   5},   // Joystick position
{0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0}};  // Servo percentage

double deckHeightLookup[2][11] = {
{  0,   1,   2,   3,   4,   5},   // Joystick position
{0.0, 0.2, 0.4, 0.6, 0.8, 1.0}};  // Servo percentage

const int i_pins[N_INPUT_PINS] = {IN1, IN2, IN3, IN4, IN5, IN6, IN7, IN8},           // All of the input pins
          o_pins[N_OUTPUT_PINS] = {OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8};  // All of the output pins

int previousJoystickSelect = -1;


/*******************************************************************************
** Input Pins
*******************************************************************************/
#define i_controllerModeSelect  IN7  // Switch that determines controller mode
#define i_safetyOverride        IN8  // Button to override safety stop

const int i_joystick[N_JOYSTICK_PINS] = {IN1, IN2, IN3, IN4, IN5, IN6}; // Joysitck intput pins where position 0 is the direction


/*******************************************************************************
** Output Pins
*******************************************************************************/
#define o_leftTrackServo   OUT5  // Pin connected to the left track servo
#define o_rightTrackServo  OUT6  // Pin connected to the right track servo
#define o_deckServo        OUT7  // Pin that controls the deck height servo
#define o_engineServo      OUT8  // Pin that controls engine throttle servo

const int o_joystickSelect[N_JOYSTICK_SELECT_PINS] = {OUT1, OUT2, OUT3, OUT4};  // Multiplex selector pins







/*******************************************************************************
** setup()
** This will set everything to it's default position and ready to mower for
** opperation.
*******************************************************************************/
void setup() {
  // Init Serial port
  Serial.begin(115200);
  
  // Set pins to be input or output
  for (int i = 0; i < N_INPUT_PINS; i++ )
    pinMode(i_pins[i], INPUT);
  
  for (int o = 0; o < N_OUTPUT_PINS; o++ )
    pinMode(o_pins[o], OUTPUT);
    
  // Set servos to their defaul position
  
  // Set up other variable
}


/*******************************************************************************
** loop()
** The main loop will constantly read input from the RC and modify the output
** according to the values read.
*******************************************************************************/
void loop() {
  time = millis();
  
  // Calculate which joystick to multiplex to
  int x = time / JOYSTICK_READ_FREQUENCY;
  int joystickSelect = x % N_JOYSTICK_SELECT_PINS;
  
  // Reset all joystickSelect outputs if needed before reading the next ones
  if ( previousJoystickSelect != joystickSelect ) {
    digitalWrite(o_joystickSelect[previousJoystickSelect], LOW);
    previousJoystickSelect = joystickSelect;
  }
  
  // At 25Hz intervals read from each of the multiplexed inputs
  switch(joystickSelect) {
    case 0:  // Left joystick U/D
      digitalWrite(o_joystickSelect[joystickSelect], HIGH);
      break;
    case 1:  // Left joystick L/R
      digitalWrite(o_joystickSelect[joystickSelect], HIGH);
      break;
    case 2:  // Right joystick U/D
      digitalWrite(o_joystickSelect[joystickSelect], HIGH);
      break;
    case 3:  // Right joystick L/R
      digitalWrite(o_joystickSelect[joystickSelect], HIGH);
      break;
    default:
      break;
  }
  
  int joystickDirection = readJoystickDirection(),
      joystickLevel = readJoystickLevel();
  
  // Read from other inputs when needed
}




/*******************************************************************************
** servoToAngle(angle)
** Moves the servo to the specified percentage.
** Returns 0 on success.
*******************************************************************************/
int servoTo(double percentage) {
  // Use amgle to find duty cycle between 0-255 and analogWrite it
  
  return 0;
}


/*******************************************************************************
** readJoystickDirection()
** Reads the value of the joystick intput corrisponding to the direction.
** Returns 0 for Up or Left, 1 for Down or Right.
*******************************************************************************/
int readJoystickDirection() {
  // Read the input pin for direction
  return digitalRead(i_joystick[0]);
}


/*******************************************************************************
** readJoystickLevel()
** Reads the values of the joystick intput corrisponding to the desired level.
** Returns values from 0 to 4 depending on how far the joystick has been pushed.
*******************************************************************************/
int readJoystickLevel() {
  int level;
  
  // Read the input pins for the joysticks level
  for (int i = 1; i < N_JOYSTICK_PINS; i++ ) {
    if ( digitalRead(i_joystick[i]) )
      level = 1 - i;
  }
  
  return level;
}





/*******************************************************************************
** Notes:
** 
** The function map() may be useful to convert a value to 255
** May need to sleep between changing outputs
*******************************************************************************/

