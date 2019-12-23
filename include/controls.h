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
        if(Controller1.ButtonY.pressing())
        {
          stack();
          Tilt.stop(brake);
        }

        // -----------------------------Tilter Overextension Warning
        if(t.value(percentUnits::pct) > tiltMax && !displayed)
        {
          Controller1.Screen.clearLine(2);
          Controller1.Screen.setCursor(2,1);
          Controller1.Screen.print("Tilter Overextended");
          displayed = true;
        }

        // -----------------------------Tilter Overextension Warning
        if(t.value(percentUnits::pct) < tiltMax && displayed)
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
            driveSpeedFactor = 3; //Makes robot slower
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
        else if(Controller1.ButtonDown.pressing())
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
        if(Controller1.ButtonR2.pressing() && t.value(percentUnits::pct) < tiltStack)
        {
          double target = tiltStack; //In revolutions
          double error = target - t.value(percentUnits::pct);
          if(error > 0)
          {
            error = target - t.value(percentUnits::pct);
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
        else if(Controller1.ButtonR1.pressing() && t.value(percentUnits::pct) > tiltMin)
        {
          double target = tiltMax; //In revolutions
          double error = target - t.value(percentUnits::pct);
          if(error > 0)
          {
            error = target - t.value(percentUnits::pct);
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
        if(Controller1.ButtonR1.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing() && Lift.position(rev) < 0.3)
        {
            LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonB.pressing())
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

        // -----------------------------Toggle Lift Positions
        if(Controller1.ButtonUp.pressing())
        {
          //liftTo(top position);
        }
        else 
        {
            Lift.setBrake(hold);
            Lift.stop();
        }
        
        //----------------------------Fade Away
        if(Controller1.ButtonX.pressing())
        {
          intake.spinFor(directionType::rev, -2, rotationUnits::rev, 100, velocityUnits::pct, false);
          d.spinFor(-.75, rotationUnits::rev, 100, velocityUnits::pct);
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
            mode = 1;
            Controller1.Screen.clearLine(3);
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 1");
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
      if(Controller1.ButtonY.pressing())
      {
        flipOut();
      }

      // -----------------------------Run Auton
      if(Controller1.ButtonX.pressing())
      {
        BM();
      }
      if(Controller1.ButtonUp.pressing())
      {
        RM();
      }

      // -----------------------------90 degree turns
      if(Controller1.ButtonRight.pressing())
      {
        turnFor(90);
      }
      else if(Controller1.ButtonLeft.pressing())
      {
        turnFor(-90);
      }
    }
}


        // ---------------------------Driver Control Modes
        /*
        if(tank)
        {
            //Tank Control
            LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct);
            RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
            RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
            LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct); 
        }
        else
        {
            
            //Arcade Control
            LeftFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
            LeftRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
	          RightFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;
	          RightRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/(driveSpeedFactor), velocityUnits::pct);//(Axis3-Axis4)/2;
        }
        
        // -----------------------------Controller Drive Mode Switch
        if(Controller1.ButtonLeft.pressing())
        {
          tank = true;
          Controller1.Screen.clearLine(2);
          Controller1.Screen.setCursor(2,1);
          Controller1.Screen.print("Tank Control");
        }
        else if(Controller1.ButtonRight.pressing())
        {
          tank = false;
          Controller1.Screen.clearLine(2);
          Controller1.Screen.setCursor(2,1);
          Controller1.Screen.print("Split-Arcade");
        }
        */

        // -----------------------------Robot Lock
        /*
        if(Controller1.ButtonY.pressing())
        {
          while(!Controller1.ButtonA.pressing() || !Controller1.ButtonB.pressing())
          {
            vex::task::sleep(20);
          }
        }
        */
        // -----------------------------Controller Screen Manipulation
        
        /**
        Prints the motor speed to the controller screen and notifies the driver if Aim Mode is on.
        **/
        /*    
        if(Controller1.ButtonLeft.pressing())
        {
            Controller1.Screen.clearLine(2);
            Controller1.Screen.clearLine(3);
            Controller1.Screen.setCursor(2,1);
            Controller1.Screen.print("Left Rev: ");
            Controller1.Screen.setCursor(2,11);
            Controller1.Screen.print(LeftFrontMotor.rotation(rotationUnits::rev));
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Right Rev: ");
            Controller1.Screen.setCursor(3,12);
            Controller1.Screen.print(RightFrontMotor.rotation(rotationUnits::rev));
        }
        
        if(Controller1.ButtonRight.pressing())
        {
            LeftFrontMotor.resetRotation();
            RightFrontMotor.resetRotation();
            Controller1.Screen.clearLine(2);
            Controller1.Screen.clearLine(3);
            Controller1.Screen.setCursor(2,1);
            Controller1.Screen.print("Left Rev: ");
            Controller1.Screen.setCursor(2,11);
            Controller1.Screen.print(LeftFrontMotor.rotation(rotationUnits::rev));
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Right Rev: ");
            Controller1.Screen.setCursor(3,12);
            Controller1.Screen.print(RightFrontMotor.rotation(rotationUnits::rev));
        }
        */
#endif