#ifndef LISTEPOINT_H
#define LISTEPOINT_H

#include "Image.h"
#include <list>
#include <limits>

class Point{
public:
  int x;
  int y;
  Point() : x(0),y(0){}
  Point(int _x,int _y) : x(_x),y(_y){}
  Point(const Point& p) : x(p.x),y(p.y){}
  bool operator==(const Point& p)const{return p.x==this->x && p.y == this->y;}
};

class Arete{
public:
  Point Pmin;
  Point Pmax;
  int x_inters;
  int inc;
  Arete() : Pmin(),Pmax(),x_inters(0),inc(0){}
  Arete(const Point& p1,const Point& p2){
    if(p1.y<=p2.y){
      Pmin = p1;
      Pmax = p2;
      return;
    }
    Pmin = p2;
    Pmax = p1;
  }
};

class foncteur_nearestPoint{
public:
  Point nearestPoint;
  int carre_distance;
  Point compare_Point;
  foncteur_nearestPoint() : carre_distance(std::numeric_limits<int>::max()){}
  foncteur_nearestPoint(const Point& p) : compare_Point(p),carre_distance(std::numeric_limits<int>::max()){}
  void operator()(const Point& p);
};

class Polygone{
public:
  int Xmin;
  int Xmax;
  int Ymin;
  int Ymax;
  bool est_ferme;
  std::list<Point> liste_points;
  std::list<Point>::iterator it_curPoint;
  std::list<Point>::iterator it_curEdge;
  Polygone();
  void add_point(int x,int y);
  void draw(Image*);
  void fill(Image*);
  void fermer(){est_ferme=!est_ferme;}
  bool get_estFeme(){return est_ferme;}

  void show_activeVertex(Image*);
  void supr_activeVertex();
  void next_vertex();
  void prev_vertex();
  void move_vertex(Image*,int,int);

  void reset_edge();
  void show_activeEdge(Image*);
  void next_edge();
  void prev_edge();
  void split_activeEdge();

  void set_nearestPoint(int x,int y);
};

#endif
