#ifndef USERCONTROL_H
#define USERCONTROL_H

#include "vex.h"
#include "controls.h"
#include "autonomous.h"

void usercontrol(void) 
{
    while(1) 
    {
        controls();
        
        //Press Y to run autonomus
        /*
        if(Controller1.ButtonY.pressing())
        {
          autonomous();
        }
        */
    }
}

#endif