#pragma once

class IMU
{
  private:
  double kP = 0.45;    // 0.45
  double kI = 0.00006; // 0.00006
  double kD = 0.50;    // 0.45
  public:
  IMU();
  void resetPID();
  void setPID(double kP, double kI, double kD);
  void turnTo(double raw, int intakeSpeed, int timeout = 1, double tolerance = 0.1);
  void turnToHeading(double target, int timeout = 250);
  void turn(double raw, int intakeSpeed = 0, int timeout = 1, double marginOfError = 1.0);
  void turnFor(double raw, bool timeout = false, int time = 250);
  void turnTo(double degrees);
  void getPositionY();
};


class HOLD
{
  private:
  static double holder;
  static vex::encoder e_empty;
  static vex::pot p_empty;
  static vex::encoder *e;
  static vex::pot *p;
  static void set_e_pos();
  static void set_p_pos();
  public:
  HOLD(vex::encoder e);
  HOLD(vex::pot p);
  void update_e_pos();
  void update_p_pos();
  double get_holder();
};

class PID // : private HOLD
{
  private:
  static double kP;
  static double kI;
  static double kD;
  static double dT;
  static double max;
  static double min;
  static vex::motor m;
  static vex::motor_group mg;
  static vex::pot potA;
  static vex::pot potB;
  static vex::pot potC;
  static vex::pot potD;
  static vex::pot potE;
  static vex::pot potF;
  static vex::pot potG;
  static vex::pot potH;
  static vex::encoder encoderA;
  static vex::encoder encoderB;
  static vex::encoder encoderC;
  static vex::encoder encoderD;
  static vex::encoder encoderE;
  static vex::encoder encoderF;
  static vex::encoder encoderG;
  static vex::encoder encoderH;
  // static vex::pot p;
  static std::string threeWireDevice;
  static double target;
  static double error;
  static double integral;
  static double prevError;
  static bool motorGroup;
  static bool complete;
  
  static void update_position();
  // enum Units {rev, deg, pct};
  public:static double position;
  PID();
  PID(double kP, double kI, double kD);
  PID(double dt, double max, double min, double Kp, double Kd, double Ki);
  PID(vex::motor iM);
  PID(vex::motor_group iMG);
  PID(double iKP, double iKI, double iKD, vex::motor iM);
  PID(double iKP, double iKI, double iKD, vex::motor_group iMG);
  PID(double iKP, double iKI, double iKD, std::string iThreeWireDevice, vex::motor iM);
  PID(double iKP, double iKI, double iKD, std::string iThreeWireDevice, vex::motor_group iMG);
  void setPID(double kP, double kI, double kD);
  void setTarget(double iTarget);
  void setParam(double iTarget, vex::motor iM);
  void setParam(double iTarget, vex::motor_group iMG);
  static double calc();
  static void to();
  static void to(double iTarget);
  void async();
  void async(double iTarget);
  void setLift();
  void setPotDRLift();
  void setEncDRLift();
  void setTilt();
};

class BASE_DRIVE : public IMU
{
    private:
    double kP = 2;
    double kI = 0.0075;
    double kD = 6;
    double theta = 0;
    double thetaTolerance = 1;
    public:
    BASE_DRIVE();
    void resetPID();
    void setPID(double kP, double kI, double kD);
    void setTheta(double angle, double angleTolerance);
    void driveTo(double positionRev, int intakeSpeed = 0, int timeout = 50, double tolerance = 0.1);
    void driveFor(double positionRev, int driveSpeed = 50, int intakeSpeed = 0, int timeout = 50);
    void drive(double revolutions, int intakeSpeed = 0, int timeout = 50, double tolerance = 0.1);
};

class MECH_DRIVE : public BASE_DRIVE
{
  private:
  double kP = 2;
  double kI = 0.0095;
  double kD = 6;
  public:
  MECH_DRIVE();
  void setPID(double kP, double kI, double kD);
  void strafe(double revolutions, int intakeSpeed = 0, int timeout = 10, double tolerance = 0.1);
  void strafeTo(double revolutions, int intakeSpeed = 0, int timeout = 10, double tolerance = 0.1);
  void strafeFor(double revolutions, int driveSpeed, int intakeSpeed, int timeout) ;
};

