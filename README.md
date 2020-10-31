# Pratham
Code for 8995E- Ellegal made by Pratham


This code contains some incomplete files and some garbage files since the work on it was canceled so abruptly due to COVID but the holonomic drive and regular base drive should be mostly complete.

- It contains a really smart and elegant (at least I think so) way of implementing PID control through the use of a PID class.
- At the bottom of PID.cpp there is a comprehensive explanation and an example use case of the PID class.
- The PID class is constructed into an object that does all of the calculations needed to run PID so there is no need for copying and pasting PID calculation code.
- Then the motor classes contain methods that provide public access to the motor running at the calculated velocity. 
- Inspiration for Field Positioning System (FPS) came from 7K's odometry code. 
- Holonomic drive should be able to drive to any coordinate in the XY plane in a straight line.
- PID controlled turning allows for very precise turns using the data from the inertial sensor.
