#ifndef LISTEPOINT_H
#define LISTEPOINT_H

#include "Image.h"
#include "Point.h"
#include "Arete.h"
#include <list>
#include <limits>

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
  void set_nearestArete(int x,int y);
};

#endif
