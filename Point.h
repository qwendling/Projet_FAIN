#ifndef POINT_H
#define POINT_H

class Point{
public:
  int x;
  int y;
  Point() : x(0),y(0){}
  Point(int _x,int _y) : x(_x),y(_y){}
  Point(const Point& p) : x(p.x),y(p.y){}
  bool operator==(const Point& p)const{return p.x==this->x && p.y == this->y;}
};

#endif
