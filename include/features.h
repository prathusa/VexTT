#pragma once
#include "calc\calc.h"
#include <math.h>
#include <utility>
#include <iostream>

namespace feature // features
{
  struct Coordinate // coordinates
  {
    double x() const { return x_; }
    void x(double x) { x_ = std::move(x); }
    double y() const { return y_; }
    void y(double y) { y_ = std::move(y); }
    double z() const { return z_; }
    void z(double z) { x_ = std::move(z); }
    enum rotationType {DEG, RAD};
    double theta() const { return theta_; }
    double theta(rotationType rt) const 
    { 
      switch(rt)
      {
        case Coordinate::rotationType::DEG:
        return theta_/M_PI*180;
        case Coordinate::rotationType::RAD:
        return theta_; 
      }
    }
    void theta(double theta, rotationType rt) 
    { 
      if (rotationType::DEG == rt) theta_ = theta / 180 * M_PI; 
      else theta_ = theta;
    }
    Coordinate(double x, double y, double z, double theta, rotationType rt)
    {
      this->x(x);
      this->y(y);
      this->z(z);
      this->theta(theta, rt);
    }
    Coordinate() : Coordinate{0, 0, 0, 0, rotationType::RAD} {}
    Coordinate operator+(const Coordinate& other)
    {
      Coordinate result;
      result.x(this->x() + other.x());
      result.y(this->y() + other.y());
      result.z(this->z() + other.z());
      result.theta(this->theta() + other.theta(), rotationType::RAD);
      return result;
    }
    Coordinate operator-(const Coordinate& other)
    {
      Coordinate result;
      result.x(this->x() - other.x());
      result.y(this->y() - other.y());
      result.z(this->z() - other.z());
      result.theta(this->theta() - other.theta(), rotationType::RAD);
      return result;
    }
    Coordinate operator-()
    {
      Coordinate result;
      result.x(-this->x());
      result.y(-this->y());
      result.z(-this->z());
      result.theta(-this->theta(), rotationType::RAD);
      return result;
    }
    double magnitude() { return hypot(x(), y()); }
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate)
    {
        os 
        << "x: " << coordinate.x() 
        << ", y: " << coordinate.y() 
        << ", z: " << coordinate.z() 
        << ", theta_rad: " << coordinate.theta() 
        << ", theta_deg: " << coordinate.theta(feature::Coordinate::rotationType::DEG) 
        << ", magn: " << hypot(coordinate.x(), coordinate.y());
        return os;
    }
    private:
    double x_, y_, z_, theta_;
  }; 

  struct tuple
  {
    double x, y;
    tuple operator+(tuple const& other) const
    {
      return tuple{this->x-other.x, this->y-other.y};
    }
    tuple operator*(double const& scaler) const
    {
      return tuple{scaler*x, scaler*y};
    }
    // tuple operator*(tuple const& other) const
    // {
      
    // }
    // tuple& operator*=(tuple const& other);
  };

  struct segment
  {
    tuple a, b;
    // multiplication
    double dist() { return hypot(b.x - a.x, b.y - a.y); }
  };

};