#include "main.h"

// ostream& operator<<(ostream& os, const feature::Coordinate& coordinate)
// {
//     os 
//     << "x: " << coordinate.x() 
//     << ", y: " << coordinate.y() 
//     << ", z: " << coordinate.z() 
//     << ", theta_rad: " << coordinate.theta() 
//     << ", theta_deg: " << coordinate.theta(feature::Coordinate::rotationType::DEG) 
//     << ", magn: " << hypot(coordinate.x(), coordinate.y());
//     return os;
// }


// feature::Coordinate::Coordinate(double x, double y, double z, double theta, rotationType rt)
// {
//   this->x = x;
//   this->y = y;
//   this->z = z;
//   this->magnitude = hypot(x, y);
//   if (rotationType::DEG == rt)
//   {
//     this->theta = theta / 180 * M_PI;
//   }
//   else
//   {
//     this->theta = theta;
//   }
// }