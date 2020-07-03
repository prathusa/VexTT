//Field Positioning System
#include "main.h"
using namespace std;

FPS::FPS(){};
double FPS::theta = 2*M_PI*Inertial.rotation(rotationUnits::rev);
double FPS::prevPos[2] = {0, 0};
double FPS::dPos[2] = {0, 0};
double FPS::pos[2] = {0, 0};
double FPS::coordinates[2] = {0, 0};
double FPS::magnitude = 0;

// Robot Base Drivers

void FPS::twoMotorEnc() // 2 Parallel Motor Encoders
{
  while(1)
  {
    theta = 2*M_PI*Inertial.rotation(rotationUnits::rev);
    pos[0] = l.position(rotationUnits::rev);
    pos[1] = r.position(rotationUnits::rev);
    dPos[0] = pos[0] - prevPos[0];
    dPos[1] = pos[1] - prevPos[1];
    coordinates[0] += (dPos[0]+dPos[1])/2 * sin(theta);
    coordinates[1] += (dPos[0]+dPos[1])/2 * cos(theta);
    magnitude = magn(coordinates[0], coordinates[1]);
    prevPos[0] = l.position(rotationUnits::rev);
    prevPos[1] = r.position(rotationUnits::rev);
    this_thread::sleep_for(20);
  }
}

void FPS::twoParaShaftEnc() // 2 Parallel Shaft Encoders
{
  while(1)
  {
    theta = 2*M_PI*Inertial.rotation(rotationUnits::rev);
    pos[0] = l.position(rotationUnits::rev);
    pos[1] = r.position(rotationUnits::rev);
    dPos[0] = pos[0] - prevPos[0];
    dPos[1] = pos[1] - prevPos[1];
    coordinates[0] += (dPos[0]+dPos[1])/2 * sin(theta);
    coordinates[1] += (dPos[0]+dPos[1])/2 * cos(theta);
    magnitude = magn(coordinates[0], coordinates[1]);
    prevPos[0] = l.position(rotationUnits::rev);
    prevPos[1] = r.position(rotationUnits::rev);
    this_thread::sleep_for(20);
  }
}

void FPS::twoPerpShaftEnc() // 2 Perpendicular (Normal) Shaft Encoders
{
  while(1)
  {
    theta = 2*M_PI*Inertial.rotation(rotationUnits::rev);
    pos[0] = xe.position(rotationUnits::rev);
    pos[1] = ye.position(rotationUnits::rev);
    dPos[0] = pos[0] - prevPos[0];
    dPos[1] = pos[1] - prevPos[1];
    coordinates[0] += dPos[0] * cos(theta);
    coordinates[1] += dPos[1] * sin(theta);
    magnitude = magn(coordinates[0], coordinates[1]);
    prevPos[0] = xe.position(rotationUnits::rev);
    prevPos[1] = ye.position(rotationUnits::rev);
    this_thread::sleep_for(20);
  }
}

void FPS::setUpdate(int MODE)
{
  if(MODE == 0)
    thread updatePosition = thread(twoMotorEnc);
  else if(MODE == 1)
    thread updatePosition = thread(twoParaShaftEnc);
  else if(MODE == 2)
    thread updatePosition = thread(twoPerpShaftEnc);
}

void FPS::reset()
{
  coordinates[0] = 0;
  coordinates[1] = 0;
}

void FPS::printData(void)
{
  while(1)
  {
    std::cout << "Theta ";
    std::cout << theta << std::endl;
    // std::cout << "Left Position ";
    // std::cout << -dPos[0] << std::endl;
    // std::cout << "Right Position ";
    // std::cout << -dPos[1] << std::endl;
    std::cout << "IMU Rotation ";
    std::cout << Inertial.rotation() << std::endl;
    std::cout << "Heading ";
    std::cout << 180*atan(pos[1]/pos[0])/M_PI << std::endl;
    std::cout << "X Component ";
    std::cout << coordinates[0] << std::endl;
    std::cout << "Y Component ";
    std::cout << coordinates[1] << std::endl;
    std::cout << "Magnitude ";
    std::cout << magnitude << std::endl << endl;
    vex::this_thread::sleep_for(100);
  }
}

void FPS::print(void)
{
  thread position_print = thread(printData);
}