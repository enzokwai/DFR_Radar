/**
  * @file       DFR_Radar.h
  * @brief      An Arduino library that makes it easy to configure and use the DFRobot 24GHz millimeter-wave Human Presence Detection sensor (SEN0395)
  * @copyright  Copyright (c) 2010 DFRobot Co. Ltd. (http://www.dfrobot.com)
  *             Copyright (c) 2023 Matthew Clark (https://github.com/MaffooClock)
  * @license    The MIT License (MIT)
  * @authors    huyujie (yujie.hu@dfrobot.com)
  *             Matthew Clark
  * @version    v1.0
  * @date       2023-11-07
  * @url        https://github.com/MaffooClock/DFRobot_Radar
  */

#include <DFR_Radar.h>


DFR_Radar::DFR_Radar( Stream *s )
{
  sensorUART = s;
}

size_t DFR_Radar::readBytes( char *buffer, size_t length )
{
  size_t offset = 0, remaining = length;
  unsigned long startTime = millis();

  while( remaining )
  {
    if( sensorUART -> available() )
    {
      buffer[offset] = sensorUART->read();
      offset++;
      remaining--;
    }

    if( millis() - startTime > readBytesTimeout )
      break;
  }

  return offset;
}

bool DFR_Radar::readPacket( char *buffer )
{
  unsigned long startTime = millis();
  bool result = false;

  while( !result )
  {
    if( millis() - startTime > readPacketTimeout )
      break;

    if( readBytes( buffer, packetLength ) == packetLength )
      if( strncmp( packetStart, buffer, strlen( packetStart ) ) == 0 )
        result = true;
  }

  buffer[packetLength] = '\0';

  return result;
}

bool DFR_Radar::checkPresence()
{
  char data[packetLength] = {0};

  // Should contain something like this: $JYBSS,1, , , *
  // ...with parameter 1 (character 7) being either 0 or 1.

  if( !readPacket( data ) )
    return false;

  return ( data[7] == '1' );
}


bool DFR_Radar::setDetectionArea( float rangeStart, float rangeEnd )
{
  if( rangeStart < 0 || rangeEnd < 0 || rangeEnd < rangeStart )
    return false;

  uint8_t _rangeStart = rangeStart / 0.15;
  uint8_t _rangeEnd   = rangeEnd / 0.15;

  if( _rangeStart > 127 || _rangeEnd > 127 )
    return false;

  char _comDetRangeCfg[23] = {0};
  sprintf( _comDetRangeCfg, comDetRangeCfg1, _rangeStart, _rangeEnd );

  setConfig( _comDetRangeCfg );

  return true;
}

bool DFR_Radar::setDetectionArea( float rangeA_Start, float rangeA_End, float rangeB_Start, float rangeB_End )
{
  if( rangeA_Start < 0 || rangeA_End < 0 || rangeA_End < rangeA_Start )
    return false;

  if( rangeB_Start < 0 || rangeB_End < 0 || rangeB_End < rangeB_Start )
    return false;

  if( rangeB_Start < rangeA_End )
    return false;

  uint8_t _rangeA_Start = rangeA_Start / 0.15;
  uint8_t _rangeA_End   = rangeA_End / 0.15;
  uint8_t _rangeB_Start = rangeB_Start / 0.15;
  uint8_t _rangeB_End   = rangeB_End / 0.15;

  if( _rangeA_Start > 127 || _rangeA_End > 127 || _rangeB_Start > 127 || _rangeB_End > 127 )
    return false;

  char _comDetRangeCfg[31] = {0};
  sprintf( _comDetRangeCfg, comDetRangeCfg2, _rangeA_Start, _rangeA_End, _rangeB_Start, _rangeB_End );

  setConfig( _comDetRangeCfg );

  return true;
}

bool DFR_Radar::setDetectionArea( float rangeA_Start, float rangeA_End, float rangeB_Start, float rangeB_End, float rangeC_Start, float rangeC_End )
{
  if( rangeA_Start < 0 || rangeA_End < 0 || rangeA_End < rangeA_Start )
    return false;

  if( rangeB_Start < 0 || rangeB_End < 0 || rangeB_End < rangeB_Start )
    return false;

  if( rangeC_Start < 0 || rangeC_End < 0 || rangeC_End < rangeC_Start )
    return false;

  if( rangeB_Start < rangeA_End || rangeC_Start < rangeB_End )
    return false;

  uint8_t _rangeA_Start = rangeA_Start / 0.15;
  uint8_t _rangeA_End   = rangeA_End / 0.15;
  uint8_t _rangeB_Start = rangeB_Start / 0.15;
  uint8_t _rangeB_End   = rangeB_End / 0.15;
  uint8_t _rangeC_Start = rangeC_Start / 0.15;
  uint8_t _rangeC_End   = rangeC_End / 0.15;

  if( _rangeA_Start > 127 || _rangeA_End > 127 || _rangeB_Start > 127 || _rangeB_End > 127 || _rangeC_Start > 127 || _rangeC_End > 127 )
    return false;

  char _comDetRangeCfg[39] = {0};
  sprintf( _comDetRangeCfg, comDetRangeCfg3, _rangeA_Start, _rangeA_End, _rangeB_Start, _rangeB_End, _rangeC_Start, _rangeC_End );

  setConfig( _comDetRangeCfg );

  return true;
}