namespace track
{
  class TRACKING
  {
    private:
    public:
    TRACKING();
    void driveTo();

  };
}

class TILTER
{
  private:
  public:
  TILTER();
  PID pid = PID();
  void tiltTo(int potentiometerPCT, double volts, bool slowDown = false);
  void tiltFor(int potentiometerPCT, double volts);
  void tiltTo(int potentiometerPCT);
  void tiltFor(int potentiometerPCT);
  void stack(int intakeSpeed = 0);
};


void liftTiltCheck();
void tiltIntakeCheck();

class LIFTER
{
  private:
  public:
  LIFTER();
  PID pid = PID();
  void liftTo(int potentiometerPCT, double volts);
  void liftFor(int potentiometerPCT, double volts);
  void liftTo(int potentiometerPCT);
  void liftFor(int potentiometerPCT);
  void towerLow(void);
  void towerMid(void);
};

namespace bot
{
  class ROBOT : public MECH_DRIVE, public LIFTER, public TILTER, public PID
  {
    private:
    public:
    ROBOT();
    IMU imu;
    PID pid;
    BASE_DRIVE base;
    MECH_DRIVE mech;
    TILTER tilter;
    LIFTER lifter;
    void fadeAway();
    void fadeAwayMid();
    void flipOut();
    bool allInstalled();
    bool driveInstalled();
    void resetEncoders(void);
  };
}

extern int accel_step;
extern int decel_step;

int leftSlew(int leftTarget);
int rightSlew(int rightTarget);
int slew(int target, double iMotor);

// Added Controller and Brain feedback when autonomous is selected.
void autonController();
void autonBrain();


/*
//-------------------------Method 1 (Guess and Check):

First of all, set all three constants (kP, kI, kD) to zero. This “disables
them”. Tune them one by one, rather than jumping straight in. Generally tune in
the order of Proportional, Derivative, Integral, that is, tune in the order of
kP, kD and finally kI. This entire process relies on making a prediction for the
constant (“trial”), and then adjusting it when it doesn’t go to plan (“error”).
//Scientific Method, isolate one independent variable and observe dependant
variables to It’s important to be prepared to stop your robot (both by disabling
it from your program or a switch, and by physically catching it if necessary),
as you’ll likely make a prediction that is far off an appropriate value. So long
as you’re ready, there typically isn’t too much harm in just experimenting.

1. Increase kP until the robot oscillates just slightly, once or twice.
  We’re interested in achieving a fast motion to the target here, but not too
violent – it needs to settle, and in a reasonable amount of time!
2.  Start adding kD until the steady-state error starts to decrease until
something suitable. This will allow us to maintain the fast motion from the
Proportional component, whilst minimising the overshoot. You may need to go back
to adjusting kP a little.
3. Start adding kI until any minor steady-state error and disturbances are
accounted for. You may need to adjust kD when doing this.
4. Using the knowledge from the table on the previous page, keep adjusting the
constants until you end up with a nice, quick but smooth motion that you’re
happy with.

//-------------------------Method 2 (Ziegler-Nichols Mathematical Model):

Begin by disabling all three constants (set them to zero).
1. Increase kP until you get steady continuous oscillations.
  These need to be stable and consistent. Record this value as “kU” (ultimate or
critical gain).
2. Measure the period of the oscillations caused by step 1.
  That is, the time it takes to do a full cycle from a point back to itself. You
can measure this with a bit of programming, or with a stopwatch. It’s a good
idea to measure many oscillations and then divide the time by the number of
oscillations to get a good average. Record this number as “pU” (period for
ultimate or critical gain).
3. Calculate the approximate constant values from the following table:

       kP        kI         kD
PID  0.6*kU  1.2*kU/pU  0.075*kU*pU

*/

// Makes the bot accelerate smoothly, leading to less jerk and more accurate
// movements. Possibly make the drive command use the gyro to make sure that the
// robot is not turning or not going in a straight line
