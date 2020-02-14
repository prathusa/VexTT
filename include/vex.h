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
//port 3&4 ded
vex::brain Brain;
vex::motor Lift (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor Tilt (vex::PORT10, vex::gearSetting::ratio36_1,false);
vex::motor LeftIntake (vex::PORT5, vex::gearSetting::ratio18_1,true);
vex::motor RightIntake (vex::PORT14, vex::gearSetting::ratio18_1,false);
vex::motor RightRearMotor (vex::PORT1, vex::gearSetting::ratio18_1,true);
vex::motor RightFrontMotor (vex::PORT6, vex::gearSetting::ratio18_1,true);
vex::motor LeftFrontMotor (vex::PORT8, vex::gearSetting::ratio18_1,false);
vex::motor LeftRearMotor (vex::PORT9, vex::gearSetting::ratio18_1,false);
vex::motor_group intake(LeftIntake, RightIntake);
vex::motor_group f(LeftFrontMotor, RightFrontMotor);
vex::motor_group b(LeftRearMotor, RightRearMotor);
vex::motor_group l(LeftFrontMotor, LeftRearMotor);
vex::motor_group r(RightFrontMotor, RightRearMotor);
vex::motor_group d(LeftFrontMotor, LeftRearMotor, RightFrontMotor, RightRearMotor);
vex::inertial Inertial(vex::PORT7);
vex::gyro Gyro (Brain.ThreeWirePort.G);
vex::pot tilt(Brain.ThreeWirePort.F);
vex::pot lift(Brain.ThreeWirePort.H);
vex::limit Test (Brain.ThreeWirePort.B);
vex::limit Debug (Brain.ThreeWirePort.D);
vex::smartdrive sdt(l, r, Inertial, 12.56, 16, 16, distanceUnits::in);
vex::drivetrain dt(l, r);
vex::controller Controller1;
vex::competition Competition;

int liftMax = 55;
int liftTowerMid = 58;
int liftTowerLow = 48;
int liftTilter = 31;
int liftMin = 23;
int tiltMax = 76;
int tiltStack = 55;
int tiltMin = 32; 
bool rojo = false;
bool azul = false;
bool slow = false;
bool test = false;
bool skills = false;
bool rm = false;
bool bm = false;
bool manual = false;
bool isStacking = false;
double driveSpeedFactor = 1;
double turnSpeedFactor = 1;
double circumference = 4;
double tileInch = 23.6;
int tempStatus = 0;
#endif
