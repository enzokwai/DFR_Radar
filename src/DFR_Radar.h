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


#ifndef __DFR_Radar_H__
#define __DFR_Radar_H__

#include <Arduino.h>


class DFR_Radar
{
  public:

    /**
      * @brief Constructor
      * @param Stream  Software serial port interface
      */
    DFR_Radar( Stream *s );

    /**
     * @brief Not currently implemented
     *
     * @return true
     */
    bool begin( void );

    /**
     * @brief Configure sensor detection for a single range
     *
     * @note Values are in meters; minimum is 0, maximum is 19.05; end must be greater than start
     *
     * @param rangeStart
     * @param rangeEnd
     *
     * @return false if the range values are invalid (no changes made), true otherwise
     */
    bool setDetectionArea( float rangeStart, float rangeEnd );

    /**
     * @brief Configure sensor detection for two ranges
     *
     * @note Values are in meters; minimum is 0, maximum is 19.05; end must be greater than start;
     *       subsequent range start value must be greater than previous range end value
     *
     * @param rangeA_Start
     * @param rangeA_End
     *
     * @param rangeB_Start
     * @param rangeB_End
     *
     * @return false if any of the range values are invalid (no changes made), true otherwise
     */
    bool setDetectionArea(
      float rangeA_Start, float rangeA_End,
      float rangeB_Start, float rangeB_End
    );

    /**
     * @brief Configure sensor detection for three ranges
     *
     * @note Values are in meters; minimum is 0, maximum is 19.05; end must be greater than start;
     *       subsequent range start value must be greater than previous range end value
     *
     * @param rangeA_Start
     * @param rangeA_End
     *
     * @param rangeB_Start
     * @param rangeB_End
     *
     * @param rangeC_Start
     * @param rangeC_End
     *
     * @return false if any of the range values are invalid (no changes made), true otherwise
     */
    bool setDetectionArea(
      float rangeA_Start, float rangeA_End,
      float rangeB_Start, float rangeB_End,
      float rangeC_Start, float rangeC_End
    );

    /**
     * @brief Configure sensor detection for four ranges
     *
     * @note Values are in meters; minimum is 0, maximum is 19.05; end must be greater than start;
     *       subsequent range start value must be greater than previous range end value
     *
     * @param rangeA_Start
     * @param rangeA_End
     *
     * @param rangeB_Start
     * @param rangeB_End
     *
     * @param rangeC_Start
     * @param rangeC_End
     *
     * @param rangeD_Start
     * @param rangeD_End
     *
     * @return false if any of the range values are invalid (no changes made), true otherwise
     */
    bool setDetectionArea(
      float rangeA_Start, float rangeA_End,
      float rangeB_Start, float rangeB_End,
      float rangeC_Start, float rangeC_End,
      float rangeD_Start, float rangeD_End
    );

    /**
     * @brief Set the sensitivity level
     *
     * @param level  0 = Low, 9 = High, 7 = Factory Default
     *
     * @return false if the level value is invalid (no changes made), true otherwise
     */
    bool setSensitivity( uint8_t level );

    /**
     * @brief Configure delays that translate actual presence activity to sensor assertion of presence
     *
     * @note A longer confirmation delay can reduce false positives.  A longer disappearance delay can bridge gaps between presence events.
     *
     * @param confirmationDelay  Time in seconds of continuous presence activity before the sensor actually asserts presence; factory default is 0.025s
     * @param disappearanceDelay Time in seconds without any presence activity before desserting presence; factory default is 5s
     *
     * @return false if either delay value is invalid (no changes made), true otherwise
     */
    bool setTriggerLatency( float confirmationDelay, float disappearanceDelay );

    /**
     * @brief Configure delays between state changes on output (IO2)
     *
     * @param triggerDelay  Time in seconds after the sensor has been triggered before setting output HIGH; factory default is 2.5s
     * @param resetDelay    Time in seconds after the sensor is no longer triggered before returning the output LOW; factory default is 10s
     *
     * @return false if either delay value is invalid (no changes made), true otherwise
     */
    bool setOutputLatency( float triggerDelay, float resetDelay );

    /**
     * @brief Check if the sensor is detecting presence
     *
     * @return true if presence is currently being detected;
     *         false if no presence or reading sensor failed
     */
    bool checkPresence( void );

    /**
     * @brief Sets a delay between when the presence detection resets and when it can trigger again.
     *
     * @note Used to prevent short-cycling (re-triggering immediately after a reset).
     *
     * @param time  Time in seconds after the presence detection has reset before it can be triggered again.
     *              Range is 0.1 - 255; factory default is 1
     *
     * @return false if the value is invalid (no changes made), true otherwise
     */
    bool setLockout( float time );

    /**
     * @brief Set whether the IO2 pin is HIGH or LOW when triggered.
     *
     * @param triggerLevel  HIGH = Vcc when triggered, Ground when idle (factory default)
     *                      LOW  = Ground when triggered, Vcc when idle
     *
     * @return false if the value is invalid (no changes made), true otherwise
     */
    bool setTriggerLevel( uint8_t triggerLevel );

