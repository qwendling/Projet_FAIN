#include <stdlib.h>
#include "Polygone.h"
#include "bresenham.h"
#include <iterator>
#include <iostream>

/*ListePoint new_listepoint(){
  return NULL;
}

ListePoint add_point(ListePoint l,int x ,int y){
  if(l == NULL){
    ListePoint new_liste = new ListePoint;
    new_liste->x=x;
    new_liste->y=y;
    return new_liste;
  }
  if(l->x == x && l->y == y)
    return l;
  l->next = add_point(l->next,x,y);
  return l;
}

ListePoint delete_point(ListePoint l,int x,int y){
  if(l==NULL){
    return NULL;
  }
  if(l->x == x || l->y == y){
    return l->next;
  }
  l->next = delete_point(l->next,x,y);
  return l;
}

void free_liste(ListePoint l){
  if(l == NULL)
    return;
  free_liste(l->next);
  free(l);
}*/

/*void draw_liste_aux(ListePoint l,ListePoint first,Image* img,bool ferme){

  if(l==NULL || (l->x == first->x && l->y == first->y))
    return;

  if(l->next == NULL){
    if(ferme)
      I_bresenham(img,l->x,l->y,first->x,first->y);
    return;
  }

  I_bresenham(img,l->x,l->y,l->next->x,l->next->y);
  draw_liste_aux(l->next,first,img,ferme);
}

void draw_liste(ListePoint l,Image* img,bool ferme){
  if(l==NULL || l->next == NULL)
    return;
  I_bresenham(img,l->x,l->y,l->next->x,l->next->y);
  draw_liste_aux(l->next,l,img,ferme);
}*/

void Polygone::draw(Image* img,bool ferme){
  std::cout << "last : " << (*(this->liste_points.end())).x << (*(this->liste_points.end())).y << std::endl;
  std::list<Point>::iterator it;
  Point p1,p2;
  for(it=this->liste_points.begin();std::next(it)!=this->liste_points.end();++it){
    p1=*it;
    p2=*std::next(it);
    I_bresenham(img,p1.x,p1.y,p2.x,p2.y);
  }
  if(ferme){
    p1=*(this->liste_points.begin());
    p2=*(std::prev(this->liste_points.end()));
    I_bresenham(img,p1.x,p1.y,p2.x,p2.y);
  }
}
