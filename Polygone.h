#ifndef LISTEPOINT_H
#define LISTEPOINT_H

#include "Image.h"
#include <list>

class Point{
public:
  int x;
  int y;
  Point() : x(0),y(0){}
  Point(int _x,int _y) : x(_x),y(_y){}
};

class Polygone{
public:
  std::list<Point> liste_points;
  Polygone() : liste_points(){}
  void add_point(int x,int y){
    liste_points.push_back(Point(x,y));
  }
  void draw(Image*,bool);

};

#endif
