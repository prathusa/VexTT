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
vex::motor Lift (vex::PORT6, vex::gearSetting::ratio36_1,true);
vex::motor Tilt (vex::PORT5, vex::gearSetting::ratio36_1,false);
vex::motor LeftIntake (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor RightIntake (vex::PORT8, vex::gearSetting::ratio18_1,false);
vex::motor RightRearMotor (vex::PORT9, vex::gearSetting::ratio18_1,true);
vex::motor RightFrontMotor (vex::PORT10, vex::gearSetting::ratio18_1,true);
vex::motor LeftFrontMotor (vex::PORT1, vex::gearSetting::ratio18_1,false);
vex::motor LeftRearMotor (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::motor_group intake(LeftIntake, RightIntake);
vex::motor_group l(LeftFrontMotor, LeftRearMotor);
vex::motor_group r(RightFrontMotor, RightRearMotor);
vex::motor_group d(LeftFrontMotor, LeftRearMotor, RightFrontMotor, RightRearMotor);
vex::inertial Inertial(vex::PORT20);
vex::gyro Gyro (Brain.ThreeWirePort.G);
vex::pot t(Brain.ThreeWirePort.H);
vex::limit Test (Brain.ThreeWirePort.B);
vex::limit Debug (Brain.ThreeWirePort.D);
//vex::pwm_out LED(Brain.ThreeWirePort.E);
vex::smartdrive sdt(l, r, Gyro, 12.56, 16, 16, distanceUnits::in);
vex::drivetrain dt(l, r);
vex::controller Controller1;
vex::competition Competition;
//vex::encoder LeftTrack (Brain.ThreeWirePort.A);
//vex::encoder RightTrack (Brain.ThreeWirePort.C);

int mode = 0;
int tiltMax = 72;
int tiltStack = 63;
int tiltMin = 23; 
bool rojo = false;
bool azul = false;
bool slow = false;
bool test = false;
bool skills = false;
bool rm = false;
bool bm = false;
bool manual = false;
double driveSpeedFactor = 1;
double gyroLinearFactor = 47/90;
double leftAngle = -47;
double rightAngle = 47;
#endif