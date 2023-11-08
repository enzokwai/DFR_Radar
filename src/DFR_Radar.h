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
     * @brief Configure delays between state changes on output (IO2)
     *
     * @param triggerDelay  Time in seconds after the sensor has been triggered before setting output HIGH; factory default is 0.025s
     * @param resetDelay    Time in seconds after the sensor is no longer triggered before returning the output LOW; factory default is 5s
     *
     * @return false if either delay value is invalid (no changes made), true otherwise
     */
    bool setOutputLatency( float triggerDelay, float resetDelay );

    /**
     * @brief Check if the sensor is detecting presence
     *
     * @return true if presence is currently being detected
     * @return false if no presence or reading sensor failed
     */
    bool checkPresence( void );

    /**
     * @brief Sets a delay between when the presence detection resets and when it can trigger again.
     *
     * @note Used to prevent short-cycling (re-triggering immediately after a rest).
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
    bool setTriggerLevel( PinStatus triggerLevel );

    /**
     * @brief Start the sensor.
     *
     */
    void start( void );

    /**
     * @brief Stop the sensor
     *
     */
    void stop( void );

    /**
     * @brief Restart the sensor's internal software (safe; configuration is not lost or changed).
     *
     */
    void reboot( void );

    /**
     * @brief Disable the LED
     *
     */
    void disableLED( void );

    /**
     * @brief Enable the LED
     *
     */
    void enableLED( void );

    /**
     * @brief Set whether LED is enabled.
     *
     * @note Called by `disableLED()` and `enableLED()`
     *
     * @param disabled true if LED should be disabled, false for enabled
     */
    void configureLED( bool disabled );

    /**
     * @brief Enable automatic start on power-up.
     *
     */
    void enableAutoStart();

    /**
     * @brief Disable automatic start on power-up.
     *
     * @note Will need to call `start()` at runtime.
     *
     */
    void disableAutoStart();

    /**
     * @brief Set whether sensor will start automatically on power-up.
     *
     * @note Called by `disableAutoStart()` and `enableAutoStart()`
     *
     * @param autoStart true if sensor should start immediately after power-up,
     *                  false if not (will need to call `start()` at runtime)
     */
    void configureAutoStart( bool autoStart );

    /**
     * @brief Commits configuration data to flash
     *
     */
    void saveConfig();

    /**
     * @brief Restore the sensor configuration to factory default settings.
     *
     */
    void factoryReset( void );


  private:

    /**
     * @brief Read data from the serial port
     *
     * @param buffer Store the read data
     * @param length The number of bytes to read
     *
     * @return the actual length of bytes read
     */
    size_t readBytes( char *buffer, size_t length );

    /**
     * @brief Read complete data packet
     *
     * @note The packet should be 15 bytes long and look like this:
     *         `$JYBSS,1, , , *`
     *       The first field is presence detection (0 or 1), and the
     *       remaining three fields are reserved (always be spaces).
     *
     * @param buffer Store the read data
     *
     * @return true if successful, false otherwise
     */
    bool readPacket( char *buffer );

    /**
     * @brief Executes a command string after first stopping the sensor, then
     *        afterwards saves the configuration and re-starts the sensor
     *
     * @note Each of the methods called by this one also call `sendCommand()`, which
     *       will delay for `comDelay` -- thus, this method will delay for `4 x comDelay`
     *
     * @param command A command string generated by one of the configuration methods
     */
    void setConfig( const char *command );

    /**
     * @brief Writes a command string to the sensor UART port, then delays for `comDelay`
     *
     * @param command A command string generated by one of the other config/command methods
     */
    void sendCommand( const char *command );

    /**
     * @brief The serial port (hardware or software) to use for communicating with the sensor
     *
     */
    Stream *sensorUART;


    static const uint16_t readBytesTimeout         =  100;
    static const uint16_t readPacketTimeout        = 1000;
    static const size_t packetLength               =   15;
    static constexpr const char *packetStart       = "$JYBSS";

    static const unsigned long comDelay            = 1000;
    static constexpr const char *comStop           = "sensorStop";
    static constexpr const char *comStart          = "sensorStart";
    static constexpr const char *comResetSystem    = "resetSystem 0";
    static constexpr const char *comDetRangeCfg1   = "detRangeCfg -1 %u %u";
    static constexpr const char *comDetRangeCfg2   = "detRangeCfg -1 %u %u %u %u";
    static constexpr const char *comDetRangeCfg3   = "detRangeCfg -1 %u %u %u %u %u %u";
    static constexpr const char *comDetRangeCfg4   = "detRangeCfg -1 %u %u %u %u %u %u %u %u";
    static constexpr const char *comSetSensitivity = "setSensitivity %u";
    static constexpr const char *comOutputLatency  = "outputLatency -1 %u %u";
    static constexpr const char *comSetGpioMode    = "setGpioMode 1 %u";
    static constexpr const char *comSetInhibit     = "setInhibit %u";
    static constexpr const char *comSetLedMode     = "setLedMode 1 %u";
    static constexpr const char *comSensorCfgStart = "sensorCfgStart %u";
    static constexpr const char *comSaveCfg        = "saveConfig";  // "saveCfg 0x45670123 0xCDEF89AB 0x956128C6 0xDF54AC89";
    static constexpr const char *comFactoryReset   = "resetCfg";    // "factoryReset 0x45670123 0xCDEF89AB 0x956128C6 0xDF54AC89";
};

#endif
