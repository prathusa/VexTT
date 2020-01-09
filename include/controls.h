#ifndef CONTROLS_H
#define CONTROLS_H

#include "vex.h" 
#include "play.h"
#include "manual.h"
#include "drivefunctions.h"
using namespace vex;

bool displayed = false;
void controls()
{       
        //Arcade Control
        LeftFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
        LeftRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
	      RightFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;
	      RightRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;

        // -----------------------------Toggle Stacker Command
        if(Controller1.ButtonY.pressing() && lift.value(pct) < 32)
        {
          Brain.Timer.reset();
          stack();
          Tilt.stop(brake);
          Controller1.Screen.clearLine(3);
          Controller1.Screen.setCursor(3, 1);
          Controller1.Screen.print("%d ", Brain.Timer.time()); 
        }

        // -----------------------------Tilter Overextension Warning
        if(tilt.value(percentUnits::pct) > tiltMax && !displayed)
        {
          Controller1.Screen.clearLine(2);
          Controller1.Screen.setCursor(2,1);
          Controller1.Screen.print("Tilter Overextended");
          displayed = true;
        }

        // -----------------------------Tilter Overextension Warning
        if(tilt.value(percentUnits::pct) < tiltMax && displayed)
        {
          Controller1.Screen.clearLine(2);
          displayed = false;
        }
        
    if(mode == 0)
    {
        //------------------------------DriveSpeed Control
        if(Controller1.ButtonB.pressing())
        {
            driveSpeedFactor = 3; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced x3");
            Controller1.rumble("-");
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 2; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced x1.5");
            Controller1.rumble(".");
        }
        
        // -----------------------------Intake Control
        if(Controller1.ButtonL1.pressing())
        {
            LeftIntake.spin(directionType::fwd, 40, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 40, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing() && Lift.position(rev) < .3)
        {
            LeftIntake.spin(directionType::rev, 40, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 40, velocityUnits::pct);
        }
        else
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }
        
        // -----------------------------Lift Control
        if(Controller1.ButtonUp.pressing())
        {
            Lift.spin(directionType::fwd, 70, velocityUnits::pct);
            liftTiltCheck();
        }
        else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
        {
            Lift.spin(directionType::rev, 70, velocityUnits::pct);
            liftTiltCheck();
        }
        else
        {
          Lift.setBrake(hold);
          Lift.stop();
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
          /*
          double target = 1.8; //In revolutions
          if(Tilt.position(rev) < target)
          {
            double volts = 70 - Tilt.position(rev)*30;
            Tilt.spin(directionType::fwd, volts/10, voltageUnits::volt);
            vex::task::sleep(20);
          }
          else
          {
            double volts = 70 - target*30;
            Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
          }
          */
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
        // -----------------------------Robot Sensitivity Change && Mode Change
        /*
        if(Controller1.ButtonLeft.pressing())
        {
            mode = 0;
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 0");
            driveSpeedFactor = 3; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced x1.5");
            Controller1.rumble("...");
        }
        else */if(Controller1.ButtonLeft.pressing())
        {
            mode = 1;
            Controller1.Screen.clearLine(3);
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 1");
            driveSpeedFactor = 1; //Resets the drive speed to normal
            Controller1.Screen.clearLine(1);
            Controller1.rumble("---");
        }
    }
    else if(mode == 1)
    {     
        //------------------------------DriveSpeed Control
        if(Controller1.ButtonB.pressing())
        {
            driveSpeedFactor = 2; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced x2");
            Controller1.rumble("-");
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1; //Resets the drive speed to normal
            Controller1.Screen.clearLine(1);
            Controller1.rumble(".");
        }
        
        // -----------------------------Intake Control
        if(Controller1.ButtonL1.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing() && Lift.position(rev) < 0.3 && !Controller1.ButtonDown.pressing())
        {
            LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else //if(Controller1.ButtonB.pressing() || Controller1.ButtonA.pressing())
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

        // -----------------------------Toggle Lift Positions
        if(Controller1.ButtonUp.pressing())
        {
          liftTo(liftTower);
        }
        else if(Controller1.ButtonDown.pressing())
        {
          liftTo(liftMin);
        }
        else 
        {
            Lift.setBrake(hold); //potentially make a custom hold function for the lift using potentiometer
            Lift.stop();
        }
        
        //----------------------------Fade Away
        if(Controller1.ButtonX.pressing())
        {
          fadeAway();
        }

        // -----------------------------Robot Sensitivity Change && Mode Change
        if(Controller1.ButtonLeft.pressing())
        {
            mode = 0;
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 0");
            driveSpeedFactor = 3; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced x1.5");
            Controller1.rumble("...");
        }
        else if(Controller1.ButtonRight.pressing())
        {
            mode = 2;
            Controller1.Screen.clearLine(3);
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 2");
            driveSpeedFactor = 1; //Resets the drive speed to normal
            Controller1.Screen.clearLine(1);
            Controller1.rumble("---");
        }

        // -----------------------------Run Auton
        if(Controller1.ButtonDown.pressing() && Controller1.ButtonL2.pressing())
        {
          mode = 2;
          Controller1.Screen.clearLine(3);
          Controller1.Screen.setCursor(3,1);
          Controller1.Screen.print("Test Mode");
          driveSpeedFactor = 1; //Resets the drive speed to normal
          Controller1.Screen.clearLine(1);
          Controller1.rumble("-.-");
        }
    }
    if(mode == 2)
    {
      if(Controller1.ButtonB.pressing())
        {
            mode = 1;
            Controller1.Screen.clearLine(3);
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 1");
            driveSpeedFactor = 1; //Resets the drive speed to normal
            Controller1.Screen.clearLine(1);
            Controller1.rumble("---");
        }
      
      // -----------------------------Flip Out
      if(Controller1.ButtonX.pressing())
      {
        Brain.Timer.reset();
        flipOut();
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("%d ", Brain.Timer.time());  
      }

      // -----------------------------Robot Sensitivity Change && Mode Change
        
        else if(Controller1.ButtonLeft.pressing())
        {
            turnTo(90);
        }

      // -----------------------------90 degree turns
      /**
      if(Controller1.ButtonR1.pressing())
      {
        sdt.turnFor(80, rotationUnits::deg, 30, velocityUnits::pct);
      }
      else if(Controller1.ButtonL1.pressing())
      {
        sdt.turnFor(-80, rotationUnits::deg, 30, velocityUnits::pct);
      }
      // -----------------------------PID Drive
      if(Controller1.ButtonR2.pressing())
      {
        drive(3);
      }
      */
    }
}

void skillscontrol()
{       
        //Arcade Control
        LeftFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
        LeftRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
	      RightFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;
	      RightRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;

        // -----------------------------Toggle Stacker Command
        if(Controller1.ButtonY.pressing() && lift.value(pct) < 32)
        {
          Brain.Timer.reset();
          stack();
          Tilt.stop(brake);
          Controller1.Screen.clearLine(3);
          Controller1.Screen.setCursor(3, 1);
          Controller1.Screen.print("%d ", Brain.Timer.time()); 
        }

        //------------------------------DriveSpeed Control
        if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1.5; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced x3");
            Controller1.rumble("-");
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced x1.5");
            Controller1.rumble(".");
        }
        
        // -----------------------------Intake Control
        if(Controller1.ButtonL1.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing() && Lift.position(rev) < .3)
        {
            LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

          Tilt.stop(brake);
        //Fade away
        if(Controller1.ButtonX.pressing()){
          fadeAway();
        }
        
        // -----------------------------Toggle Lift Positions
        if(Controller1.ButtonUp.pressing())
        {
          liftTo(liftTower);
        }
        else if(Controller1.ButtonDown.pressing())
        {
          liftTo(liftMin);
        }
        else 
        {
            Lift.setBrake(hold); //potentially make a custom hold function for the lift using potentiometer
            Lift.stop();
        }
        
        // -----------------------------Robot Sensitivity Change && Mode Change
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