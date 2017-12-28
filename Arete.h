#ifndef ARETE_H
#define ARETE_H

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

#endif
