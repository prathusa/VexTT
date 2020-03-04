#include "vex.h"
using namespace std;

BASE_DRIVE::BASE_DRIVE(){};
IMU::IMU(){};
MECH_DRIVE::MECH_DRIVE(){};
LIFTER::LIFTER(){};
TILTER::TILTER(){};
bot::ROBOT::ROBOT(){};
PID::PID(){};

PID::PID(double iKP, double iKI, double iKD)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
};

// Added Controller and Brain feedback when autonomous is selected.
void autonController() 
{
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  if (rojo) 
  {
    Controller1.Screen.print("RED");
  }

  if (azul) 
  {
    Controller1.Screen.print("BLUE");
  }

  if (skills) 
  {
    Controller1.Screen.print(" SK");
  }

  if (slow) 
  {
    Controller1.Screen.print(" SLOW");
  }

  if (test) 
  {
    Controller1.Screen.print(" TEST");
  }
}

void autonBrain() 
{
  int row = 1;
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(fontType::mono60);
  Brain.Screen.setCursor(1, row);

  if (rojo) 
  {
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("RED");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (azul) 
  {
    Brain.Screen.setFillColor(blue);
    Brain.Screen.print("BLUE");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (skills) 
  {
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.print("SKILLS");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (slow) 
  {
    Brain.Screen.setFillColor(orange);
    Brain.Screen.print("SLOW MODE");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (test) 
  {
    Brain.Screen.setFillColor(purple);
    Brain.Screen.print("TEST MODE");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }
}

//slew control
int accel_step = 12;
int deccel_step = 12; // Probabiliy needs to be reduced 

int slew(int target, double iMotor)
{
  int step;
  int returnSpeed;

  if(std::abs(iMotor) < abs(target))
    step = accel_step;
  else
    step = deccel_step;

  if(target > iMotor + step)
    returnSpeed = iMotor + step;
  else if(target < iMotor - step)
    returnSpeed = iMotor - step;
  else
    returnSpeed = target;

  return returnSpeed;
}

double calc_turn_angle(double angle)
{
  return baseDiagonal * angle * M_PI / 360;
}

  double PID::dT = .02;
  double PID::kP = 0;
  double PID::kI = 0;
  double PID::kD = 0;
  double PID::target = 0;
  double PID::error = 0;
  double PID::max = 12;
  double PID::min = -12;
  vex::motor PID::m = vex::motor(vex::PORT1);
  vex::motor_group PID::mg;
  vex::inertial PID::imu = vex::inertial(PORT10);
  void *PID::pos_device;
  int PID::type_device = 0; 
  //                     0 is Motor
  //                     1 is Motor_group
  //                     2 is Pot 
  //                     3 is Encoder
  double PID::position = 0;
  double PID::Pout = 0;
  double PID::integral = 0;
  double PID::Iout = 0;
  double PID::derivative = 0;
  double PID::Dout = 0;
  double PID::output = 0;
  double PID::prevError = 0;
  double PID::tolerance = 0.02;
  bool PID::motorGroup = false;
  bool PID::complete = false;

void PID::setTarget(double iTarget)
{
  target = iTarget;
}

void PID::setPID(double p, double i, double d)
{
  kP = p;
  kI = i;
  kD = d;
}

void PID::setParam(vex::motor iM)
{
  m = iM;
  motorGroup = false;
}

void PID::setParam(vex::motor_group iMG)
{
  mg = iMG;
  motorGroup = true;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor iM)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  m = iM;
  type_device = 0;
  motorGroup = false;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor_group iMG)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  mg = iMG;
  type_device = 1;
  motorGroup = true;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor iM, vex::pot iP)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  pos_device = &iP;
  m = iM;
  type_device = 2;
  motorGroup = false;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor_group iMG, vex::pot iP)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  pos_device = &iP;
  mg = iMG;
  type_device = 2;
  motorGroup = true;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor iM, vex::encoder iE)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  pos_device = &iE;
  m = iM;
  type_device = 3;
  motorGroup = false;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor_group iMG, vex::encoder iE)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  pos_device = &iE;
  mg = iMG;
  type_device = 3;
  motorGroup = true;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor iM, vex::inertial iIMU)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  imu = iIMU;
  m = iM;
  type_device = 4;
  motorGroup = false;
}

void PID::setParam(double iKP, double iKI, double iKD, vex::motor_group iMG, vex::inertial iIMU)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
  imu = iIMU;
  mg = iMG;
  type_device = 4;
  motorGroup = true;
}

