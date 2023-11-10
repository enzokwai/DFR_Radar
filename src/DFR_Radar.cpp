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
  // isConfigured = false;
  stopped = false;
  multiConfig = false;
}

bool DFR_Radar::begin()
{
  /* Not sure if I want to impliment this, keeping it for future consideration...

  unsigned long startTime = millis() + startupDelay;

  // Give the sensor time to start up just in case this method is called too soon.
  //
  // There's probably a smarter way to do this.  Factory default configuration will
  // have the sensor dumping out $JYBSS messages once per second, so that could be
  // an easy way to tell that it's "ready".  But if the sensor is configured to send
  // these only when queried, or when an presence event occurs, or if the interval
  // is set too long, then this won't really work.
  //
  // Another way might be to send a `sensorStart` and see if 1) it complains about
  // not being ready, or 2) it responds with "sensor started already" and "Error",
  // or 3) actually starts?

  while( millis() < startTime )
    yield();

  if( !stop() )
    return false;

  // Disable command echoing (less response data that we have to parse through)
  sendCommand( comSetEcho );

  // Disable periodic $JYBSS messages (we will query for them)
  sendCommand( comSetUartOutput );

  if( !saveConfig() )
    return false;

  if( !start() )
    return false;

  isConfigured = true;

  */

  return true;
}

size_t DFR_Radar::readLines( char *buffer, size_t lineCount )
{
  unsigned long timeLimit = millis() + readPacketTimeout;
  size_t offset = 0, linesLeft = lineCount;

  while( linesLeft && millis() < timeLimit )
  {
    if( sensorUART->available() <= 0 )
      continue;

    char c = sensorUART->read();

    if( c == '\r' )
      continue;

    buffer[offset++] = c;

    if( c == '\n' )
      linesLeft--;
  }

  return strlen( buffer );
}

bool DFR_Radar::checkPresence()
{
  char packet[packetLength] = {0};

  // Factory default settings have $JYBSS messages sent once per second,
  // but we won't want to wait; this will prompt for status immediately
  sensorUART->write( comGetOutput );

  /**
   * Get the response immediately after sending the command.
   *
   * If command echoing is enabled, there should be three lines:
   *   1. the "getOutput 1" echoed back
   *   2. a "Done" status
   *   3. the "leapMMW:/>" response followed by the $JYBSS data we want
   *
   * If command echoing is disabled, there should be two lines:
   *   1. a "Done" status
   *   2. the $JYBSS data we want
   *
   * Factory default is command echoing on (might change this in `begin()`)
   */
  size_t length = readLines( packet, 3 );

  if( !length )
    return false;

  const size_t expectedLength = 16;
  char data[expectedLength] = {0};
  uint8_t offset = 0;
  bool startCharacterFound = false, endCharacterFound = false;

  /**
   * Parse through the packet until we find a "$", and
   * then start capturing characters until we find a "*"
   *
   * We're expecting to get something like: $JYBSS,1, , , *
   */
  for( uint8_t i = 0; i < length; i++ )
  {
    char c = packet[i];

    if( c == '$' )
      startCharacterFound = true;

    if( !startCharacterFound )
      continue;

    if( c == '*' )
      endCharacterFound = true;

    data[offset++] = c;

    if( endCharacterFound || offset == expectedLength )
      break;
  }

  if( !startCharacterFound || !endCharacterFound )
    return false;

  return ( data[7] == '1' );
}

bool DFR_Radar::setLockout( float time )
{
  if( time < 0.1 || time > 255 )
    return false;

  char _comSetInhibit[19] = {0};
  sprintf( _comSetInhibit, comSetInhibit, time );

  return setConfig( _comSetInhibit );
}

bool DFR_Radar::setTriggerLevel( uint8_t triggerLevel )
{
  if( triggerLevel != HIGH || triggerLevel != LOW )
    return false;

  char _comSetGpioMode[16] = {0};
  sprintf( _comSetGpioMode, comSetGpioMode, triggerLevel );

  return setConfig( _comSetGpioMode );
}

bool DFR_Radar::setDetectionArea( float rangeStart, float rangeEnd )
{
  if( rangeStart < 0 || rangeEnd < 0 || rangeEnd < rangeStart )
    return false;

  // Convert meters into 15cm units
  uint8_t _rangeStart = rangeStart / 0.15;
  uint8_t _rangeEnd   = rangeEnd / 0.15;

  if( _rangeStart > 127 || _rangeEnd > 127 )
    return false;

  char _comDetRangeCfg[23] = {0};
  sprintf( _comDetRangeCfg, comDetRangeCfg1, _rangeStart, _rangeEnd );

  return setConfig( _comDetRangeCfg );
}

