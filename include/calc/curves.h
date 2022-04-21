#pragma once

#include "features.h"
#include <queue>

namespace curves
{

  class bezier
  {
    feature::tuple parameterization(double t, feature::tuple a, feature::tuple b)
    {
      return a*(1-t) + b*t;
    }

    feature::tuple quad(double t, feature::tuple a, feature::tuple b, feature::tuple c)
    {
      return parameterization(t, parameterization(t, a, b), parameterization(t, b, c));
    }

    feature::tuple cubic(double t, feature::tuple a, feature::tuple b, feature::tuple c, feature::tuple d)
    {
      return parameterization(t, quad_t(t, a, b, c), quad_t(t, b, c, d));
    }

  };

  class path
  {
    std::vector<feature::tuple> points;
    std::queue<curves::bezier> q;
  };

}