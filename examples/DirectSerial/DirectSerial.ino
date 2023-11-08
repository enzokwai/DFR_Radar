/**
 * DFR_Radar: DirectSerial.ino
 * 
 * This example connects the USB serial console directly to the UART of
 * the radar sensor, allowing you to interact directly with the sensor.
 * 
 * Created 8 November 2023
 * By Matthew Clark
 */

#include <DFR_Radar.h>

// Serial1 is the hardware UART pins
DFR_Radar sensor( &Serial1 );

void setup()
{
  // The USB serial console must be set to the same speed as the radar sensor
  Serial.begin( 115200 );
  
  // The radar sensor is factory-set for 115200 baud
  Serial1.begin( 115200 );
  
  // Restore to the factory settings, if necessary
  // sensor.factoryReset();
}

void loop()
{
  if( Serial.available() )            // If anything comes in Serial (USB),
    Serial1.write( Serial.read() );   // read it and send it out Serial1

  if( Serial1.available() )           // If anything comes in Serial1
    Serial.write( Serial1.read() );   // read it and send it out Serial (USB)
}
