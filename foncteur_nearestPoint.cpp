#include "foncteur_nearestPoint.h"

void foncteur_nearestPoint::operator()(const Point& p){
  int distance = (p.x - compare_Point.x)*(p.x - compare_Point.x)+(p.y - compare_Point.y)*(p.y - compare_Point.y);
  if( distance<this->carre_distance){
    this->nearestPoint = Point(p.x,p.y);
    this->carre_distance = distance;
  }
}
