# buildhat++

buildhat++ is a student-made library to control Lego motors and color sensors via the buildHAT's serial port.

## Installation

First you need to install the libserial library which allows C/C++ code to send commands over the serial port.

On a Debian-based system you can do this with the command:

```bash
sudo apt install libserial-dev
```

Otherwise see [the documentation](https://github.com/crayzeewulf/libserial).

## Usage

In the buildhat++ directory run

```bash
cmake .
cmake --build ./
```
The example executables will now be in the buildhat++/bin/ directory.

## Structure

Inside src you will find the relevant Buildhat.cpp and config.hpp files as well as functions and modules directories. Following is a short overview of the contents. For more details please see the documentation within each respective header file.

### Buildhat.cpp

This file contains the setup code that loads the buildHAT firmware. This loading process has to be done every time the power to the buildHAT is disconnected. It also provides read/write functions for the serial interface.

### config.hpp

Here you can set the serial device, path to firmware file as well as ports for motors and sensors.

### functions

This directory contains a class for a differential driving setup with 2 motors as well as a stop function that actively holds the motors in position and a coast function that just stops power going to the motors.

### modules

#### actuators

This directory contains a class for a single Motor with a function to drive the motor forwards or backwards via PWM as well as the same stop and coast functions described above.

#### sensors

This directory contains code for calibrating a Lego color sensor and getting the color in front of said sensor.


