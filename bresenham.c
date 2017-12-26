#include "bresenham.h"

void I_bresenhamOrigin(Image *img,int x,int y){

	Color blanc;
	blanc._red = 255;
	blanc._green = 255;
	blanc._blue = 255;
	I_changeColor(img,blanc);

	int incrd1 = 2*y;
	int incrd2 = 2*(y-x);

	int tmpx=0,tmpy=0;
	int d=2*y-x;

	while(tmpx<x){
		I_plot(img,tmpx,tmpy);
		tmpx++;
		if(d<0){
			d+=incrd1;
		}else{
			tmpy++;
			d+=incrd2;
		}
	}


}

void Z2to1O(int xA,int yA,int xB,int yB,int* OxA,int* OyA,int* OxB,int* OyB){
	xB=xB-xA;
	yB=yB-yA;
	xA=0;
	yA=0;

	int dx = xB - xA;
	int dy = yB - yA;
	if(dx<0){
		xA = -xA;
		xB = -xB;
	}
	if(dy<0){
		yA = -yA;
		yB = -yB;
	}
	if(abs(dx) < abs(dy)){
		*OxA=yA;
		*OyA=xA;
		*OxB=yB;
		*OyB=xB;
		return;
	}
	*OxA=xA;
	*OyA=yA;
	*OxB=xB;
	*OyB=yB;
}

void O1toZ2(int xA,int yA,int xB,int yB,int* x,int* y){
	int dx = xB-xA;
	int dy = yB-yA;
	if(abs(dx) < abs(dy)){
		int tmp=*x;
		*x=*y;
		*y=tmp;
	}
	if(dy<0){
		*y=-(*y);
	}
	if(dx<0){
		*x=-(*x);
	}

	*x += xA;
	*y += yA;
}

void I_bresenham(Image* img, int xA, int yA, int xB, int yB,Color c){
	I_changeColor(img,c);

	int OxA,OyA,OxB,OyB;

	Z2to1O(xA,yA,xB,yB,&OxA,&OyA,&OxB,&OyB);
	int dx = OxB-OxA;
	int dy = OyB-OyA;

	int incrd1 = 2*dy;
	int incrd2 = 2*(dy-dx);

	int tmpx=OxA,tmpy=OyA;
	int d=2*dy-dx;
	int x,y;

	while(tmpx<OxB){
		x=tmpx;
		y=tmpy;
		O1toZ2(xA,yA,xB,yB,&x,&y);
		I_plot(img,x,y);
		tmpx++;
		if(d<0){
			d+=incrd1;
		}else{
			tmpy++;
			d+=incrd2;
		}
	}
	x=tmpx;
	y=tmpy;
	O1toZ2(xA,yA,xB,yB,&x,&y);
	I_plot(img,x,y);
}
