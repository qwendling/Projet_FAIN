
/*===============================================================*\

    Vendredi 25 septembre 2013

	Arash Habibi

	main.c

	Un programme equivalent à 02_glut.c et qui ne prend en compte
	que trois événements pour quitter le programme.

\*===============================================================*/

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Image.h"

Image *img;

int compareColor(Color c1,Color c2){
	return (c1._red == c2._red) && (c1._green == c2._green) && (c1._blue == c2._blue);
}

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
	if(dy<0){
		*y=-(*y);
	}
	if(dx<0){
		*x=-(*x);
	}
	if(dx<dy){
		int tmp=*x;
		*x=*y;
		*y=tmp;
	}

}

void I_bresenham(Image* img, int xA, int yA, int xB, int yB){
	Color blanc;
	blanc._red = 255;
	blanc._green = 255;
	blanc._blue = 255;
	I_changeColor(img,blanc);

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






//------------------------------------------------------------------
//	C'est le display callback. A chaque fois qu'il faut
//	redessiner l'image, c'est cette fonction qui est
//	appelee. Tous les dessins doivent etre faits a partir
//	de cette fonction.
//------------------------------------------------------------------

void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);

	Color noir;
	noir._red = 0;
	noir._green = 0;
	noir._blue = 0;
	I_fill(img,noir);
	//I_bresenhamOrigin(img,100,100);
	//I_bresenham(img,25,25,150,50);
	//I_bresenham(img,25,25,150,150);
	I_bresenham(img,150,150,0,0);
	I_bresenham(img,50,150,25,25);
	I_draw(img);

    glutSwapBuffers();
}





//------------------------------------------------------------------
// Cette fonction permet de réagir en fonction de la position de
// la souris (x,y), en fonction du bouton de la souris qui a été
// pressé ou relaché.
//------------------------------------------------------------------

void mouse_CB(int button, int state, int x, int y)
{
	if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN))
		I_focusPoint(img,x,img->_height-y);

	glutPostRedisplay();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir au fait que l'utilisateur
// presse une touche (non-spéciale) du clavier.
//------------------------------------------------------------------

void keyboard_CB(unsigned char key, int x, int y)
{
	// fprintf(stderr,"key=%d\n",key);
	switch(key)
	{
	case 27 : exit(1); break;
	case 'z' : I_zoom(img,2.0); break;
	case 'Z' : I_zoom(img,0.5); break;
	case 'i' : I_zoomInit(img); break;
	default : fprintf(stderr,"keyboard_CB : %d : unknown key.\n",key);
	}
	glutPostRedisplay();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir au fait que l'utilisateur
// presse une touche spéciale (F1, F2 ... F12, home, end, insert,
// haut, bas, droite, gauche etc).
//------------------------------------------------------------------

void special_CB(int key, int x, int y)
{
	// int mod = glutGetModifiers();

	int d = 10;

	switch(key)
	{
	case GLUT_KEY_UP    : I_move(img,0,d); break;
	case GLUT_KEY_DOWN  : I_move(img,0,-d); break;
	case GLUT_KEY_LEFT  : I_move(img,d,0); break;
	case GLUT_KEY_RIGHT : I_move(img,-d,0); break;
	default : fprintf(stderr,"special_CB : %d : unknown key.\n",key);
	}
	glutPostRedisplay();
}

//------------------------------------------------------------------------

int main(int argc, char **argv)
{
	if((argc!=3)&&(argc!=2))
	{
		fprintf(stderr,"\n\nUsage \t: %s <width> <height>\nou",argv[0]);
		fprintf(stderr,"\t: %s <ppmfilename> \n\n",argv[0]);
		exit(1);
	}
	else
	{
		int largeur, hauteur;
		if(argc==2)
		{
			img = I_read(argv[1]);
			largeur = img->_width;
			hauteur = img->_height;
		}
		else
		{
			largeur = atoi(argv[1]);
			hauteur = atoi(argv[2]);
			img = I_new(largeur,hauteur);
			Color rouge = C_new(100,0,0);
			Color blanc = C_new(200,200,255);
			I_checker(img,rouge,blanc,50);
		}
		int windowPosX = 100, windowPosY = 100;

		glutInitWindowSize(largeur,hauteur);
		glutInitWindowPosition(windowPosX,windowPosY);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
		glutInit(&argc, argv);
		glutCreateWindow(argv[0]);

		glViewport(0, 0, largeur, hauteur);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glOrtho(0,largeur,0,hauteur,-1,1);

		glutDisplayFunc(display_CB);
		glutKeyboardFunc(keyboard_CB);
		glutSpecialFunc(special_CB);
		glutMouseFunc(mouse_CB);
		// glutMotionFunc(mouse_move_CB);
		// glutPassiveMotionFunc(passive_mouse_move_CB);

		glutMainLoop();

		return 0;
	}
}
