#ifndef LISTEPOINT_H
#define LISTEPOINT_H

#include "Image.h"

typedef struct listepoint{
  int x;
  int y;
  struct listepoint* next;
} std_listepoint, *ListePoint;

ListePoint new_listepoint();

ListePoint add_point(ListePoint,int,int);

ListePoint delete_point(ListePoint,int,int);

void free_liste(ListePoint);

void draw_liste(ListePoint l,Image* img);

#endif
