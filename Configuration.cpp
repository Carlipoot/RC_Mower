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
  StartWrite(CONFIG_PAGE);
  
  WriteByte(HEAD_BYTE1);
  WriteByte(HEAD_BYTE2);
  
  WriteByte(defaultTrackPosition);
  WriteByte(defaultDeckHeight);
  WriteByte(defaultEngineThrottle);
  
  FinishWrite();
}

void Configuration::clearConfiguration() {
  PageErase(CONFIG_PAGE);
}

void Configuration::test() {
  // Test config
//  config.clearConfiguration();
  delay(100);
  writeConfiguration();
  delay(20);
  StartRead(1);
  for (int i = 0; i < 20; i++ ){Serial.println(ReadByte());}
  defaultTrackPosition = 50; 
  Serial.println("+++++++++++++++++++++++++++++");
  writeConfiguration();
  delay(20);
  StartRead(1);
  for (int i = 0; i < 20; i++ ){Serial.println(ReadByte());}
}

