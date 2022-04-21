//Field Positioning System
#include "main.h"
using namespace std;

FPS::FPS(){};
feature::Coordinate FPS::curr;
feature::Coordinate FPS::delta;
feature::Coordinate FPS::prev;
feature::Coordinate FPS::coordinates;

// Robot Base Drivers

void FPS::twoMotorEnc() // 2 Parallel Motor Encoders
{
  using feature::Coordinate;
  while(1)
  {
    curr.theta(2*M_PI*Inertial.rotation(rotationUnits::rev), Coordinate::rotationType::RAD);
    curr.y((l.position(rotationUnits::rev)+r.position(rotationUnits::rev))/2);
    delta = curr-prev;
    coordinates.theta(curr.theta(), Coordinate::rotationType::RAD);
    coordinates.x(coordinates.x() + delta.x() * sin(coordinates.theta()) + delta.y() * sin(coordinates.theta())); // Only delta y can be non zero since there is no delta x since there is no sensor measuring it
    coordinates.y(coordinates.y() + delta.x() * cos(coordinates.theta()) + delta.y() * cos(coordinates.theta()));
    prev = curr;
    this_thread::sleep_for(20);
  }
}

void FPS::twoParaShaftEnc() // 2 Parallel Shaft Encoders
{
  using feature::Coordinate;
  while(1)
  {
    curr.theta(2*M_PI*Inertial.rotation(rotationUnits::rev), Coordinate::rotationType::RAD);
    curr.y((l.position(rotationUnits::rev)+r.position(rotationUnits::rev))/2);
    delta = curr-prev;
    coordinates.theta(curr.theta(), Coordinate::rotationType::RAD);
    coordinates.x(coordinates.x() + delta.x() * sin(coordinates.theta()) + delta.y() * sin(coordinates.theta())); // Only delta y can be non zero since there is no delta x since there is no sensor measuring it
    coordinates.y(coordinates.y() + delta.x() * cos(coordinates.theta()) + delta.y() * cos(coordinates.theta()));
    prev = curr;
    this_thread::sleep_for(20);
  }
}

void FPS::twoPerpShaftEnc() // 2 Perpendicular (Normal) Shaft Encoders
{
  using feature::Coordinate;
  while(1)
  {
    curr.theta(2*M_PI*Inertial.rotation(rotationUnits::rev), Coordinate::rotationType::RAD);
    curr.x(xe.position(rotationUnits::rev));
    curr.y(ye.position(rotationUnits::rev));
    delta = curr-prev;
    coordinates.theta(curr.theta(), Coordinate::rotationType::RAD);
    coordinates.x(coordinates.x() + delta.x() * sin(coordinates.theta()) + delta.y() * sin(coordinates.theta()));
    coordinates.y(coordinates.y() + delta.x() * cos(coordinates.theta()) + delta.y() * cos(coordinates.theta()));
    prev = curr;
    this_thread::sleep_for(20);
  }
}

void FPS::twoPerpRotSen() // 2 Perpendicular (Normal) Rotation Sensor
{
  using feature::Coordinate;
  while(1)
  {
    curr.theta(2*M_PI*Inertial.rotation(rotationUnits::rev), Coordinate::rotationType::RAD);
    curr.x(xr.position(rotationUnits::rev));
    curr.y(yr.position(rotationUnits::rev));
    delta = curr-prev;
    coordinates.theta(curr.theta(), Coordinate::rotationType::RAD);
    coordinates.x(coordinates.x() + delta.x() * sin(coordinates.theta()) + delta.y() * sin(coordinates.theta()));
    coordinates.y(coordinates.y() + delta.x() * cos(coordinates.theta()) + delta.y() * cos(coordinates.theta()));
    prev = curr;
    this_thread::sleep_for(20);
  }
}

void FPS::setUpdate(config::SENSORS base_configuration)
{
  ROBOT::sensors = base_configuration;
  // start();
}

void FPS::start()
{
  if(ROBOT::sensors == config::SENSORS::TWO_MOTOR_ENC)
    main = vex::thread(twoMotorEnc);
  else if(ROBOT::sensors == config::SENSORS::TWO_PARA_SHAFT_ENC)
    main = vex::thread(twoParaShaftEnc);
  else if(ROBOT::sensors == config::SENSORS::TWO_PERP_ROT_SEN)
    main = vex::thread(twoPerpShaftEnc);
  else if(ROBOT::sensors == config::SENSORS::TWO_PERP_ROT_SEN)
    main = vex::thread(twoPerpRotSen);
}

void FPS::reset()
{
  coordinates = feature::Coordinate();
}

void FPS::printData(void)
{
  while(1)
  {
    std::cout << "Theta ";
    std::cout << coordinates.theta() << '\n';
    // std::cout << "Left Position ";
    // std::cout << -dPos[0] << std::endl;
    // std::cout << "Right Position ";
    // std::cout << -dPos[1] << std::endl;
    std::cout << "IMU Rotation ";
    std::cout << Inertial.rotation() << '\n';
    std::cout << "Heading ";
    std::cout << 180*atan2(curr.y(), curr.x())/M_PI << '\n';
    std::cout << "X Component ";
    std::cout << coordinates.x() << '\n';
    std::cout << "Y Component ";
    std::cout << coordinates.y() << '\n';
    std::cout << "Magnitude ";
    std::cout << coordinates.magnitude() << '\n' << endl;
    vex::this_thread::sleep_for(100);
  }
}

void FPS::print(void)
{
  thread position_print = thread(printData);
}