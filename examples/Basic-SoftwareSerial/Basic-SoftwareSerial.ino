/**
 * DFR_Radar: Basic-SoftwareSerial.ino
 * 
 * This is a basic example of how to instantiate a DFR_Radar object using
 * Software Serial.
 *
 * The detection area and sensitivity are set quite low to make it easier
 * to test the unit right in front of you (too high and it'll just stay
 * triggered, and that's no fun!).
 * 
 * When motion is detected, it will turn on the built-in LED.
 * 
 * Created 8 November 2023
 * By Matthew Clark
 */

#include <DFR_Radar.h>
#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;

#ifdef ESP32
  EspSoftwareSerial::UART sensorSerial;
#else
  // Create a software serial port
  // First argument is receive, second is transmit
  SoftwareSerial sensorSerial( rxPin, txPin );
#endif

// Create a DFR_Radar instance
DFR_Radar sensor( &sensorSerial );

void setup()
{
  Serial.begin( 9600 );
  
  #ifdef ESP32
    sensorSerial.begin( 115200, SWSERIAL_8N1, rxPin, txPin );
  #else
    // The DFRobot device is factory-set for 115200 baud
    sensorSerial.begin( 115200 );
  #endif
  
  // Restore to the factory settings -- it's not necessary to do this unless needed
  sensor.factoryReset();

  // Set a detection range of 0 to 1 meter (19.05m is the maximum)
  sensor.setDetectionArea( 0, 1 );

  // Lower the sensitivity so that it's easier to test
  sensor.setSensitivity( 2 );

  // This will cause the LED to turn on 1 second after presence is detected and
  // it will stay on for 5 seconds after the sensor no longer detects presence.
  // Set both of these to 0 for instant on/off, although you may get short-cycling.
  sensor.setOutputLatency( 1, 5 );

  // The default timeout is 1 second, which could cause
  // the `loop()` to be too slow.  100ms seems to work.
  sensorSerial.setTimeout( 100 );

  // Setup the built-in LED
  pinMode( LED_BUILTIN, OUTPUT );
}

void loop()
{
  /**
   * NOTE: if you use any `delay()` here, the
   * more of them plus the longer they are,
   * the more likely the presence events will
   * be missed.
   */

  // Query the presence detection status
  bool presence = sensor.checkPresence();

  // If presence == true, turn on the built-in LED.
  digitalWrite( LED_BUILTIN, presence );

  // Your serial monitor will show constant 1's or 0's depending
  Serial.println( presence );
}
