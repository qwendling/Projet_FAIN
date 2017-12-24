#ifndef LISTEPOINT_H
#define LISTEPOINT_H

#include "Image.h"
#include <list>
#include <iterator>

/*typedef struct listepoint{
  int x;
  int y;
  struct listepoint* next;
} std_listepoint, *ListePoint;

ListePoint new_listepoint();

ListePoint add_point(ListePoint,int,int);

ListePoint delete_point(ListePoint,int,int);

void free_liste(ListePoint);

void draw_liste(ListePoint l,Image* img,bool ferme);*/

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
