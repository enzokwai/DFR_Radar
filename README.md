# DFR_Radar Library for Arduino

<!-- [![Arduino Lint](https://github.com/MaffooClock/DFR_Radar/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/MaffooClock/DFR_Radar/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/MaffooClock/DFR_Radar/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/MaffooClock/DFR_Radar/actions/workflows/compile-examples.yml) [![Arduino Library](https://www.ardu-badge.com/badge/DFR_Radar.svg?)](https://www.ardu-badge.com/DFR_Radar) [![PlatformIO Registry](https://badges.registry.platformio.org/packages/maffooclock/library/DFR_Radar.svg)](https://registry.platformio.org/libraries/maffooclock/DFR_Radar) -->

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

Soon, you will be able to install this library automatically from the Arduino Library or PlatformIO Registry.  I will update this README as soon as that happens.  Until then, manual installation is necessary.


#### Arduino IDE:

First, [click here](https://github.com/MaffooClock/DFR_Radar/archive/refs/heads/master.zip) to download a ZIP of this repo.  Do not un-ZIP it — leave it as a ZIP file.

 1. Click the Sketch menu
 2. Select "Include Library..." from the menu
 3. Select "Add .ZIP Library..." from the submenu
 4. Select the ZIP file you downloaded


#### Platform IO:

There are a couple of options (choose _one_, don't do all three):

 - Add `https://github.com/MaffooClock/DFR_Radar` to the [`lib_deps`](https://docs.platformio.org/en/stable/projectconf/sections/env/options/library/lib_deps.html) line in [platformio.ini](https://docs.platformio.org/en/stable/projectconf/index.html):

 - [Download a ZIP](https://github.com/MaffooClock/DFR_Radar/archive/refs/heads/master.zip) of this repo and un-zip it in the `lib` folder in your project folder.

 - Clone the repo from the command line:
 ```shell
 cd MyProject/lib
 git clone https://github.com/MaffooClock/DFR_Radar.git

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

