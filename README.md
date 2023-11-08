# DFR_Radar Library for Arduino

[![Arduino Lint](https://github.com/MaffooClock/DFR_Radar/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/MaffooClock/DFR_Radar/actions/workflows/check-arduino.yml)  [![Compile Examples](https://github.com/MaffooClock/DFR_Radar/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/MaffooClock/DFR_Radar/actions/workflows/compile-examples.yml)  [![Arduino Library](https://www.ardu-badge.com/badge/DFR_Radar.svg?)](https://www.ardu-badge.com/DFR_Radar)  [![PlatformIO Registry](https://badges.registry.platformio.org/packages/maffooclock/library/DFR_Radar.svg)](https://registry.platformio.org/libraries/maffooclock/DFR_Radar)

This is a maintained version of the [original DFRobot_mmWave_Radar](https://github.com/DFRobotdl/DFRobot_mmWave_Radar) library.  After more than two years had passed without any commits beyond the initial commit, and issues receiving no attention, I assumed that it had become abandonware, so decided to fork this library to bring it up-to-date and get it published into the Arduino Library and PlatformIO Registry.

The SEN0395 24GHz millimeter-wave Human Presence Detection sensor (available from [DFRobot.com](https://www.dfrobot.com/product-2282.html)) is a fantastic device that works well, is software-configurable, and didn't deserve to be crippled by an unfinished library.


## Table of Contents

* [About the SEN0395](#about-the-sen0395)
* [Installation](#installation)
* [Methods](#methods)
* [Compatability](#compatability)
* [Credits](#credits)


## About the SEN0395

![Front and back of DFRobot SEN0395 module](.github/photos/SEN0395.png)

This 24GHz millimeter-wave radar sensor employs a [frequency-modulated continuous-wave (FMCW) radar](https://en.wikipedia.org/wiki/Continuous-wave_radar#Modulated_continuous-wave) featuring multi-mode modulation and separate transmit and receive antennas.

The radar sensor can detect human presence — both in motion and stationary — within a configurable detection area.  Moreover, it can even detect static or stationary human presence such as a sleeping person. There are two ways provided to output detection result: serial port and I/O port switch quantity. Besides that, the sensor module features strong sensing reliability, high sensitivity, small size, easy to be used or embedded in applications.


## Installation

This library is available in both the Arduino Library Manager and the PlatformIO Registry.


#### Arduino IDE:

There are multiple ways, but three of those are below (pick **one**, don't do all three!):

 - Search the Library Manager for `DFR_Radar`

 - Use the command line interface:
   ```shell
   arduino-cli lib install DFR_Radar@1.0.0
   ```

 -  Manual install: download the [latest release](https://github.com/MaffooClock/DFR_Radar/releases/latest), then see the documentation on [Importing a .zip Library](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries#importing-a-zip-library).


#### PlatformIO:

There are multiple ways, but three of those are below (pick **one**, don't do all three!):

 - Search the [Library Registry](https://registry.platformio.org/search?t=library) for `MaffooClock/DFR_Radar` and install it automatically.

 - Edit your [platformio.ini](https://docs.platformio.org/en/latest/projectconf/index.html) file and add `MaffooClock/DFR_Radar@^1.0.0` to the [`lib_deps`](https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_deps.html) stanza.

 - Use the command line interface:
   ```shell
   cd MyProject
   pio pkg install --library "MaffooClock/DFR_Radar@^1.0.0"
   ```


### Include the Header

Finally, just add `#include <DFR_Radar.h>` to the top of your project (below `#include <Arduino.h>` if it exists).


## Methods

_Documentation update in progress..._


## Compatibility

| **MCU**                         | **Tested - Works** | **Tested - Doesn't Work** |   **Untested**   | **Remarks** |
|---------------------------------|:------------------:|:-------------------------:|:----------------:|-------------|
| Arduino Uno (ATmega328P)        | :white_check_mark: |                           |                  |             |
| Arduino Nano Every (ATMega4809) | :white_check_mark: |                           |                  |             |
| Arduino Mega2560                | :white_check_mark: |                           |                  |             |
| Arduino Leonardo (ATmega32u4)   |                    |                           |:heavy_check_mark:|             |
| ESP32                           | :white_check_mark: |                           |                  |             |


## Credits

Originally written by huyujie (yujie.hu@dfrobot.com) in 2020 and published at [DFRobotdl/DFRobot_mmWave_Radar](https://github.com/DFRobotdl/DFRobot_mmWave_Radar).

Forked and updated by [Matthew Clark](https://github.com/MaffooClock) in November 2023.

