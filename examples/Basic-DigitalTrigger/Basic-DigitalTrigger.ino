/**
 * DFR_Radar: Basic-DigitalTrigger.ino
 * 
 * This is a basic example of how to instantiate a DFR_Radar object using
 * the second UART available on most Arduino boards.  This example is almost
 * identical to the Basic.ino, except this one uses a digital input to check
 * for presence triggering instead of querying over serial, which could be
 * somewhat faster.
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

// Serial1 is the hardware UART pins
DFR_Radar sensor( &Serial1 );

// IO2 from sensor is connected to pin 3 on the Arduino
const int TRIGGER_INPUT = 3;

void setup()
{
  Serial.begin( 9600 );
  
  // The DFRobot device is factory-set for 115200 baud
  Serial1.begin( 115200 );

  // Setup the built-in LED
  pinMode( LED_BUILTIN, OUTPUT );

  // Configure the digital input used to detect presence triggers
  pinMode( TRIGGER_INPUT, INPUT );
  
  // Restore to the factory settings -- it's not necessary to do this unless needed
  sensor.factoryReset();

  // Set a detection range of 0 to 1 meter (9.45m is the maximum)
  sensor.setDetectionRange( 0, 1 );

  // Lower the sensitivity so that it's easier to test
  sensor.setSensitivity( 2 );

  // This will cause the LED to turn on 1 second after presence is detected and
  // it will stay on for 5 seconds after the sensor no longer detects presence.
  // Set both of these to 0 for instant on/off, although you may get short-cycling.
  sensor.setOutputLatency( 1, 5 );
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
  bool presence = digitalRead( TRIGGER_INPUT );

  // If presence == true, turn on the built-in LED.
  digitalWrite( LED_BUILTIN, presence );

  // Your serial monitor will show constant 1's or 0's depending
  Serial.println( presence );
}