bool DFR_Radar::setDetectionArea( float rangeA_Start, float rangeA_End, float rangeB_Start, float rangeB_End, float rangeC_Start, float rangeC_End, float rangeD_Start, float rangeD_End )
{
  if( rangeA_Start < 0 || rangeA_End < 0 || rangeA_End < rangeA_Start )
    return false;

  if( rangeB_Start < 0 || rangeB_End < 0 || rangeB_End < rangeB_Start )
    return false;

  if( rangeC_Start < 0 || rangeC_End < 0 || rangeC_End < rangeC_Start )
    return false;

  if( rangeD_Start < 0 || rangeD_End < 0 || rangeD_End < rangeD_Start )
    return false;

  if( rangeB_Start < rangeA_End || rangeC_Start < rangeB_End || rangeD_Start < rangeC_End )
    return false;

  uint8_t _rangeA_Start = rangeA_Start / 0.15;
  uint8_t _rangeA_End   = rangeA_End / 0.15;
  uint8_t _rangeB_Start = rangeB_Start / 0.15;
  uint8_t _rangeB_End   = rangeB_End / 0.15;
  uint8_t _rangeC_Start = rangeC_Start / 0.15;
  uint8_t _rangeC_End   = rangeC_End / 0.15;
  uint8_t _rangeD_Start = rangeD_Start / 0.15;
  uint8_t _rangeD_End   = rangeD_End / 0.15;

  if( _rangeA_Start > 127 || _rangeA_End > 127 || _rangeB_Start > 127 || _rangeB_End > 127 || _rangeC_Start > 127 || _rangeC_End > 127 || _rangeD_Start > 127 || _rangeD_End > 127 )
    return false;

  char _comDetRangeCfg[47] = {0};
  sprintf( _comDetRangeCfg, comDetRangeCfg4, _rangeA_Start, _rangeA_End, _rangeB_Start, _rangeB_End, _rangeC_Start, _rangeC_End, _rangeD_Start, _rangeD_End );

  setConfig( _comDetRangeCfg );

  return true;
}


bool DFR_Radar::setOutputLatency( float triggerDelay, float resetDelay )
{
  if( triggerDelay < 0 || resetDelay < 0 )
    return false;

  uint16_t _triggerDelay = triggerDelay * 1000 / 25;
  uint16_t _resetDelay   = resetDelay * 1000 / 25;

  if( _triggerDelay > 65535 || _resetDelay > 65535 )
    return false;

  char _comOutputLatency[29] = {0};
  sprintf( _comOutputLatency, comOutputLatency, _triggerDelay , _resetDelay );

  setConfig( _comOutputLatency );

  return true;
}

bool DFR_Radar::setSensitivity( uint8_t level )
{
  if( level < 0 || level > 9 )
    return false;

  char _comSetSensitivity[17] = {0};
  sprintf( _comSetSensitivity, comSetSensitivity, level );

  setConfig( _comSetSensitivity );

  return true;
}

void DFR_Radar::disableLED()
{
  configureLED( true );
}

void DFR_Radar::enableLED()
{
  configureLED( false );
}

void DFR_Radar::configureLED( bool disabled )
{
  char _comSetLedMode[15] = {0};
  sprintf( _comSetLedMode, comSetLedMode, disabled );

  setConfig( _comSetLedMode );
}

void DFR_Radar::enableAutoStart()
{
  configureAutoStart( true );
}

void DFR_Radar::disableAutoStart()
{
  configureAutoStart( false );
}

void DFR_Radar::configureAutoStart( bool autoStart )
{
  char _comSensorCfgStart[17] = {0};
  sprintf( _comSensorCfgStart, comSensorCfgStart, autoStart );

  setConfig( _comSensorCfgStart );
}

void DFR_Radar::factoryReset()
{
  setConfig( comFactoryReset );
}

void DFR_Radar::setConfig( const char *command )
{
  stop();
  sendCommand( command );
  saveConfig();
  start();
}

void DFR_Radar::start()
{
  sendCommand( comStart );
}

void DFR_Radar::stop()
{
  sendCommand( comStop );
}

void DFR_Radar::sendCommand( const char *command )
{
  sensorUART->write( command );
  delay( comDelay );
}

void DFR_Radar::saveConfig()
{
  sendCommand( comSaveCfg );
}
