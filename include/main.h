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
#include "auton\manual.h"
#include "ACCESS_OS.h"
#include "calc\calc.h"
#include "config.h"
#include "calc\PID.h"
#include "calc\FPS.h"
#include "calc\MAPS.h"
#include "calc\ATUNE.h"
#include "motor.h"
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

//TUNER.cpp
int tune(double tolerance);

//port 3&4&10&11 ded
extern ACCESS_OS os;
// extern IMU imu;
// extern PID pid;
// extern BASE_DRIVE base;
// extern MECH_DRIVE mech;
extern ROBOT robot;