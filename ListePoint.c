#include <stdlib.h>
#include "ListePoint.h"
#include "bresenham.h"

ListePoint new_listepoint(){
  return NULL;
}

ListePoint add_point(ListePoint l,int x ,int y){
  if(l == NULL){
    ListePoint new = calloc(1,sizeof(std_listepoint));
    new->x=x;
    new->y=y;
    return new;
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
}

void draw_liste_aux(ListePoint l,ListePoint first,Image* img,bool ferme){

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
}
