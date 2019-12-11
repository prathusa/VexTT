#include "autonomous.h"
#include "usercontrol.h"
#include "GUI.h"

int main() 
{
    //Provides power to the LED lights.
    LED.state(100, percentUnits::pct);

    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) 
    {
      vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
    }
}