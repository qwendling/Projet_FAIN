#include "Arete_distance.h"
#include <iostream>
#include <stdlib.h>

void Arete_distance::calcul_distance(const Point& C){
  Point AB,AC,BC;
  AB.x = B.x - A.x;
  AB.y = B.y - A.y;
  AC.x = C.x - A.x;
  AC.y = C.y - A.y;
  BC.x = C.x - B.x;
  BC.y = C.y - B.y;
  int pscal1 = AB.x*AC.x + AB.y*AC.y;  // produit scalaire
  int pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y;  // produit scalaire
  if (pscal1>=0 && pscal2>=0){
    long numerateur = AB.x*AC.y - AB.y*AC.x;   // norme du vecteur v
    numerateur *= numerateur;
    int denominateur = AB.x*AB.x + AB.y*AB.y;  // norme de u
    carre_distance = abs(numerateur / denominateur);
    return;
  }
  int d1 = (C.x - A.x)*(C.x - A.x)+(C.y - A.y)*(C.y - A.y);
  int d2 = (C.x - B.x)*(C.x - B.x)+(C.y - B.y)*(C.y - B.y);
  if(d1 < d2){
    carre_distance = abs(d1);
    return;
  }
  carre_distance = abs(d2);
}

bool Arete_distance::operator<(const Arete_distance& a){
  return carre_distance < a.carre_distance;
}
