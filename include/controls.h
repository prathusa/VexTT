#ifndef CONTROLS_H
#define CONTROLS_H

#include "vex.h" 
#include "play.h"
#include "manual.h"
#include "drivefunctions.h"
using namespace vex;

void controls()
{       
        //Arcade Control
        LeftFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
        LeftRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
	      RightFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;
	      RightRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;

        // -----------------------------Toggle Stacker Command
        if(Controller1.ButtonY.pressing() && lift.value(pct) < liftTilter)
        {
          Brain.Timer.reset();
          stack();
          Tilt.stop(brake);
          Controller1.Screen.clearLine(3);
          Controller1.Screen.setCursor(3, 1);
          Controller1.Screen.print("%d ", Brain.Timer.time()); 
        }

        //------------------------------DriveSpeed Control
        if(Controller1.ButtonB.pressing())
        {
            driveSpeedFactor = 1.5; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Slow Mode");
            Controller1.rumble("-");
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Full Speed");
            Controller1.rumble(".");
        }
        
        // -----------------------------Intake Control
        if(Controller1.ButtonL1.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing() && lift.value(pct) < liftTower)
        {
            LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

        // -----------------------------Tilt Control
        if(Controller1.ButtonR2.pressing() && tilt.value(percentUnits::pct) < tiltMax)
        {
          double target = tiltStack; //In revolutions
          double error = target - tilt.value(percentUnits::pct);
          if(error > 0)
          {
            error = target - tilt.value(percentUnits::pct);
            double volts = .1*error+2;
            Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
            vex::task::sleep(20);
          }
          else
          {
            error = 0;
            double volts = error+2;
            Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
          }
        }
        else if(Controller1.ButtonR1.pressing() && tilt.value(percentUnits::pct) > tiltMin)
        {
          double target = tiltMax; //In revolutions
          double error = target - tilt.value(percentUnits::pct);
          if(error > 0)
          {
            error = target - tilt.value(percentUnits::pct);
            double volts = .1*error+2;
            Tilt.spin(directionType::rev, volts, voltageUnits::volt);
            vex::task::sleep(20);
          }
          else
          {
            error = 0;
            double volts = error+2;
            Tilt.spin(directionType::rev, volts, voltageUnits::volt);
          }
        }
        else
        {
          Tilt.stop(brake);
        }

        //Fade away
        if(Controller1.ButtonX.pressing()){
          fadeAway();
        }
        
        // -----------------------------Lift Control
        if(Controller1.ButtonUp.pressing())
        {
            Lift.spin(directionType::fwd, 100, velocityUnits::pct);
            liftTiltCheck();
        }
        else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
        {
            Lift.spin(directionType::rev, 100, velocityUnits::pct);
            liftTiltCheck();
        }
        // -----------------------------Toggle Lift Positions
        else if(Controller1.ButtonLeft.pressing())
        {
          liftTo(liftTower);
        }
        else if(Controller1.ButtonA.pressing())
        {
          liftTo(liftMin);
        }
        else 
        {
            Lift.setBrake(hold); //potentially make a custom hold function for the lift using potentiometer
            Lift.stop();
        }
        
      // -----------------------------Flip Out
      if(Controller1.ButtonRight.pressing())
      {
        Brain.Timer.reset();
        flipOut();
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("%d ", Brain.Timer.time());  
      }
}
#endif