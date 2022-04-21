//Pratham Maps, the best mapping system in V5
#include "main.h"
using namespace std;

MAPS::MAPS(){};

void MAPS::frontTo(double x, double y)
{
  double dX = x - robot.fps.coordinates.x();
  double dY = y - robot.fps.coordinates.y();
  double magnitude = hypot(dX, dY);
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
  << "posX: " << robot.fps.coordinates.x() << endl 
  << "posY: " << robot.fps.coordinates.y() << endl 
  << "x: " << x << endl 
  << "y: " << y << endl 
  << "dX: " << dX << endl 
  << "dY: " << dY << endl 
  << "magnitude: " << robot.fps.coordinates.magnitude() << endl 
  << "dMagnitude: " << magnitude << endl << 
  endl; // Angle calculation debug data

  // robot.imu.To(thetaDeg);
  robot.base.pid.target = magnitude;
  robot.base.pidTheta.target = thetaDeg;
  robot.base.polarFor();
}

void MAPS::To(double x, double y)
{
  double dX = x - robot.fps.coordinates.x();
  double dY = y - robot.fps.coordinates.y();
  double magnitude = hypot(dX, dY);
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
  
  cout << " targetTheta: " << targetTheta << endl << ", thetaDeg: " << thetaDeg << endl << ", posX: " << robot.fps.coordinates.x() << ", posY: " << robot.fps.coordinates.y() << endl << ", x: " << x << ", y: " << y << endl << ", dX: " << dX << ", dY: " << dY << endl << ", magnitude: " << robot.fps.coordinates.magnitude() << ", dMagnitude: " << magnitude << endl; // Angle calculation debug
  robot.imu.To(thetaDeg);
  robot.base.For(magnitude, thetaDeg);
}

// More methods to be added with new algorithms