    /**
     * @brief Start the sensor
     *
     * @return true if sensor started (or was already started);
     *         false if sensor failed to start
     */
    bool start( void );

    /**
     * @brief Stop the sensor
     *
     * @return true if sensor stopped (or was already stopped);
     *         false if sensor failed to stop
     */
    bool stop( void );

    /**
     * @brief Restart the sensor's internal software (safe; configuration is not lost or changed).
     *
     */
    void reboot( void );

    /**
     * @brief Disable the LED
     *
     * @return true if command was successful
     */
    bool disableLED( void );

    /**
     * @brief Enable the LED
     *
     * @return true if command was successful
     */
    bool enableLED( void );

    /**
     * @brief Set whether LED is enabled.
     *
     * @note Called by `disableLED()` and `enableLED()`
     *
     * @param disabled true if LED should be disabled, false for enabled
     *
     * @return true if command was successful
     */
    bool configureLED( bool disabled );

    /**
     * @brief Allows setting multiple configuration options without
     *        stopping/saving/re-starting with each one.  Make sure
     *        to call `configEnd()` after making changes.
     *
     * @return false if the sensor failed to stop (multi-config mode will be disabled), true otherwise
     */
    bool configBegin( void );

    /**
     * @brief Allows setting multiple configuration options without
     *        stopping/saving/re-starting with each one.  Must call
     *        `configBegin()` first.
     *
     * @return false if multi-config mode isn't enabled (forgot to call `configBegin()` first or it failed),
     *         or if saving or re-starting failed; true otherwise
     */
    bool configEnd( void );

    /**
     * @brief Restore the sensor configuration to factory default settings.
     *
     * @return true if command was successful;
     *         false if the sensor failed to stop or if the ecommand failed
     */
    bool factoryReset( void );


  private:

    /**
     * @brief Read a line (or more) from the UART port
     *
     * @param buffer Store the read data
     *
     * @return length of characters captured
     */
    size_t readLines( char *buffer, size_t lineCount = 1 );

    /**
     * @brief Executes a command string after first stopping the sensor, then afterwards
     *        saves the configuration and re-starts the sensor.
     *
     * @details If multi-config mode is enabled (`configBegin()` was called earlier),
     *          this this method only executes the command string, and `configEnd()`
     *          must be called to save the configuration and re-start the sensor.
     *
     * @param command A command string generated by one of the configuration methods
     *
     * @return true if command was successful;
     *         false if sensor failed to stop or re-start, command failed, or save failed
     */
    bool setConfig( const char *command );

    /**
     * @brief Commits configuration data to flash
     *
     * @return true if command was successful
     */
    bool saveConfig( void );

    /**
     * @brief Writes a command string to the sensor UART port and waits for response
     *
     * @param command A command string generated by one of the other config/command methods
     *
     * @return true if response was "Done";
     *         false if "Error" or timeout
     */
    bool sendCommand( const char *command );

    /**
     * @brief The serial port (hardware or software) to use for communicating with the sensor
     *
     */
    Stream *sensorUART;

    // bool isConfigured;
    bool stopped;
    bool multiConfig;

    static const uint16_t readPacketTimeout         =  100;
    static const size_t packetLength                =   64;

    static const unsigned long startupDelay         = 2000;

    static const unsigned long comTimeout           = 1000;
    static constexpr const char *comStop            = "sensorStop";
    static constexpr const char *comStart           = "sensorStart";
    static constexpr const char *comResetSystem     = "resetSystem 0";
    static constexpr const char *comDetRangeCfg1    = "detRangeCfg -1 %u %u";
    static constexpr const char *comDetRangeCfg2    = "detRangeCfg -1 %u %u %u %u";
    static constexpr const char *comDetRangeCfg3    = "detRangeCfg -1 %u %u %u %u %u %u";
    static constexpr const char *comDetRangeCfg4    = "detRangeCfg -1 %u %u %u %u %u %u %u %u";
    static constexpr const char *comSetSensitivity  = "setSensitivity %u";
    static constexpr const char *comOutputLatency   = "outputLatency -1 %u %u";
    static constexpr const char *comSetLatency      = "setLatency %.3f %.3f";
    static constexpr const char *comSetGpioMode     = "setGpioMode 1 %u";
    static constexpr const char *comGetOutput       = "getOutput 1";
    static constexpr const char *comSetInhibit      = "setInhibit %.3f";
    static constexpr const char *comSetLedMode      = "setLedMode 1 %u";
    // static constexpr const char *comSetUartOutput   = "setUartOutput 1 1 0 1501";
    static constexpr const char *comSetEcho         = "setEcho 0";
    static constexpr const char *comResponseSuccess = "Done";
    static constexpr const char *comResponseFail    = "Error";
    static constexpr const char *comSaveCfg         = "saveConfig";  // "saveCfg 0x45670123 0xCDEF89AB 0x956128C6 0xDF54AC89";
    static constexpr const char *comFactoryReset    = "resetCfg";    // "factoryReset 0x45670123 0xCDEF89AB 0x956128C6 0xDF54AC89";
};

#endif
