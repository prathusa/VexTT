#pragma once

class PID
{
  protected:
  static double kP;
  static double kI;
  static double kD;
  static double dT;
  static double max;
  static double min;
  static vex::motor m;
  static vex::motor_group mg;
  static vex::inertial imu;
  static void *pos_device;
  static int type_device;
  static bool motorGroup;
  static bool complete;
  // enum Units {rev, deg, pct};
  public:
  PID();
  PID(double kP, double kI, double kD);
  PID(double dt, double max, double min, double Kp, double Kd, double Ki);
  static double position;
  static double target;
  static double error;
  static double integral;
  static double derivative;
  static double prevError;
  static double Pout;
  static double Iout;
  static double Dout;
  static double output;
  static double tolerance;
  void setPID(double kP, double kI, double kD);
  void setTarget(double iTarget);
  void setParam(vex::motor iM);
  void setParam(vex::motor_group iMG);
  void setParam(double iKP, double iKI, double iKD, vex::motor iM);
  void setParam(double iKP, double iKI, double iKD, vex::motor_group iMG);
  void setParam(double iKP, double iKI, double iKD, vex::motor iM, vex::pot iP);
  void setParam(double iKP, double iKI, double iKD, vex::motor_group iMG, vex::pot iP);
  void setParam(double iKP, double iKI, double iKD, vex::motor iM, vex::encoder iE);
  void setParam(double iKP, double iKI, double iKD, vex::motor_group iMG, vex::encoder iE);
  void setParam(double iKP, double iKI, double iKD, vex::motor iM, vex::inertial iIMU);
  void setParam(double iKP, double iKI, double iKD, vex::motor_group iMG, vex::inertial iIMU);
  static double calc();
  static double calc(double iTarget);
  static double calc(double iTarget, vex::motor iM);
  static double calc(double iTarget, vex::motor_group iMG);
  static double calc(double iTarget, vex::pot iP);
  static double calc(double iTarget, vex::encoder iE);
  static double calc(double iTarget, vex::inertial iIMU);
  static void To();
  static void For();
  static void To(double iTarget);
  static void For(double iTarget);
  void aTo();
  void aFor();
  void aTo(double iTarget);
  void aFor(double iTarget);
};

class IMU : public PID
{
  private:
  public:
  IMU();
  static void setIMU();
  static void To();
  static void For();
  static void To(double iTarget);
  static void For(double iTarget);
  void aTo();
  void aFor();
  void aTo(double iTarget);
  void aFor(double iTarget);
};

class BASE_DRIVE : public PID
{
  private:
  public:
  BASE_DRIVE();
  static void setBase();
  static void To();
  static void For();
  static void To(double iTarget);
  static void For(double iTarget);
  void aTo();
  void aFor();
  void aTo(double iTarget);
  void aFor(double iTarget);
};


class MECH_DRIVE : public PID
{
  private:
  public:
  MECH_DRIVE();
  static void setMech();
  static void setBase();
  static void ToX();
  static void ForX();
  static void ToX(double iTarget);
  static void ForX(double iTarget);
  void aToX();
  void aForX();
  void aToX(double iTarget);
  void aForX(double iTarget);
};

class TILTER : public PID
{
  private:
  public:
  TILTER();
  void setTilt();
};

class LIFTER : public PID
{
  private:
  public:
  LIFTER();
  void setLift();
};

namespace bot
{
  class ROBOT
  {
    private:
    public:
    ROBOT();
    IMU imu;
    BASE_DRIVE base;
    MECH_DRIVE mech;
    TILTER tilter;
    LIFTER lifter;
  };
}

int slew(int target, double iMotor);