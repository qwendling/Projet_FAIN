#ifndef FONCTEUR_NEARESTPOINT_H
#define FONCTEUR_NEARESTPOINT_H

#include "Point.h"
#include <limits>

class foncteur_nearestPoint{
public:
  Point nearestPoint;
  int carre_distance;
  Point compare_Point;
  foncteur_nearestPoint() : carre_distance(std::numeric_limits<int>::max()){}
  foncteur_nearestPoint(const Point& p) : compare_Point(p),carre_distance(std::numeric_limits<int>::max()){}
  void operator()(const Point& p);
};



#endif
