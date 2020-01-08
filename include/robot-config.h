/*------------------------------------------------------------------------------------------------------
[CONFIG] robot-config > Defines connected devices.
Every file MUST have these lines of code on top:
//Connected devices file
#ifndef CONFIG_H
#define CONFIG_H
#include "robot-config.h"
#endif
------------------------------------------------------------------------------------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++| INFOMATION |++++++++++++++++++++++++++++++++++++++++++++++
This is a sample robot-config.h file for ACCESS_OS (Sample meaning not complete, a templete/base)

The robot specs are as follows:
2 motor omniwheel drive

A small batch of example programs are provided, but you'll need to modify the code to fit your robot.

Changelog, documentation, and more information can be found at the ACCESS_OS website.
Link to website: https://dev.azure.com/roboVEX/_git/ACCESS_OS
------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Includes > Include needed external libraries and files
------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>		//Include math.h in order to gain access to math functions like PI.
#include <tgmath.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Devices > Connected devices and sensors
------------------------------------------------------------------------------------------------------*/
//Main compoments
vex::brain Brain;
vex::controller Controller = vex::controller();

//Drive motors
vex::motor LeftBaseM1 = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1, false);		//geared 1:1
vex::motor RightBaseM1 = vex::motor(vex::PORT10, vex::gearSetting::ratio18_1, true);	//geared 1:1

//Create object Compettition of the Competition class
#ifndef COMPETITION_DEFINED
#define COMPETITION_DEFINED
vex::competition Competition;
#endif
