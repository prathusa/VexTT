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
            driveSpeedFactor = 2.5; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced");
            Controller1.rumble(".-");
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1; //Resets the drive speed to normal
            Controller1.Screen.clearLine(1);
            Controller1.rumble("..");
        }

        // -----------------------------Avoids Lift - Tilter conflict
        if(Lift.position(rotationUnits::rev) > 0 && Tilt.position(rotationUnits::rev) < .7)
        {
            Tilt.spinFor(directionType::fwd, .7 - Tilt.position(rotationUnits::rev), rotationUnits::rev, 100, velocityUnits::pct);
        }
        else if(Lift.position(rotationUnits::rev) < 0)
        {
            Tilt.spinTo(0, rotationUnits::rev, 70, velocityUnits::pct);
        }
        
    if(mode == 0)
    {
        // -----------------------------Intake Control
        if(Controller1.ButtonL2.pressing())
        {
            LeftIntake.spin(directionType::fwd, 40, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 40, velocityUnits::pct);
        }
        else if(Controller1.ButtonL1.pressing())
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
        }
        else if(Controller1.ButtonDown.pressing())
        {
            Lift.spin(directionType::rev, 70, velocityUnits::pct);
        }
        else
        {
          Lift.setBrake(hold);
          Lift.stop();
        }

        // -----------------------------Tilt Control
        if(Controller1.ButtonR2.pressing())
        {
          Tilt.spin(directionType::fwd, 30, percentUnits::pct);
        }
        else if(Controller1.ButtonR1.pressing())
        {
          Tilt.spin(directionType::rev, 30, percentUnits::pct);
        }
        else
        {
          Tilt.stop(brake);
        }

        // -----------------------------Flip Out
        if(Controller1.ButtonX.pressing())
        {
          flipOut();
        }

        // -----------------------------Code Test
        if(Controller1.ButtonY.pressing())
        {
          
        }
    }
    else if(mode == 1)
    {     
        // -----------------------------Rest Position
        if(Controller1.ButtonDown.pressing())
        {
            Lift.setBrake(coast);
            Lift.rotateTo(.4, rotationUnits::rev, 90, velocityUnits::pct);
            Lift.setBrake(brake);
            Tilt.rotateTo(0, rotationUnits::rev, 40, velocityUnits::pct);
        }

        // -----------------------------Toggle Intake In
        if(Controller1.ButtonR1.pressing())
        {
            LeftIntake.spin(directionType::rev, 100/driveSpeedFactor, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100/driveSpeedFactor, velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100/driveSpeedFactor, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100/driveSpeedFactor, velocityUnits::pct);
        }
        else
        {
            LeftIntake.stop(brakeType::brake);
            RightIntake.stop(brakeType::brake);
        }
        
        // -----------------------------Toggle Stacker Command
        if(Controller1.ButtonY.pressing())
        {
          while(!Controller1.ButtonDown.pressing())
          {
            intake.spin(directionType::rev, 15, velocityUnits::pct);
            Tilt.spinFor(1.3, rev, 60, velocityUnits::pct, true);
            drive(-.5, 40);
            Tilt.spinFor(-1.3, rev, 60, velocityUnits::pct, false);
            goto close;
          }
          close:
          vex::task::sleep(20);
        }
        else
        {
          Tilt.stop(brake);
        }

        // -----------------------------Toggle Lift Positions
        if(Controller1.ButtonL2.pressing())
        {
            Lift.rotateTo(.4, rotationUnits::rev, 90, velocityUnits::pct);
        }
        else if(Controller1.ButtonL1.pressing())
        {
            Lift.rotateTo(.8, rotationUnits::rev, 90, velocityUnits::pct);
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

        //----------------------------Fade Away
        if(Controller1.ButtonX.pressing())
        {
          intake.spinFor(directionType::rev, -1, rotationUnits::rev, 40, velocityUnits::pct, false);
          //d.spinFor(-1, rotationUnits::rev, 40, velocityUnits::pct);
          d.spinFor(-.5, rotationUnits::rev, 20, velocityUnits::pct);
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