#include <stdlib.h>
#include "ListePoint.h"

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
  add_point(l->next,x,y);
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
