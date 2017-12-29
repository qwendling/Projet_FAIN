#ifndef ARETE_DISTANCE_H
#define ARETE_DISTANCE_H

#include "Point.h"
#include <limits>

class Arete_distance{
public:
  Point A;
  Point B;
  int carre_distance;
  Arete_distance() : carre_distance(std::numeric_limits<int>::max()){}
  Arete_distance(const Point& p1,const Point& p2) : A(p1),B(p2),carre_distance(std::numeric_limits<int>::max()){}
  void calcul_distance(const Point&);
  bool operator<(const Arete_distance& a);
};


#endif
