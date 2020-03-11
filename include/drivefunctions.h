#pragma once

class PID
{
  public:
  PID();
  PID(double kP, double kI, double kD);
  PID(double dt, double max, double min, double Kp, double Kd, double Ki);
  double kP = 0;
  double kI = 0;
  double kD = 0;
  double dT = .02;
  double max = 12;
  double min = -12;
  double position = 0;
  double target = 0;
  double error = 0;
  double integral = 0;
  double derivative = 0;
  double prevError = 0;
  double prevPosition = 0;
  double prevDeriv = 0;
  double acceleration = 0;
  double Pout = 0;
  double Iout = 0;
  double Dout = 0;
  double output = 0;
  void setPID(double kP, double kI, double kD);
  void setTarget(double iTarget);
  double calc(double target, double position);
};

class IMU //: public PID
{
  private:
  public:
  IMU();
  static PID pid;
  static void setPrecise();
  static void setFast();
  static void To();
  static void For();
  static void To(double iTarget);
  static void For(double iTarget);
  void aTo();
  void aFor();
  void aTo(double iTarget);
  void aFor(double iTarget);
};

class BASE_DRIVE //: public PID
{
  private:
  public:
  BASE_DRIVE();
  static PID pid;
  static void setPrecise();
  static void setIntake();
  static void To();
  static void For();
  static void To(double iTarget);
  static void For(double iTarget);
  void aTo();
  void aFor();
  void aTo(double iTarget);
  void aFor(double iTarget);
};


class MECH_DRIVE //: public PID
{
  private:
  public:
  MECH_DRIVE();
  static PID pid;
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

class TILTER //: public PID
{
  private:
  static void setTilt();
  public:
  TILTER();
  static PID pid;
  static void To();
  static void For();
  static void To(double iTarget);
  static void For(double iTarget);
  void aTo();
  void aFor();
  void aTo(double iTarget);
  void aFor(double iTarget);
};

class LIFTER //: public PID
{
  private:
  static void setLift();
  public:
  LIFTER();
  static PID pid;
  static void To();
  static void For();
  static void To(double iTarget);
  static void For(double iTarget);
  void aTo();
  void aFor();
  void aTo(double iTarget);
  void aFor(double iTarget);
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