double PID::calc()
{
  // Calculate error
  if(type_device == 0)
    position = m.position(rev);
  else if(type_device == 1)
    position = mg.position(rev);
  else if(type_device == 2)
    position = (*(pot *) pos_device).value(pct);
  else if(type_device == 3)
    position = (*(encoder *) pos_device).position(rev);
  else if(type_device == 4)
    position = imu.rotation(deg);

    error = target - position;

    // Proportional term
    Pout = kP * error;

    // Integral term
    integral += error * dT;
    Iout = kI * integral;

    // Derivative term
    derivative = (error - prevError) / dT;
    Dout = kD * derivative;

    // Calculate total output
    output = Pout + Iout + Dout;

    // Restrict to max/min
    if(output > max)
        output = max;
    else if(output < min)
        output = min;
    
    double integralCap = 6;

    if(Iout > integralCap)
        Iout = integralCap;
    else if (Iout < -integralCap)
        Iout = -integralCap;
    if(std::abs(error) < tolerance)
    {
      integral = 0;
      output = 0;
    }

    // Save error to previous error
    prevError = error;
    
    return output;
}

double PID::calc(double iTarget)
{
  target = iTarget;
  return calc();
}

double PID::calc(double iTarget, motor iM)
{
  target = iTarget;
  m = iM;
  type_device = 0;
  return calc();
}

double PID::calc(double iTarget, motor_group iMG)
{
  target = iTarget;
  mg = iMG;
  type_device = 1;
  return calc();
}

double PID::calc(double iTarget, pot iP)
{
  target = iTarget;
  pos_device = &iP;
  type_device = 2;
  return calc();
}

double PID::calc(double iTarget, encoder iE)
{
  target = iTarget;
  pos_device = &iE;
  type_device = 3;
  return calc();
}

double PID::calc(double iTarget, inertial iIMU)
{
  target = iTarget;
  imu = iIMU;
  type_device = 4;
  return calc();
}

void PID::To()
{
  while(1)
  {
    double volts = calc();
    if(volts == 0)
    {
      if(!motorGroup)
        m.stop();
      else
        mg.stop();
      this_thread::yield();
      break;
    }
    if(!motorGroup)
      m.spin(fwd, volts, voltageUnits::volt);
    else
      mg.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
}

void PID::For()
{
  if(type_device == 0)
    position = m.position(rev);
  else if(type_device == 1)
    position = mg.position(rev);
  else if(type_device == 2)
    position = (*(pot *) pos_device).value(pct);
  else if(type_device == 3)
    position = (*(encoder *) pos_device).position(rev);
  else if(type_device == 4)
    position = imu.rotation(deg);
  
  target += position;
  To();
}

void PID::To(double iTarget)
{
  target = iTarget;
  To();
}

void PID::For(double iTarget)
{
  target = iTarget;
  For();
}

void PID::aTo()
{
  thread async_pid = vex::thread(To);
}

void PID::aFor()
{
  thread async_pid = vex::thread(For);
}

void PID::aTo(double iTarget)
{
  target = iTarget;
  aTo();
}

void PID::aFor(double iTarget)
{
  target = iTarget;
  aFor();
}

//PID Presets

void PID::setEncDR()
{
  kP = 12;
  kI = 16;
  kD = 0.8;
  mg = intake;
  motorGroup = true;
  type_device = 0;
  tolerance = 0;
}

void PID::setPotDR()
{
  kP = .3;
  kI = .3;
  kD = 0;
  mg = intake;
  motorGroup = true;
  pos_device = &lift;
  type_device = 2;
  tolerance = 0;
}

void PID::setLift()
{
  kP = .3;
  kI = .3;
  kD = 0;
  m = Lift;
  motorGroup = false;
  pos_device = &lift;
  type_device = 2;
  tolerance = 0;
}

void PID::setTilt()
{
  kP = .3;
  kI = .3;
  kD = 0;
  m = Tilt;
  motorGroup = false;
  pos_device = &tilt;
  type_device = 2;
}

void PID::setBase()
{
  kP = 6;
  kI = 8;
  kD = 1;
  mg = d;
  motorGroup = true;
  type_device = 1;
}

void PID::setMech()
{
  kP = .3;
  kI = .3;
  kD = 0;
  m = Tilt;
  motorGroup = false;
  pos_device = &tilt;
  type_device = 2;
}