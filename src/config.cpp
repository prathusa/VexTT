#include "main.h"

vex::brain Brain;
// vex::motor Lift(vex::PORT5, vex::gearSetting::ratio36_1, true);
// vex::motor Tilt(vex::PORT6, vex::gearSetting::ratio36_1, true);
vex::motor LeftIntake (vex::PORT9, vex::gearSetting::ratio18_1, true);
vex::motor RightIntake (vex::PORT2, vex::gearSetting::ratio18_1, false);
vex::motor RightRearMotor (vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor RightFrontMotor (vex::PORT19, vex::gearSetting::ratio18_1, true);
vex::motor LeftFrontMotor (vex::PORT15, vex::gearSetting::ratio18_1, false);
vex::motor LeftRearMotor (vex::PORT11, vex::gearSetting::ratio18_1, false);
// vex::motor_group intake(LeftIntake, RightIntake);
vex::motor_group l(LeftFrontMotor, LeftRearMotor); // l stands for Left Side motor group
vex::motor_group r(RightFrontMotor, RightRearMotor); // r stands for Right Side motor group
vex::motor_group ld(LeftFrontMotor, RightRearMotor); // ld stands for Left Diagonal motor group
vex::motor_group rd(RightFrontMotor, LeftRearMotor); // rd stands for Right Diagonal motor group
vex::motor_group d(LeftFrontMotor, LeftRearMotor, RightFrontMotor, RightRearMotor);
vex::inertial Inertial(vex::PORT18);
// vex::gyro Gyro (Brain.ThreeWirePort.G);
vex::pot tilt(Brain.ThreeWirePort.G);
vex::pot lift(Brain.ThreeWirePort.F);
// vex::encoder le(Brain.ThreeWirePort.A); // Left Encoder
// vex::encoder re(Brain.ThreeWirePort.C); // Right Encoder
vex::encoder xe(Brain.ThreeWirePort.A); // X-axis Encoder
vex::encoder ye(Brain.ThreeWirePort.C); // Y-axis Encoder
vex::rotation xr(vex::PORT1); // X-axis Rotation Sensor
vex::rotation yr(vex::PORT2); // X-axis Rotation Sensor
vex::limit Test (Brain.ThreeWirePort.B); // Test Button
vex::limit Debug (Brain.ThreeWirePort.D); // Debug Button
vex::smartdrive sdt(l, r, Inertial, 12.56, 9, 10, distanceUnits::in);
vex::drivetrain dt(l, r);
vex::controller Controller1;
vex::competition Competition;
ACCESS_OS os;
ROBOT robot;

int liftMax = 41;
int liftTowerMid = 37;
int liftTowerLow = 30;
int liftMin = 11;
int tiltMax = 80;
int tiltStack = 70;
int tiltMin = 32; 
bool isStacking = false;
double driveSpeedFactor = 1;
double turnSpeedFactor = 1;
double tileInch = 23.6;
double trackWidth = 9; // inches
double wheelBase = 10; // inches
double baseDiagonal = 13.45; // inches