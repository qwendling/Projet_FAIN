#include <stdlib.h>
#include "Polygone.h"
#include "bresenham.h"
#include "foncteur_nearestPoint.h"
#include <iterator>
#include <iostream>
#include <algorithm>



Polygone::Polygone() : est_ferme(false),
  liste_points(),
  Xmin(std::numeric_limits<int>::max()),
  Xmax(0),
  Ymax(0),
  Ymin(std::numeric_limits<int>::max()){
    it_curPoint=liste_points.end();
    it_curEdge=liste_points.end();
  }

void Polygone::add_point(int x,int y){
  liste_points.push_back(Point(x,y));
  if(it_curPoint==liste_points.end()){
    it_curPoint = liste_points.begin();
  }
  if(it_curEdge==liste_points.end()){
    it_curEdge = liste_points.begin();
  }
  if(x>Xmax)
    Xmax=x;
  if(x<Xmin)
    Xmin=x;
  if(y>Ymax)
    Ymax=y;
  if(y<Ymin)
    Ymin=y;
}

void Polygone::draw(Image* img){
  Color blanc;
	blanc._red = 255;
	blanc._green = 255;
	blanc._blue = 255;
  std::list<Point>::iterator it;
  Point p1,p2;
  for(it=this->liste_points.begin();std::next(it)!=this->liste_points.end();++it){
    p1=*it;
    p2=*std::next(it);
    I_bresenham(img,p1.x,p1.y,p2.x,p2.y,blanc);
  }
  if(est_ferme){
    p1=*(this->liste_points.begin());
    p2=*(std::prev(this->liste_points.end()));
    I_bresenham(img,p1.x,p1.y,p2.x,p2.y,blanc);
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
  std::vector<Arete> TAA;


  for(int y = this->Ymin;y < this->Ymax;y++){
    while(y>=prochain_ymin && indx_prochaine_arete < TA.size()){
      prochaine_arete.x_inters = prochaine_arete.Pmin.x;
      prochaine_arete.inc=0;
      TAA.push_back(prochaine_arete);
      indx_prochaine_arete++;
      prochaine_arete = TA[indx_prochaine_arete];
      prochain_ymin = prochaine_arete.Pmin.y;
    }

    TAA.erase(std::remove_if(TAA.begin(),TAA.end(),[&y](Arete& a){return a.Pmax.y == y;}),TAA.end());
    std::sort(TAA.begin(),TAA.end(),compareAreteInters);

    int N = TAA.size()/2;
    for(int i=0;i < N;i++){
      Arete A2i = TAA[2*i];
      Arete A2i1 = TAA[2*i+1];
      for(int x=A2i.x_inters;x<A2i1.x_inters;x++){
        I_plot(img,x,y);
      }
    }
    std::vector<Arete>::iterator it_A;
    for(it_A = TAA.begin();it_A!=TAA.end();it_A++){
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


void Polygone::show_activeVertex(Image* img){
  if(it_curPoint == liste_points.end())
    return;
  Color blanc;
  blanc._red = 255;
	blanc._green = 0;
	blanc._blue = 0;
	I_changeColor(img,blanc);
  Point activeVertex = *it_curPoint;
  for(int i=-2;i<=2;i++){
    for(int j=-2;j<=2;j++){
      if(i==j && i==0){
        continue;
      }
      if(activeVertex.x+i > img->_width || activeVertex.x+i < 0 || activeVertex.y+j > img->_height || activeVertex.y+j < 0)
        continue;
      I_plot(img,activeVertex.x+i,activeVertex.y+j);
    }
  }
}

void Polygone::supr_activeVertex(){
  if(it_curPoint == liste_points.end()){
    return;
  }
  liste_points.erase(it_curPoint++);
  if(it_curPoint == liste_points.end()){
    it_curPoint--;
  }
}

void Polygone::next_vertex(){
  if(it_curPoint == liste_points.end()){
    return;
  }
  it_curPoint++;
  if(it_curPoint == liste_points.end()){
    it_curPoint=liste_points.begin();
  }
}

void Polygone::prev_vertex(){
  if(it_curPoint == liste_points.end()){
    return;
  }
  if(it_curPoint == liste_points.begin()){
    it_curPoint = std::prev(liste_points.end());
    return;
  }
  it_curPoint--;
}

void Polygone::move_vertex(Image* img,int dx,int dy){
  if(it_curPoint == liste_points.end()){
    return;
  }
  if(it_curPoint->x+dx>0 && it_curPoint->x+dx < img->_width){
    it_curPoint->x += dx;
    if(it_curPoint->x>Xmax){
      Xmax = it_curPoint->x;
    }
    if(it_curPoint->x<Xmin){
      Xmin = it_curPoint->x;
    }
  }
  if(it_curPoint->y+dy>0 && it_curPoint->y+dy < img->_height){
    it_curPoint->y +=dy;
    if(it_curPoint->y>Ymax){
      Ymax = it_curPoint->y;
    }
    if(it_curPoint->y<Ymin){
      Ymin = it_curPoint->y;
    }
  }

}

void Polygone::reset_edge(){
  it_curEdge = liste_points.begin();
}

void Polygone::show_activeEdge(Image* img){
  if(it_curEdge == liste_points.end())
    return;
  std::list<Point>::iterator it_p2 = std::next(it_curEdge);
  if(it_p2 == liste_points.end()){
    if(!est_ferme){
      return;
    }
    it_p2=liste_points.begin();
  }
  Color c;
	c._red = 255;
	c._green = 0;
	c._blue = 0;
  I_bresenham(img,it_curEdge->x,it_curEdge->y,it_p2->x,it_p2->y,c);
}

void Polygone::next_edge(){
  if(it_curEdge == liste_points.end()){
    return;
  }
  it_curEdge++;
  if(it_curEdge == liste_points.end()){
    it_curEdge=liste_points.begin();
  }
  if(it_curEdge == std::prev(liste_points.end()) && !est_ferme){
    it_curEdge=liste_points.begin();
  }
}

void Polygone::prev_edge(){
  if(it_curEdge == liste_points.end()){
    return;
  }
  if(it_curEdge == liste_points.begin()){
    if(est_ferme){
      it_curEdge = std::prev(liste_points.end());
    }else{
      it_curEdge = std::prev(std::prev(liste_points.end()));
    }
    return;
  }
  it_curEdge--;
}

void Polygone::split_activeEdge(){
  if(it_curEdge == liste_points.end())
    return;
  std::list<Point>::iterator it_p2 = std::next(it_curEdge);
  if(it_p2 == liste_points.end()){
    if(!est_ferme){
      return;
    }
    it_p2=liste_points.begin();
  }
  Point next_pts((it_curEdge->x+it_p2->x)/2,(it_curEdge->y+it_p2->y)/2);
  liste_points.insert(it_p2,next_pts);
}

void Polygone::set_nearestPoint(int x,int y){
  foncteur_nearestPoint f(Point(x,y));
  f=std::for_each(liste_points.begin(),liste_points.end(),f);
  it_curPoint = std::find(liste_points.begin(),liste_points.end(),f.nearestPoint);
}
