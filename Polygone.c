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

  std::vector<Arete>::iterator it_TA;
  for(it_TA = TA.begin();it_TA!=TA.end();it_TA++){
    std::cout << "ymax : " << (*it_TA).Pmax.y << "ymin : " << (*it_TA).Pmin.y << std::endl;
  }

  int indx_prochaine_arete = 0;
  Arete prochaine_arete = TA[0];
  int prochain_ymin = prochaine_arete.Pmin.y;
  std::list<Arete> TAA;


  for(int y = this->Ymin;y < this->Ymax;y++){
    std::cout << "ymin : " << this->Ymin << "ymax : " << this->Ymax << std::endl;
    std::cout << y << std::endl;
    while(y>=prochain_ymin){

      prochaine_arete.x_inters = prochaine_arete.Pmin.x;
      prochaine_arete.inc=0;
      std::cout << "prochaine_arete id : "<< indx_prochaine_arete <<" ymax : " << prochaine_arete.Pmax.y << "ymin : " << prochaine_arete.Pmin.y << std::endl;
      TAA.push_back(prochaine_arete);
      //std::sort(TAA.begin(),TAA.end(),compareAreteInters);
      TAA.sort(compareAreteInters);
      indx_prochaine_arete++;
      prochaine_arete = TA[indx_prochaine_arete];
      prochain_ymin = prochaine_arete.Pmin.y;
    }
    std::cout << "fin premier while" << std::endl;

    TAA.remove_if([&y](Arete& a){return a.Pmax.y == y;});

    std::list<Arete>::iterator it_TAA;
    for(it_TAA = TAA.begin();it_TAA!=TAA.end();it_TAA++){
      std::cout << "ymax : " << (*it_TAA).Pmax.y << "ymin : " << (*it_TAA).Pmin.y << std::endl;
    }
  }


}
