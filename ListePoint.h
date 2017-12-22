#ifndef LISTEPOINT_H
#define LISTEPOINT_H

typedef struct listepoint{
  int x;
  int y;
  struct listepoint* next;
} std_listepoint, *ListePoint;

ListePoint new_listepoint();

ListePoint add_point(ListePoint,int,int);

ListePoint delete_point(ListePoint,int,int);

void free_liste(ListePoint);



#endif
