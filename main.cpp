
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
#include "bresenham.h"
#include "Polygone.h"

typedef enum{
	append,
	vertex,
	edge,
} mode;


mode cur_mode = append;
Image *img;
//ListePoint lp;
Polygone p;
int _HauteurImg;
bool est_fill=false;


int compareColor(Color c1,Color c2){
	return (c1._red == c2._red) && (c1._green == c2._green) && (c1._blue == c2._blue);
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

	p.draw(img);

	if(est_fill){
		p.fill(img);
	}

	if(cur_mode==vertex){
		p.show_activeVertex(img);
	}

	if(cur_mode==edge){
		p.show_activeEdge(img);
	}

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
	if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN)&&(cur_mode==append)){
		p.add_point(x,_HauteurImg-y);
	}
	if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN)&&(cur_mode==vertex)){
		p.set_nearestPoint(x,_HauteurImg-y);
	}
	if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN)&&(cur_mode==edge)){
		p.set_nearestArete(x,_HauteurImg-y);
	}
	if((button==GLUT_MIDDLE_BUTTON)&&(state==GLUT_DOWN)&&(cur_mode==edge)){
		p.split_activeEdge();
	}
	glutPostRedisplay();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir au fait que l'utilisateur
// presse une touche (non-spéciale) du clavier.
//------------------------------------------------------------------

void keyboard_CB(unsigned char key, int x, int y)
{
	//fprintf(stderr,"key=%c\n",key);
	switch(key)
	{
	case 27 : exit(1); break;
	case 'z' : I_zoom(img,2.0); break;
	case 'Z' : I_zoom(img,0.5); break;
	case 'i' : I_zoomInit(img); break;
	case 'c' : p.fermer(); break;
	case 'f' : est_fill = !est_fill; break;
	case 'a' : cur_mode = append;break;
	case 'v' : cur_mode = vertex;break;
	case 'e' : cur_mode = edge;p.reset_edge();break;
	case 127 : if(cur_mode == vertex){
			p.supr_activeVertex();
		}
		break;
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
	case GLUT_KEY_UP    :
		if(cur_mode==vertex){p.move_vertex(img,0,1);break;}I_move(img,0,d); break;
	case GLUT_KEY_DOWN  :
		if(cur_mode==vertex){p.move_vertex(img,0,-1);break;}I_move(img,0,-d); break;
	case GLUT_KEY_LEFT  :
		if(cur_mode==vertex){p.move_vertex(img,-1,0);break;}I_move(img,d,0); break;
	case GLUT_KEY_RIGHT :
		if(cur_mode==vertex){p.move_vertex(img,1,0);break;}I_move(img,-d,0); break;
	case GLUT_KEY_PAGE_UP :
		if(cur_mode==vertex){p.next_vertex();}
		if(cur_mode==edge){p.next_edge();}
		break;
	case GLUT_KEY_PAGE_DOWN :
		if(cur_mode==vertex){p.prev_vertex();}
		if(cur_mode==edge){p.prev_edge();}
		break;
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

		_HauteurImg = img->_height;


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
