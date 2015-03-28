#include "naglowki.h"
#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
CBullet::CBullet()
{
	predkosc = 12;
	x = -10;
	mnoznik = 1;
}
void CBullet::zmienpredkosc(int a)
{
	if (predkosc > 4 && predkosc < 13)
	predkosc += a;
	if (predkosc == 4)
		predkosc = 5;
	if (predkosc == 13)
		predkosc = 12;
}
int CBullet::getpredkosc()
{
	return predkosc;
}
float CBullet::gety()
{
	return y;
}
void CBullet::ustalp(float p)
{
	x = p;
}
void CBullet::draw()
{
	glPushMatrix();
	glTranslated(0.5, 0, 0);
	glColor3d(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(x, y, 0);
	glVertex3d(x + 0.05, y, 0);
	glVertex3d( x + 0.05, y+0.05 , 0);
	glVertex3d( x, y +0.05, 0);
	glEnd();
	glPopMatrix();
}
void CBullet::trajektoria(float kat, float iks)
{
	angle = kat;
	czas+=0.01;
	x = predkosc*czas*cos(3.1415926535*angle / 180) + pozycjastrzalu;
	y = (predkosc*czas*sin(3.1415926535*angle / 180) - (10 * czas*czas) / 2 +0.35)*mnoznik ;
	if (y <= 0)
	{
		x = iks ;
		y = -10;
		czas = 0;
		strzal = false;
	}
}
void CBullet::strzelaj(float x)
{
	strzal = true;
	pozycjastrzalu = x;
}
bool CBullet::getstrzal()
{
	return strzal;
}
float CBullet::getx()
{
	return x;
}
void CBullet::sety(int a)
{
	mnoznik = a;
}

void CCzolg::kat(float a)
{
	angle += a;
}
CCzolg::CCzolg(float p)
{
	x = p, y = 0, angle = 0, zycie = 2;
}
float CCzolg::getx()
{
	return x;
}
float CCzolg::getangle()
{
	return angle;
}
int CCzolg::getzycie()
{
	return zycie;
}
void CCzolg::szkicowanie(float w, float h)
	{
		glColor3d(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3d(0, 0, 0);
		glVertex3d(w, 0, 0);
		glVertex3d(w, h, 0);
		glVertex3d(0, h, 0);
		glEnd();
	}
void CCzolg::rysowanko()
{
	glPushMatrix();
	glPushMatrix();
	szkicowanie(1, 0.25);
	glPopMatrix();
	glTranslated(0.35, 0.25, 0);
	szkicowanie(0.35, 0.25);
	glPopMatrix();
	glTranslated(0.63, 0.335, 0);
	glRotated(angle, 0, 0, 1);
	szkicowanie(0.7, 0.1);
}

void CCzolg::jedz(float p)
{
	x += p;
}

bool CCzolg::detekcja(float iks, float igr)
{
	if (iks >= x+0.5 && iks <= x + 1.5 && igr < 0.30 && igr > 0)
	{
		zycie -= 1;
		return true;
	}
	
}
void rysujswiat()
{
	glPushMatrix();
	glColor3d(0.2, 0.7, 0);
	glBegin(GL_POLYGON);
	glVertex3d(-10, 0, 0);
	glVertex3d(-10, -0.2, 0);
	glVertex3d(10, -0.2, 0);
	glVertex3d(10, 0, 0);
	glEnd();
	glColor3d(1, 0.7, 0.3);
	glBegin(GL_POLYGON);
	glVertex3d(-10, -0.2, 0);
	glVertex3d(-10, -5, 0);
	glVertex3d(10, -5, 0);
	glVertex3d(10, -0.2, 0);
	glEnd();
	glPopMatrix();
}
void rysujserce()
{
	glPushMatrix();
	glColor3d(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(0.4, 0.5, 0);
	glVertex3d(0.45, 0.6, 0);
	glVertex3d(0.5, 0.7, 0);
	glVertex3d(0.4, 0.8, 0);
	glVertex3d(0.3, 0.9, 0);
	glVertex3d(0.25, 0.93, 0);
	glVertex3d(0.20, 0.84, 0);
	glVertex3d(0.05, 0.75, 0);
	glVertex3d(0,0.7,0);
	glEnd();
	glPopMatrix();
}
void rysujzycie(int zycia, bool gdzie)
{
	if (gdzie)
	{
		if (zycia == 2)
		{
			glPushMatrix();
			glTranslated(2.75, 1.4, 0);
			rysujserce();
			glRotated(180, 0, 1, 0);
			rysujserce();
			glTranslated(1, 0, 0);
			rysujserce();
			glRotated(180, 0, 1, 0);
			rysujserce();
			glPopMatrix();
		}
		if (zycia == 1)
		{
			glPushMatrix();
			glTranslated(2.75, 1.4, 0);
			rysujserce();
			glRotated(180, 0, 1, 0);
			rysujserce();
			glPopMatrix();
		}
	}
	if (gdzie==false)
	{
		if (zycia == 2)
		{
			glPushMatrix();
			glTranslated(-2.75, 1.4, 0);
			rysujserce();
			glRotated(180, 0, 1, 0);
			rysujserce();
			glTranslated(-1, 0, 0);
			rysujserce();
			glRotated(180, 0, 1, 0);
			rysujserce();
			glPopMatrix();
		}
		if (zycia == 1)
		{
			glPushMatrix();
			glTranslated(-2.75, 1.4, 0);
			rysujserce();
			glRotated(180, 0, 1, 0);
			rysujserce();
			glPopMatrix();
		}
	}



}	

void rysujmoc(int ile, float move)
{
	glPushMatrix();
	glTranslated(move, -2, 0);
	float temp = 0;
	for (int a = 0; a < ile; a++)
	{
		glPushMatrix();
		glColor3d(0.5, 0.5, 0.5);
		glTranslated(temp, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0.2+temp, 0);
		glVertex3d(0.2, 0.2+temp, 0);
		glVertex3d(0.2, 0, 0);
		glEnd();
		glPopMatrix();
		temp += 0.3;
	}
	glPopMatrix();
}

		