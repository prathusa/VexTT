#include "vex.h"
using namespace std;

PID::PID(){};
IMU::IMU(){};
BASE_DRIVE::BASE_DRIVE(){};
MECH_DRIVE::MECH_DRIVE(){};
LIFTER::LIFTER(){};
TILTER::TILTER(){};
bot::ROBOT::ROBOT(){};

PID::PID(double iKP, double iKI, double iKD)
{
  kP = iKP;
  kI = iKI;
  kD = iKD;
};

PID IMU::pid = PID();
PID BASE_DRIVE::pid = PID();
PID MECH_DRIVE::pid = PID();
PID LIFTER::pid = PID();
PID TILTER::pid = PID();

//PID Presets

void IMU::setPrecise()
{
  pid.kP = 0.37;
  pid.kI = 0.16;
  pid.kD = 0.015;
}

void IMU::setFast()
{
  pid.kP = 0.37;
  pid.kI = 0.16;
  pid.kD = 0.015;
}

void BASE_DRIVE::setPrecise()
{
  pid.kP = 10;
  pid.kI = 1.5;
  pid.kD = .05;
}

void BASE_DRIVE::setIntake()
{
  pid.kP = 10;
  pid.kI = 1.5;
  pid.kD = .05;
}

void MECH_DRIVE::setMech()
{
  pid.kP = 10;
  pid.kI = 1.5;
  pid.kD = .05;
}

void LIFTER::setLift()
{
  pid.kP = 1.7;
  pid.kI = 0.04;
  pid.kD = 0;
}

void TILTER::setTilt()
{
  pid.kP = 1.7;
  pid.kI = 0.09;
  pid.kD = 0;
}

//slew control
int accel_step = 12;
int deccel_step = 12; // Probabily needs to be reduced 

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



void PID::setTarget(double iTarget) { target = iTarget; }

void PID::setPID(double p, double i, double d)
{
  kP = p;
  kI = i;
  kD = d;
}

double PID::calc(double target, double position) 
{
  this->target = target;
  this->position = position;

  error = target - position;
  // Proportional term
  Pout = kP * error;

  // Integral term
  integral += error * dT;
  Iout = kI * integral;

  // Derivative term
  derivative = (error - prevError)/dT; //-(position - prevPosition) / dT; // Subtracting from 0 rather than error helps prevent Derivative pid.kIck
  // if(abs(derivative) > abs(acceleration + prevDeriv) && prevDeriv != 0)
  //   derivative = acceleration + prevDeriv;
  Dout = kD * derivative;

  // Calculate total output
  output = Pout + Iout + Dout;

  // Restrict to max/min
  if (output > max)
    output = max;
  else if (output < min)
    output = min;

  double integralCap = 3.5;

  if (Iout > integralCap)
    Iout = integralCap;
  else if (Iout < -integralCap)
    Iout = -integralCap;
  // if (std::abs(error) < tolerance) 
  // {
  //   integral = 0;
  //   output = 0;
  // }

  // Save error to previous error
  acceleration = derivative - prevDeriv;
  prevDeriv = derivative;
  prevPosition = position;
  prevError = error;

  return output;
}

void IMU::To() 
{
  while (1) 
  {
    double volts = pid.calc(pid.target, Inertial.rotation());
    double angleTolerance = 1;
    if(std::abs(pid.error) < angleTolerance * abs(pid.derivative) * .09)
      pid.integral = 0;
    if(abs(pid.derivative) < 1 && std::abs(pid.error) < angleTolerance * 3) 
      goto kill;
    // volts = calc();
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    if(std::abs(pid.error) < angleTolerance && abs(pid.derivative) < 10)
    {
      kill:
      d.stop();
      this_thread::yield();
      break;
    }
    l.spin(fwd, volts, voltageUnits::volt);
    r.spin(fwd, -volts, voltageUnits::volt);
    this_thread::sleep_for(30);
  }
}

void IMU::For() 
{
  pid.position = Inertial.rotation(deg);
  pid.target += pid.position;
  To();
}

void IMU::To(double iTarget)
{
  pid.target = iTarget;
  To();
}

void IMU::For(double iTarget) 
{
  pid.target = iTarget;
  For();
}

void IMU::aTo() { thread async_pid = vex::thread(To); }

void IMU::aFor() { thread async_pid = vex::thread(For); }

void IMU::aTo(double iTarget) 
{
  pid.target = iTarget;
  aTo();
}

void IMU::aFor(double iTarget) 
{
  pid.target = iTarget;
  aFor();
}

