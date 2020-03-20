//Pratham Maps, the best mapping system in V5
#include "main.h"
using namespace std;

MAPS::MAPS(){};

void MAPS::To(double x, double y)
{
  double travelX = x - robot.fps.coordinates[0];
  double travelY = y - robot.fps.coordinates[1];
  double targetTheta = atan((travelY)/(travelX));
  robot.imu.setPrecise();
  double thetaDeg = (180 * (targetTheta)/M_PI);

  if(travelX >= 0 && travelY >= 0)
    thetaDeg = 90-thetaDeg;
  else if(travelX < 0 && travelY > 0)
    thetaDeg = -90-thetaDeg;
  else if(travelX > 0 && travelY < 0)
    thetaDeg = abs(thetaDeg) + 90;
  else //if(travelX < 0 && travelY < 0)
    thetaDeg = -abs(thetaDeg) - 90;
  // cout << targetTheta << " " << thetaDeg << endl; // Angle calculation debug
  robot.imu.To(thetaDeg);
  robot.base.To(y, thetaDeg);
}

// More methods to be added with new algorithms