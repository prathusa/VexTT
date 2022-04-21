#pragma once

extern vex::brain Brain;
extern vex::motor Lift;
extern vex::motor Tilt;
extern vex::motor LeftIntake;
extern vex::motor RightIntake;
extern vex::motor RightRearMotor;
extern vex::motor RightFrontMotor;
extern vex::motor LeftFrontMotor;
extern vex::motor LeftRearMotor;
// extern vex::motor_group intake;
extern vex::motor_group l;
extern vex::motor_group r;
namespace mg
{
  extern vex::motor_group x;
  extern vex::motor_group y;
}
extern vex::motor_group ld;
extern vex::motor_group rd;
extern vex::motor_group d;
extern vex::inertial Inertial;
extern vex::gyro Gyro;
extern vex::pot tilt;
extern vex::pot lift;
extern vex::encoder le;
extern vex::encoder re;
extern vex::encoder xe;
extern vex::encoder ye;
extern vex::rotation xr;
extern vex::rotation yr;
extern vex::limit Test;
extern vex::limit Debug;
extern vex::smartdrive sdt;
extern vex::drivetrain dt;
extern vex::controller Controller1;
extern vex::competition Competition;

namespace config 
{
  enum SENSORS // each enum is a different base configuration
  {
    TWO_MOTOR_ENC, TWO_PARA_SHAFT_ENC, 
    TWO_PERP_SHAFT_ENC, ONE_MOTOR_ENC, 
    ONE_SHAFT_ENC, THREE_SHAFT_ENC, 
    TWO_PERP_ROT_SEN
  };
  enum MOTORS
  {
    BASE, H, HOLO, MECH
  };
}

extern double driveSpeedFactor;
extern double turnSpeedFactor;
extern double tileInch;
extern double trackWidth;
extern double wheelBase;
extern double baseDiagonal;