void BASE_DRIVE::To() 
{
  double volts;
  int time = 0;
  int timeout = 60;
  while (1) 
  {
    volts = pid.calc(pid.target, d.position(rev));
    double tolerance = .03;
    if(std::abs(pid.error) < tolerance * abs(pid.derivative))
      pid.integral = 0;
    
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    {
      kill:
      d.stop();
      this_thread::yield();
      break;
    }
    if(abs(pid.derivative) < 0.01)
    {
      if(time >= timeout)
        goto kill;
      else
        time += 20;
    }
    d.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
}

void BASE_DRIVE::For() 
{
  double position = d.position(rev);
  pid.target += position;
  To();
}

void BASE_DRIVE::To(double iTarget) 
{
  pid.target = iTarget;
  To();
}

void BASE_DRIVE::For(double iTarget) 
{
  pid.target = iTarget;
  For();
}

void BASE_DRIVE::aTo() 
{
  thread async_pid = vex::thread(To);
}

void BASE_DRIVE::aFor() 
{
  thread async_pid = vex::thread(For);
}

void BASE_DRIVE::aTo(double iTarget) 
{
  pid.target = iTarget;
  aTo();
}

void BASE_DRIVE::aFor(double iTarget) 
{
  pid.target = iTarget;
  aFor();
}

void MECH_DRIVE::ToX() 
{
  int time = 0;
  while (1) 
  {
    double volts = pid.calc(pid.target, d.position(rev));
    if (volts == 0) 
    {
      d.stop();
      this_thread::yield();
      break;
    } 
    else if (abs(d.velocity(percentUnits::pct)) < 2 && pid.target > .5) // else if makes sure that the volts aren't 0
    {
      time += 15;
    } 
    else if (abs(d.velocity(percentUnits::pct)) < .1) 
    {
      time += 10;
    }
    if(time >= 40)
    {
      d.stop();
      this_thread::yield();
      break;
    }
    ld.spin(fwd, volts, volt);
    rd.spin(fwd, -volts, volt);
    this_thread::sleep_for(20);
  }
}

void MECH_DRIVE::ForX() 
{
  pid.target += pid.position;
  ToX();
}

void MECH_DRIVE::ToX(double iTarget) 
{
  pid.target = iTarget;
  ToX();
}

void MECH_DRIVE::ForX(double iTarget) 
{
  pid.target = iTarget;
  ForX();
}

void MECH_DRIVE::aToX() 
{
  thread async_pid = vex::thread(ToX);
}

void MECH_DRIVE::aForX() 
{
  thread async_pid = vex::thread(ForX);
}

void MECH_DRIVE::aToX(double iTarget) 
{
  pid.target = iTarget;
  aToX();
}

void MECH_DRIVE::aForX(double iTarget) 
{
  pid.target = iTarget;
  aForX();
}

void LIFTER::To()
{
  setLift();
  while(1)
  {
    double volts = pid.calc(pid.target, lift.value(pct));
    // double tolerance = .03;
    // if(std::abs(pid.error) < tolerance * abs(pid.derivative))
    //   pid.integral = 0;
    // if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    // {
    //   Lift.stop();
    //   this_thread::yield();
    //   break;
    // }
    Lift.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
}

void LIFTER::For()
{
  double position = lift.value(pct);
  pid.target += position;
  To();
}

void LIFTER::To(double iTarget)
{
  pid.target = iTarget;
  To();
}

void LIFTER::For(double iTarget)
{
  pid.target = iTarget;
  For();
}

void LIFTER::aTo()
{
  thread async_pid = vex::thread(To);
}

void LIFTER::aTo(double iTarget)
{
  pid.target = iTarget;
  aTo();
}

void LIFTER::aFor()
{
  thread async_pid = vex::thread(For);
}

void LIFTER::aFor(double iTarget)
{
  pid.target = iTarget;
  aFor();
}

void TILTER::To()
{
  setTilt();
  while(1)
  {
    double volts = pid.calc(pid.target, tilt.value(pct));
    double tolerance = .03;
    if(std::abs(pid.error) < tolerance * abs(pid.derivative))
      pid.integral = 0;
    if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    {
      Tilt.stop();
      this_thread::yield();
      break;
    }
    Tilt.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
}

void TILTER::For()
{
  double position = lift.value(pct);
  pid.target += position;
  To();
}

void TILTER::To(double iTarget)
{
  pid.target = iTarget;
  To();
}

void TILTER::For(double iTarget)
{
  pid.target = iTarget;
  For();
}

void TILTER::aTo()
{
  thread async_pid = vex::thread(To);
}

void TILTER::aTo(double iTarget)
{
  pid.target = iTarget;
  aTo();
}

void TILTER::aFor()
{
  thread async_pid = vex::thread(For);
}

void TILTER::aFor(double iTarget)
{
  pid.target = iTarget;
  aFor();
}

// -----------------------------PID Code template:

/*
void PID::To()
{
  while(1)
  {
    double volts = calc();
    if(volts == 0)
    {
      if(!)
        m.stop();
      else
        pid.mg.stop();
      this_thread::yield();
      break;
    }
    if(!)
      m.spin(fwd, volts, voltageUnits::volt);
    else
      pid.mg.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
}

void PID::For()
{
  if (pid.type_device == 0)
    position = m.position(rev);
  else if (pid.type_device == 1)
    position = pid.mg.position(rev);
  else if (pid.type_device == 2) 
  {
    if ((*(pot *)pid.pos_device).value(pct) == 0) // Avoid starting/ending the Pot at PCT 0 because it can cause issues
      position = 0; // with the operation of the Potentiometer since latency and over/under rotation of the pot can occur
    else
      position = (*(pot *)pid.pos_device).value(pct);
  } 
  else if (pid.type_device == 3)
    position = (*(encoder *)pid.pos_device).position(rev);
  else if (pid.type_device == 4)
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
*/