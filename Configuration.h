#ifndef Configuration_h
#define Configuration_h
/***************************************************************************************************
** File:    Configuration.h
** Author:  Carl Hansen
** Version: 0.0.1
** Purpose: Used to set configurations of the robot.
***************************************************************************************************/

#include <DataFlash.h>
#include <stdint.h>

// Define a byte
#define byte uint8_t

// To determine the start of configuration packet: 0xF00D
#define HEAD_BYTE1  0xF0
#define HEAD_BYTE2  0x0D

#define CONFIG_PAGE  1  // The page to start for configuration

// Defaults as a percentage of the full servo movement
#define DEFAULT_TRACK_POSITION   0    // Default track position
#define DEFAULT_DECK_HEIGHT      100  // Default deck height
#define DEFAULT_ENGINE_THROTTLE  20   // Default throttle position

class Configuration : public DataFlash_APM2 {
public:
  Configuration();
  
  // void init();                // Initialises configuration. Clears memory if none is found
  int readConfiguration();    // Reads all values from memory
  void writeConfiguration();  // Writes all values to memory
  // void reset();               // Resets configuration with set defaults
  
  // Configurable variables
  // DataFlash_APM2 DataFlash;
  
  byte defaultTrackPosition;
  byte defaultDeckHeight;
  byte defaultEngineThrottle;
};

#endif
