//MAIN_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "v5_vcs.h"
#include "..\src\auton\routines\manual.h"
#include "..\src\auton\gui\ACCESS_OS\ACCESS_OS.h"
#include "..\src\calc\calc.h"
#include "..\src\config\config.h"
#include "..\src\calc\PID\PID.h"
#include "..\src\calc\FPS\FPS.h"
#include "..\src\calc\MAPS\MAPS.h"
#include "..\src\calc\ATUNE\ATUNE.h"
#include "..\src\calc\TUNER\TUNER.h"
#include "..\src\motor\DRIVE\IMU\IMU.h"
#include "..\src\motor\DRIVE\BASE_DRIVE\BASE_DRIVE.h"
#include "..\src\motor\DRIVE\MECH_DRIVE\MECH_DRIVE.h"
#include "..\src\motor\DRIVE\X_DRIVE\X_DRIVE.h"
#include "..\src\motor\LIFTER\LIFTER.h"
#include "..\src\motor\TILTER\TILTER.h"
#include "..\src\motor\ROBOT.h"
using namespace std;
using namespace vex;

// gui.cpp
void pre_auton(void);

// usercontrol.cpp
void usercontrol(void);

// controls.cpp
void controls(void);

//autonomous.cpp
void autonomous(void);

//port 3&4&10&11 ded
extern ACCESS_OS os;
extern ROBOT robot;