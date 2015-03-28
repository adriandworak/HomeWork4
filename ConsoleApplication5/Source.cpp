#include <iostream>
#include "naglowki.h"
#include<windows.h>
#include <GL/freeglut.h>
using namespace std;
float czas = 0;
bool temp=false;
CCzolg Tank1(-3), Tank2(-3);
CBullet Bullet1, Bullet2;
const int glutWindowWidth = 640;
const int glutWindowHeight = 480;
float proportion = (float)glutWindowWidth / (float)glutWindowHeight;
void tank_functions(unsigned char key, int a, int b){
	switch (key)
	{
	case 'd':
		Tank1.jedz(0.1);
		break;
	case 'a':
		Tank1.jedz(-0.1);
		break;
	case 'w':
		Tank1.kat(1);
		break;
	case 's':
		Tank1.kat(-1);
		break;
	case 'l':
		Tank2.jedz(-0.1);
		break;
	case 'j':
		Tank2.jedz(+0.1);
		break;
	case 'i':
		Tank2.kat(1);
		break;
	case 'k':
		Tank2.kat(-1);
		break;
	case 'z':
		Bullet1.strzelaj(Tank1.getx());
		Bullet1.sety(1);
		break;
	case 'm':
		Bullet2.strzelaj(Tank2.getx());
		Bullet2.sety(1);
		break;
	case 'q':
		Bullet1.zmienpredkosc(-1);
		break;
	case 'e':
		Bullet1.zmienpredkosc(1);
		break;
	case 'u':
		Bullet2.zmienpredkosc(-1);
		break;
	case 'o':
		Bullet2.zmienpredkosc(1);
		break;
	}
}
	void timerFunc(int i)
	{
		glutTimerFunc(10, &timerFunc, 0);
		if (Bullet1.getstrzal())
		{
		Bullet1.trajektoria(Tank1.getangle(), Tank1.getx());
		if(Tank2.detekcja(-Bullet1.getx(), Bullet1.gety())==true)
			Bullet1.sety(0);
		}
		if (Bullet2.getstrzal())
		{
			Bullet2.trajektoria(Tank2.getangle(), Tank1.getx());
			if(Tank1.detekcja(-Bullet2.getx(), Bullet2.gety())==true)
				Bullet2.sety(0);
		}
	}
	
	
static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	proportion = ar;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
static void czolg(void)
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//nie tykac
	
	rysujmoc(Bullet2.getpredkosc()/3, 2);
	rysujmoc(Bullet1.getpredkosc()/3, -3.3);
	rysujswiat();
	rysujzycie(Tank1.getzycie(), false);
	rysujzycie(Tank2.getzycie(), true);

	glPushMatrix();
	glTranslated(Tank1.getx(), 0, 0);
	Tank1.rysowanko();
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glTranslated(Tank2.getx(), 0, 0);
	Tank2.rysowanko();
	glPopMatrix();
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	if (Bullet2.getstrzal())
		Bullet2.draw();
	glPopMatrix();
	if (Bullet1.getstrzal())
		Bullet1.draw();
	glPopMatrix();
	//nie tykac
	glutSwapBuffers();
	glPopMatrix();
}
static void idle(void)
{
	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	// it's still possible to use console to print messages
	// the same can be done with cout / cin
	Sleep(1000);
	sndPlaySound(L"waw.wav", SND_ASYNC);
	glutInitWindowSize(glutWindowWidth, glutWindowHeight);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutCreateWindow("OpenGLUT Shapes");
	glutReshapeFunc(resize);
	glutDisplayFunc(czolg);
	glutIdleFunc(idle);
	glutTimerFunc(1000, &timerFunc, 0);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// set white as clear colour
	glClearColor(0, 0.7, 0.9, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glutKeyboardFunc(tank_functions);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutMainLoop();
	return 0;
}