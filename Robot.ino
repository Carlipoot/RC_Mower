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
#include <FastSerial.h>
#include <AP_Common.h>
#include <AP_Math.h>
#include <SPI.h>
#include <AP_Semaphore.h>
#include <DataFlash.h>

#include "PinDefinitions.h"
#include "Joystick.h"
#include "Configuration.h"


/***************************************************************************************************
** Constants
***************************************************************************************************/
#define DEBUG_MODE  1  // Used to print debug information

// May be useful in some sort of configuration class for writing to memory
#define MODE_PLAYSTATION  1  // Controls tracks and throttle by different joysticks
#define MODE_SKIDSTICK    2  // Controls each track by the joysticks

#define SERVO_PULSE_WIDTH_MIN  1.0  // The minimum width (ms) of a PWM pulse. Also 0.7
#define SERVO_PULSE_WIDTH_MAX  2.0  // The maximum width (ms) of a PWM pulse. Also 2.3

#define JOYSTICK_READ_FREQUENCY  1000  // The frequency to read each joystick


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
** Global Variables
***************************************************************************************************/
FastSerialPort0(Serial);

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

Configuration DataFlash;

#define HEAD_BYTE1 0xA3
#define HEAD_BYTE2 0x95


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
  leftHoriJS.setInput(I_LEFT_JOYSTICK_HORIZONTAL);
  leftVertJS.setInput(I_LEFT_JOYSTICK_VERTICAL);
  rightHoriJS.setInput(I_RIGHT_JOYSTICK_HORIZONTAL);
  rightVertJS.setInput(I_RIGHT_JOYSTICK_VERTICAL);
  
  
  
  
  DataFlash.Init();  
    delay(20);
    DataFlash.ReadManufacturerID();
    delay(10);
    Serial.print("Manufacturer:");
    Serial.print(int(DataFlash.df_manufacturer));
    Serial.print(",");
    Serial.print(DataFlash.df_device);
    Serial.println();
    
  Serial.println("Testing configuration");
  
    // We start to write some info (sequentialy) starting from page 1
    // This is similar to what we will do...
//    DataFlash.EraseAll(&delay);
    delay(10);
    DataFlash.StartWrite(1);
    Serial.println("After testing perform erase before using DataFlash for logging!");
    Serial.println("");
    Serial.println("Writing to flash... wait...");
    for (int i = 0; i < 50; i++) {     // Write 1000 packets...
        // We write packets of binary data... (without worry about nothing more)
        DataFlash.WriteByte(HEAD_BYTE1);
        DataFlash.WriteByte(HEAD_BYTE2);
        DataFlash.WriteInt(4500 + i);
        DataFlash.WriteByte(0xA2);               // 2 bytes of checksum (example)
        DataFlash.WriteByte(0x4E);
        delay(10);
    }
    DataFlash.FinishWrite();
  delay(100);

  DataFlash.StartRead(1);
  for (int i = 0; i < 10000; i++) {
  Serial.println(DataFlash.ReadInt());
}
  
  

  
    
    
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
  
  // Test for configuration

  
//  DataFlash.DataFlash.StartWrite(1);
//  DataFlash.DataFlash.WriteByte(0xF0);
//  DataFlash.DataFlash.WriteByte(0x0D);
  delay(100);
  // DataFlash.WriteByte(DataFlash.defaultTrackPosition);
  // DataFlash.WriteByte(DataFlash.defaultDeckHeight);
  // DataFlash.WriteByte(DataFlash.defaultEngineThrottle);
  delay(1000);

  // DataFlash.reset();
  // Serial.printf("Base readings... track: %d, deck: %d, engine: %d\n", (int)DataFlash.defaultTrackPosition, (int)DataFlash.defaultDeckHeight, (int)DataFlash.defaultEngineThrottle);
  // int success = DataFlash.readConfiguration();
  // Serial.println("Reading");
  // Serial.printf("Success: %d, track: %d, deck: %d, engine: %d\n", success, (int)DataFlash.defaultTrackPosition, (int)DataFlash.defaultDeckHeight, (int)DataFlash.defaultEngineThrottle);
  // Serial.println("Writing track position to 50");
  // DataFlash.defaultTrackPosition = 50;
  // DataFlash.writeConfiguration();
  // Serial.println("Reading again");
  // success = DataFlash.readConfiguration();
  // Serial.printf("Success: %d, track: %d, deck: %d, engine: %d\n", success, (int)DataFlash.defaultTrackPosition, (int)DataFlash.defaultDeckHeight, (int)DataFlash.defaultEngineThrottle);
  // Serial.println("Reading again with setting track position to 100");
  // DataFlash.defaultTrackPosition = 100;
  // success = DataFlash.readConfiguration();
  // Serial.printf("Success: %d, track: %d, deck: %d, engine: %d\n", success, (int)DataFlash.defaultTrackPosition, (int)DataFlash.defaultDeckHeight, (int)DataFlash.defaultEngineThrottle);
  
  
  while(1){};
  
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
