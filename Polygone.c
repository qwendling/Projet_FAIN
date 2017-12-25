#include <stdlib.h>
#include "Polygone.h"
#include "bresenham.h"
#include <iterator>
#include <iostream>
#include <algorithm>

void Polygone::add_point(int x,int y){
  liste_points.push_back(Point(x,y));
  if(x>Xmax)
    Xmax=x;
  if(x<Xmin)
    Xmin=x;
  if(y>Ymax)
    Ymax=y;
  if(y<Ymin)
    Ymin=y;
}

void Polygone::draw(Image* img,bool ferme){
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

bool sort_arete_ymin(const Arete& a1,const Arete& a2){
  if(a1.Pmin.y < a2.Pmin.y)
    return true;
  return false;
}

bool compareAreteInters(const Arete& a1,const Arete& a2){
  if(a1.x_inters<a2.x_inters)
    return true;
  return false;
}

void Polygone::fill(Image* img){
  Color blanc;
	blanc._red = 255;
	blanc._green = 255;
	blanc._blue = 255;
	I_changeColor(img,blanc);


  std::vector<Arete> TA;
  std::list<Point>::iterator it;
  Point p1,p2;
  for(it=this->liste_points.begin();std::next(it)!=this->liste_points.end();++it){
    p1=*it;
    p2=*std::next(it);
    TA.push_back(Arete(p1,p2));
  }
  p1=*(this->liste_points.begin());
  p2=*(std::prev(this->liste_points.end()));
  TA.push_back(Arete(p1,p2));
  std::sort(TA.begin(),TA.end(),sort_arete_ymin);

  int indx_prochaine_arete = 0;
  Arete prochaine_arete = TA[0];
  int prochain_ymin = prochaine_arete.Pmin.y;
  //std::list<Arete> TAA;
  std::vector<Arete> TAA;


  for(int y = this->Ymin;y < this->Ymax;y++){
    while(y>=prochain_ymin && indx_prochaine_arete < TA.size()){
      prochaine_arete.x_inters = prochaine_arete.Pmin.x;
      prochaine_arete.inc=0;
      TAA.push_back(prochaine_arete);
      //TAA.sort(compareAreteInters);
      //std::sort(TAA.begin(),TAA.end(),compareAreteInters);
      indx_prochaine_arete++;
      prochaine_arete = TA[indx_prochaine_arete];
      prochain_ymin = prochaine_arete.Pmin.y;
    }

    TAA.erase(std::remove_if(TAA.begin(),TAA.end(),[&y](Arete& a){return a.Pmax.y == y;}),TAA.end());
    std::sort(TAA.begin(),TAA.end(),compareAreteInters);

    /*TAA.remove_if([&y](Arete& a){return a.Pmax.y == y;});
    std::list<Arete>::iterator it_TAA;
    for(it_TAA = TAA.begin();it_TAA!=TAA.end();it_TAA++){
      std::cout << "ymax : " << (*it_TAA).Pmax.y << "ymin : " << (*it_TAA).Pmin.y << "x_inters : " << (*it_TAA).x_inters << std::endl;
    }*/
    int N = TAA.size()/2;
    for(int i=0;i < N;i++){
      //Normalement on colorie ici
      Arete A2i = TAA[2*i];
      Arete A2i1 = TAA[2*i+1];
      for(int x=A2i.x_inters;x<A2i1.x_inters;x++){
        I_plot(img,x,y);
      }
    }
    std::vector<Arete>::iterator it_A;
    for(it_A = TAA.begin();it_A!=TAA.end();it_A++){
      //std::cout << "AH ! " << std::endl;
      int dx = (*it_A).Pmax.x-(*it_A).Pmin.x;
      int dy = (*it_A).Pmax.y-(*it_A).Pmin.y;
      (*it_A).inc=(*it_A).inc + dx;
      while((*it_A).inc > dy){
        (*it_A).inc=(*it_A).inc-dy;
        (*it_A).x_inters++;
      }
      while((*it_A).inc < -dy){
        (*it_A).inc=(*it_A).inc+dy;
        (*it_A).x_inters--;
      }
    }

  }


}