bool DFR_Radar::setDetectionArea( float rangeA_Start, float rangeA_End, float rangeB_Start, float rangeB_End )
{
  if( rangeA_Start < 0 || rangeA_End < 0 || rangeA_End < rangeA_Start )
    return false;

  if( rangeB_Start < 0 || rangeB_End < 0 || rangeB_End < rangeB_Start )
    return false;

  if( rangeB_Start < rangeA_End )
    return false;

  // Convert meters into 15cm units
  uint8_t _rangeA_Start = rangeA_Start / 0.15;
  uint8_t _rangeA_End   = rangeA_End / 0.15;
  uint8_t _rangeB_Start = rangeB_Start / 0.15;
  uint8_t _rangeB_End   = rangeB_End / 0.15;

  if( _rangeA_Start > 127 || _rangeA_End > 127 || _rangeB_Start > 127 || _rangeB_End > 127 )
    return false;

  char _comDetRangeCfg[31] = {0};
  sprintf( _comDetRangeCfg, comDetRangeCfg2, _rangeA_Start, _rangeA_End, _rangeB_Start, _rangeB_End );

  return setConfig( _comDetRangeCfg );
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

  // Convert meters into 15cm units
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

  return setConfig( _comDetRangeCfg );
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

  // Convert meters into 15cm units
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

  return setConfig( _comDetRangeCfg );
}


bool DFR_Radar::setTriggerLatency( float confirmationDelay, float disappearanceDelay )
{
  if( confirmationDelay < 0 || confirmationDelay > 100 )
    return false;

  if( disappearanceDelay < 0 || disappearanceDelay > 1500 )
    return false;

  char _comSetLatency[28] = {0};
  sprintf( _comSetLatency, comSetLatency, confirmationDelay , disappearanceDelay );

  return setConfig( _comSetLatency );
}


bool DFR_Radar::setOutputLatency( float triggerDelay, float resetDelay )
{
  if( triggerDelay < 0 || resetDelay < 0 )
    return false;

  // Convert seconds into 25ms units
  uint32_t _triggerDelay = triggerDelay * 1000 / 25;
  uint32_t _resetDelay   = resetDelay * 1000 / 25;

  if( _triggerDelay > 65535 || _resetDelay > 65535 )
    return false;

  char _comOutputLatency[29] = {0};
  sprintf( _comOutputLatency, comOutputLatency, _triggerDelay , _resetDelay );

  return setConfig( _comOutputLatency );
}

bool DFR_Radar::setSensitivity( uint8_t level )
{
  if( level > 9 )
    return false;

  char _comSetSensitivity[17] = {0};
  sprintf( _comSetSensitivity, comSetSensitivity, level );

  return setConfig( _comSetSensitivity );
}

bool DFR_Radar::disableLED()
{
  return configureLED( true );
}

bool  DFR_Radar::enableLED()
{
  return configureLED( false );
}

bool DFR_Radar::configureLED( bool disabled )
{
  char _comSetLedMode[15] = {0};
  sprintf( _comSetLedMode, comSetLedMode, disabled );

  return setConfig( _comSetLedMode );
}

bool DFR_Radar::factoryReset()
{
  if( !stop() )
    return false;

  return sendCommand( comFactoryReset );
}

bool DFR_Radar::configBegin()
{
  if( multiConfig )
    return true;

  if( !stop() )
    return false;

  multiConfig = true;

  return true;
}

bool DFR_Radar::configEnd()
{
  if( !multiConfig )
    return false;

  multiConfig = false;

  if( !saveConfig() )
    return false;

  if( !start() )
    return false;

  return true;
}

bool DFR_Radar::setConfig( const char *command )
{
  if( multiConfig )
  {
    return sendCommand( command );
  }
  else
  {
    if( !stop() )
      return false;

    if( !sendCommand( command ) )
      return false;

    bool saved = saveConfig();

    if( !start() )
      return false;

    return saved;
  }
}

bool DFR_Radar::saveConfig()
{
  return sendCommand( comSaveCfg );
}

bool DFR_Radar::start()
{
  if( !stopped )
    return true;

  if( !sendCommand( comStart ) )
    return false;

  stopped = false;
  return true;
}

bool DFR_Radar::stop()
{
  if( stopped )
    return true;

  if( !sendCommand( comStop ) )
    return false;

  stopped = true;
  return true;
}

void DFR_Radar::reboot()
{
  sendCommand( comResetSystem );
}

bool DFR_Radar::sendCommand( const char *command )
{
  char responseBuffer[32] = {0};
  unsigned long timeout = millis() + comTimeout;

  static const size_t successLength = strlen( comResponseSuccess );
  static const size_t failLength = strlen( comResponseFail );
  static const size_t minResponseLength = min( successLength, failLength );

  const size_t commandLength = strlen( command );
  const size_t minLength = min( commandLength, minResponseLength );

  // Make sure we have exactly enough time
  sensorUART->setTimeout( comTimeout );

  // Send the command...
  sensorUART->write( command );

  // ...then wait for a response
  while( millis() < timeout )
  {
    if( sensorUART->available() <= 0 )
      continue;

    // Start with an empty buffer
    responseBuffer[0] = '\0';

    // Read a whole line
    size_t responseLength = sensorUART->readBytesUntil( '\n', responseBuffer, sizeof( responseBuffer ) );

    // We got something shorter than anything we're expecting, so try again
    if( responseLength < minLength )
      continue;

    // Check if that line is an echo of the original command
    if( strncmp( command, responseBuffer, commandLength ) == 0 )
      continue;

    // ...or if that line says "Done"
    if( strncmp( comResponseSuccess, responseBuffer, successLength ) == 0 )
      return true;

    // ...or if that line says "Error"
    if( strncmp( comResponseFail, responseBuffer, failLength ) == 0 )
      return false;

    // ...we got nothing we expected, so try again
  }

  // We've timed out
  return false;
}
