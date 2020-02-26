#include "vex.h"

vex::brain Brain;
vex::motor Lift (vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor Tilt (vex::PORT10, vex::gearSetting::ratio36_1, false);
vex::motor LeftIntake (vex::PORT5, vex::gearSetting::ratio18_1, true);
vex::motor RightIntake (vex::PORT14, vex::gearSetting::ratio18_1, false);
vex::motor RightRearMotor (vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor RightFrontMotor (vex::PORT9, vex::gearSetting::ratio18_1, true);
vex::motor LeftFrontMotor (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor LeftRearMotor (vex::PORT12, vex::gearSetting::ratio18_1, false);
vex::motor_group intake(LeftIntake, RightIntake);
vex::motor_group l(LeftFrontMotor, LeftRearMotor);
vex::motor_group r(RightFrontMotor, RightRearMotor);
vex::motor_group ld(LeftFrontMotor, RightRearMotor);
vex::motor_group rd(RightFrontMotor, LeftRearMotor);
vex::motor_group d(LeftFrontMotor, LeftRearMotor, RightFrontMotor, RightRearMotor);
vex::inertial Inertial(vex::PORT2);
vex::gyro Gyro (Brain.ThreeWirePort.G);
vex::pot tilt(Brain.ThreeWirePort.F);
vex::pot lift(Brain.ThreeWirePort.H);
vex::limit Test (Brain.ThreeWirePort.B);
vex::limit Debug (Brain.ThreeWirePort.D);
vex::smartdrive sdt(l, r, Inertial, 12.56, 9, 10, distanceUnits::in);
vex::drivetrain dt(l, r);
vex::controller Controller1;
vex::competition Competition;
ACCESS_OS os;
bot::ROBOT robot;

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
double tileInch = 23.6;
double trackWidth = 9; // inches
double wheelBase = 10; // inches
double baseDiagonal = 13.45; // inches
int tempStatus = 0;