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

        // -----------------------------Robot Sensitivity Change && Mode Change
        if(Controller1.ButtonLeft.pressing())
        {
            mode = 0;
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 0");
            Controller1.rumble("...");
        }
        else if(Controller1.ButtonRight.pressing())
        {
            mode = 1;
            Controller1.Screen.clearLine(3);
            Controller1.Screen.setCursor(3,1);
            Controller1.Screen.print("Mode 1");
            Controller1.rumble("---");
        }

        //------------------------------DriveSpeed Control
        if(Controller1.ButtonB.pressing())
        {
            driveSpeedFactor = 2; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced");
            Controller1.rumble("--..");
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = .5; //Resets the drive speed to normal
            Controller1.Screen.clearLine(1);
            Controller1.rumble("..--");
        }

        // -----------------------------Toggle Stacker Command
        if(Controller1.ButtonY.pressing())
        {
          stack();
          Tilt.stop(brake);
        }
        
    if(mode == 0)
    {
        // -----------------------------Intake Control
        if(Controller1.ButtonR1.pressing())
        {
            LeftIntake.spin(directionType::fwd, 40, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 40, velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing() && Lift.position(rev) < 0)
        {
            LeftIntake.spin(directionType::rev, 127, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 127, velocityUnits::pct);
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
        if(Controller1.ButtonL2.pressing())
        {
          double target = 1.8; //In revolutions
          double error = target - Tilt.position(rev);
          if(error > 0)
          {
            error = target - Tilt.position(rev);
            double volts = 4*sqrt(error)+2;
            Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
            error = target - Tilt.position(rev);
            vex::task::sleep(20);
          }
          else
          {
            double volts = 4*sqrt(0)+2;
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
        else if(Controller1.ButtonL1.pressing())
        {
          double target = 1.8; //In revolutions
          double error = target - Tilt.position(rev);
          if(error > 0)
          {
            error = target - Tilt.position(rev);
            double volts = 4*sqrt(error)+2;
            Tilt.spin(directionType::rev, volts, voltageUnits::volt);
            error = target - Tilt.position(rev);
            vex::task::sleep(20);
          }
          else
          {
            double volts = 4*sqrt(0)+2;
            Tilt.spin(directionType::rev, volts, voltageUnits::volt);
          }
        }
        else
        {
          Tilt.stop(brake);
        }

        //----------------------------Fade Away
        if(Controller1.ButtonX.pressing())
        {
          intake.spinFor(directionType::rev, -2, rotationUnits::rev, 40, velocityUnits::pct, false);
          //d.spinFor(-1, rotationUnits::rev, 40, velocityUnits::pct);
          d.spinFor(-.5, rotationUnits::rev, 30, velocityUnits::pct);
        }
    }
    else if(mode == 1)
    {     
        // -----------------------------Intake Control
        if(Controller1.ButtonR1.pressing())
        {
            LeftIntake.spin(directionType::fwd, 40, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 40, velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing() && Lift.position(rev) < 0)
        {
            LeftIntake.spin(directionType::rev, 127, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 127, velocityUnits::pct);
        }
        else if(Controller1.ButtonB.pressing())
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

        // -----------------------------Toggle Lift Positions
        if(Controller1.ButtonL2.pressing())
        {
            liftTiltCheck();
            Lift.rotateTo(.6, rotationUnits::rev, 70, velocityUnits::pct);
            
        }
        else if(Controller1.ButtonL1.pressing())
        {
            liftTiltCheck();
            Lift.rotateTo(1.2, rotationUnits::rev, 70, velocityUnits::pct);
        }
        else if(Lift.position(rotationUnits::rev) < -.25)
        {
            Lift.setBrake(brake);
            Lift.stop();
        }
        else 
        {
            Lift.setBrake(hold);
            Lift.stop();
        }

        if(Controller1.ButtonX.pressing())
        {
          Lift.spinFor(.3, rev, 75, velocityUnits::pct);
    Lift.spinFor(-.5, rev, 75, velocityUnits::pct, false);
    //drive(-.1, 60, false, false, false);
    intake.spin(vex::forward, 100, pct);
    Tilt.spinFor(2, rev, 127, velocityUnits::pct);
    Tilt.spinFor(-2, rev, 127, velocityUnits::pct);
    Lift.spinFor(-.1, rev, 75, velocityUnits::pct, true);
    intake.stop();
        }
        // -----------------------------Flip Out
        if(Controller1.ButtonUp.pressing())
        {
          RM();
          //sdt.turnToHeading(0, rotationUnits::deg, 20, velocityUnits::pct);
        }
        if(Controller1.ButtonDown.pressing())
        {
          BM();
          //sdt.turnToHeading(0, rotationUnits::deg, 20, velocityUnits::pct);
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