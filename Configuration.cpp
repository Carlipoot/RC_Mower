/***************************************************************************************************
** File:    Configuration.h
** Author:  Carl Hansen
** Version: 0.0.1
** Purpose: Used to set configurations of the robot.
***************************************************************************************************/

#include "Configuration.h"

Configuration::Configuration() {
  defaultTrackPosition = DEFAULT_TRACK_POSITION;
  defaultDeckHeight = DEFAULT_DECK_HEIGHT;
  defaultEngineThrottle = DEFAULT_ENGINE_THROTTLE;
}

/* void Configuration::init() {
  // Initialise memory
  DataFlash.Init();
  
  // See if configuration already exists. Clear and write defaults if none found
  DataFlash.StartRead(CONFIG_PAGE);
  byte head1 = DataFlash.ReadByte();
  byte head2 = DataFlash.ReadByte();

  if ( (head1 == HEAD_BYTE1) && (head2 == HEAD_BYTE2) ) {
    readConfiguration();
  } else {
    // reset();
    // writeConfiguration();
  }
} */

int Configuration::readConfiguration() {
  // Read configuration
  StartRead(CONFIG_PAGE);
  byte head1 = ReadByte();
  byte head2 = ReadByte();
  
  // Start reading if there
  if ( (head1 == HEAD_BYTE1) && (head2 == HEAD_BYTE2) ) {
    defaultTrackPosition = ReadByte();
    defaultDeckHeight = ReadByte();
    defaultEngineThrottle = ReadByte();
    
    // TODO - Checksum here
    return ((int) 1);
  }
  return ((int) 0);
}

void Configuration::writeConfiguration() {
  // Begin writing configuration
  StartWrite(1);
  
  WriteByte(HEAD_BYTE1);
  WriteByte(HEAD_BYTE2);
  
  WriteByte(defaultTrackPosition);
  WriteByte(defaultDeckHeight);
  WriteByte(defaultEngineThrottle);
}

/* void Configuration::reset() {
  DataFlash.EraseAll(&delay);
} */
