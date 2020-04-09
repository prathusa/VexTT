//Pratham Maps, the best mapping system in V5
#include "main.h"
using namespace std;

MAPS::MAPS(){};

void MAPS::frontTo(double x, double y)
{
  double dX = x - robot.fps.coordinates[0];
  double dY = y - robot.fps.coordinates[1];
  double magnitude = magn(dX, dY);
  double targetTheta = atan((dY)/(dX));
  double thetaDeg = (180 * (targetTheta)/M_PI);

  if(dX >= 0 && dY >= 0) // Quadrant 1
    thetaDeg = 90-thetaDeg;
  else if(dX < 0 && dY > 0) // Quadrant 2
    thetaDeg = -90-thetaDeg;
  else if(dX > 0 && dY < 0) // Quadrant 4
    thetaDeg = abs(thetaDeg) + 90;
  else //if(dX < 0 && dY < 0) // Quadrant 3
    thetaDeg = -abs(thetaDeg) - 90;
  
  cout 
  << "targetTheta: " << targetTheta << endl 
  << "thetaDeg: " << thetaDeg << endl 
  << "posX: " << robot.fps.coordinates[0] << endl 
  << "posY: " << robot.fps.coordinates[1] << endl 
  << "x: " << x << endl 
  << "y: " << y << endl 
  << "dX: " << dX << endl 
  << "dY: " << dY << endl 
  << "magnitude: " << robot.fps.magnitude << endl 
  << "dMagnitude: " << magnitude << endl << 
  endl; // Angle calculation debug data

  // robot.imu.To(thetaDeg);
  robot.base.pid.target = magnitude;
  robot.base.pidTheta.target = thetaDeg;
  robot.base.polarFor();
}

void MAPS::To(double x, double y)
{
  double dX = x - robot.fps.coordinates[0];
  double dY = y - robot.fps.coordinates[1];
  double magnitude = magn(dX, dY);
  double targetTheta = atan((dY)/(dX));
  double thetaDeg = (180 * (targetTheta)/M_PI);

  if(dX >= 0 && dY >= 0) // Quadrant 1
    thetaDeg = 90-thetaDeg;
  else if(dX < 0 && dY > 0) // Quadrant 2
    thetaDeg = -90-thetaDeg;
  else if(dX > 0 && dY < 0) // Quadrant 4
    thetaDeg = abs(thetaDeg) + 90;
  else //if(dX < 0 && dY < 0) // Quadrant 3
    thetaDeg = -abs(thetaDeg) - 90;
  
  cout << " targetTheta: " << targetTheta << endl << ", thetaDeg: " << thetaDeg << endl << ", posX: " << robot.fps.coordinates[0] << ", posY: " << robot.fps.coordinates[1] << endl << ", x: " << x << ", y: " << y << endl << ", dX: " << dX << ", dY: " << dY << endl << ", magnitude: " << robot.fps.magnitude << ", dMagnitude: " << magnitude << endl; // Angle calculation debug
  robot.imu.To(thetaDeg);
  robot.base.For(magnitude, thetaDeg);
}

// More methods to be added with new algorithms