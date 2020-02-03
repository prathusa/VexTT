#ifndef CONTROLS_H
#define CONTROLS_H

#include "vex.h" 
//#include "play.h"
//#include "manual.h"
//#include "drivefunctions.h"
using namespace vex;

void controls()
{       
        //Arcade Control
        LeftFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
        LeftRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
	      RightFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;
	      RightRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;
/*
        //Tank Control
        LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct); 
 */     
        //------------------------------DriveSpeed Control
        if(Controller1.ButtonB.pressing())
        {
            driveSpeedFactor = 2; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Slow Mode");
            Controller1.rumble("-");
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1; 
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Full Speed");
            Controller1.rumble(".");
        }
        
        // -----------------------------Intake Control 
        if(Controller1.ButtonL1.pressing())
        {
            intake.spin(directionType::fwd, 50, pct);
        }
        else if(Controller1.ButtonL2.pressing() && lift.value(pct) < liftTowerMid)
        {
            intake.spin(directionType::rev, 80, pct);
        }
        else
        {
          LeftIntake.stop(brakeType::hold);
          RightIntake.stop(brakeType::hold);
        }

        // -----------------------------Tilt Control
        if(Controller1.ButtonR2.pressing() && tilt.value(percentUnits::pct) < tiltMax && lift.value(pct) < liftTowerLow)
        {
          double target = tiltStack; //In revolutions
          double error = target - tilt.value(percentUnits::pct);
          if(error > 0)
          {
            error = target - tilt.value(percentUnits::pct);
            double volts = .4*error+2.5;
            Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
            vex::task::sleep(20);
          }
          else
          {
            error = 0;
            double volts = error+2.5;
            Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
          }
        }
        else if(Controller1.ButtonR1.pressing() && tilt.value(percentUnits::pct) > tiltMin && lift.value(pct) < liftTowerLow)
        {
          double target = tiltMax; //In revolutions
          double error = target - tilt.value(percentUnits::pct);
          if(error > 0)
          {
            error = target - tilt.value(percentUnits::pct);
            double volts = .4*error+2.5;
            Tilt.spin(directionType::rev, volts, voltageUnits::volt);
            vex::task::sleep(20);
          }
          else
          {
            error = 0;
            double volts = error+2.5;
            Tilt.spin(directionType::rev, volts, voltageUnits::volt);
          }
        }
        else
        {
          Tilt.stop(brake);
        }
}
#endif