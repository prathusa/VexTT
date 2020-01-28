//Drive system class
#ifndef ROBOT_C
#define ROBOT_C
#include "robot-base.cpp"
#endif
//ACCESS_OS file
#ifndef ACCESS_OS_C
#define ACCESS_OS_C
#include "ACCESS_OS.cpp"
#endif
//VEX
#ifndef VEX_H
#define VEX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include "v5_vcs.h"
#include <iostream>
#include <fstream>

using namespace vex;
vex::brain Brain;
vex::motor Lift (vex::PORT16, vex::gearSetting::ratio36_1,true);
vex::motor Tilt (vex::PORT5, vex::gearSetting::ratio36_1,false);
vex::motor LeftIntake (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor RightIntake (vex::PORT4, vex::gearSetting::ratio18_1,false);
vex::motor RightRearMotor (vex::PORT6, vex::gearSetting::ratio18_1,true);
vex::motor RightFrontMotor (vex::PORT7, vex::gearSetting::ratio18_1,true);
vex::motor LeftFrontMotor (vex::PORT1, vex::gearSetting::ratio18_1,false);
vex::motor LeftRearMotor (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::motor_group intake(LeftIntake, RightIntake);
vex::motor_group l(LeftFrontMotor, LeftRearMotor);
vex::motor_group r(RightFrontMotor, RightRearMotor);
vex::motor_group d(LeftFrontMotor, LeftRearMotor, RightFrontMotor, RightRearMotor);
vex::inertial Inertial(vex::PORT17);
vex::gyro Gyro (Brain.ThreeWirePort.G);
vex::pot tilt(Brain.ThreeWirePort.H);
vex::pot lift(Brain.ThreeWirePort.F);
vex::limit Test (Brain.ThreeWirePort.B);
vex::limit Debug (Brain.ThreeWirePort.D);
vex::smartdrive sdt(l, r, Inertial, 12.56, 16, 16, distanceUnits::in);
vex::drivetrain dt(l, r);
vex::controller Controller1;
vex::competition Competition;

int liftMax = 55;
int liftTowerMid = 59;
int liftTowerLow = 35;
int liftTilter = 31;
int liftMin = 23;
int tiltMax = 76;
int tiltStack = 59;
int tiltMin = 25; 
bool rojo = false;
bool azul = false;
bool slow = false;
bool test = false;
bool skills = false;
bool rm = false;
bool bm = false;
bool manual = false;
double driveSpeedFactor = 1;
double tileInch = 23.6;
int tempStatus = 0;
#endif