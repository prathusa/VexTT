//VEX_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include "v5_vcs.h"
#include <iostream>
#include <fstream>
#include "robot-config.h"
#include "usercontrol.h"
#include "record.h"
#include "controls.h"
#include "play.h"
#include "manual.h"
#include "drivefunctions.h"
#include "autonomous.h"
#include "gui.h"
#include "ACCESS_OS.h"
#include "robot-base.h"
extern ROBOT_BASE ROBOT;
extern ACCESS_OS OS;

//port 3&4 ded
extern vex::brain Brain;
extern vex::motor Lift;
extern vex::motor Tilt;
extern vex::motor LeftIntake;
extern vex::motor RightIntake;
extern vex::motor RightRearMotor;
extern vex::motor RightFrontMotor;
extern vex::motor LeftFrontMotor;
extern vex::motor LeftRearMotor;
extern vex::motor_group intake;
extern vex::motor_group f;
extern vex::motor_group b;
extern vex::motor_group l;
extern vex::motor_group r;
extern vex::motor_group d;
extern vex::inertial Inertial;
extern vex::gyro Gyro;
extern vex::pot tilt;
extern vex::pot lift;
extern vex::limit Test;
extern vex::limit Debug;
extern vex::smartdrive sdt;
extern vex::drivetrain dt;
extern vex::controller Controller1;
extern vex::competition Competition;

extern int liftMax;
extern int liftTowerMid;
extern int liftTowerLow;
extern int liftTilter;
extern int liftMin;
extern int tiltMax;
extern int tiltStack;
extern int tiltMin; 
extern bool rojo;
extern bool azul;
extern bool slow;
extern bool test;
extern bool skills;
extern bool rm;
extern bool bm;
extern bool manual;
extern bool isStacking;
extern double driveSpeedFactor;
extern double turnSpeedFactor;
extern double circumference;
extern double tileInch;
extern int tempStatus;