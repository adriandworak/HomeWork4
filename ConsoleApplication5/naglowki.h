#ifndef naglowki_h
#define naglowki_h
class CFigura
{
protected:
	float x, y, angle;
};
class CBullet : public CFigura
{
	int predkosc;
	float czas;
	float pozy;
	bool strzal;
	float pozycjastrzalu;
	int mnoznik;
public:
	void sety(int a);
	void draw();
	void trajektoria( float kat, float x);
	CBullet();
	void strzelaj(float x);
	bool getstrzal();
	float getx();
	void ustalp(float p);
	float gety();
	int getpredkosc();
	void zmienpredkosc(int a);
};


class CCzolg : public CFigura
{
	int zycie;
public:
	void kat(float a);
	CCzolg(float p);
	void szkicowanie(float w, float h);
	void jedz(float p);
	void rysowanko();
	float getx();
	float getangle();
	int getzycie();
	bool detekcja(float x, float y);
};
void rysujswiat();
void rysujzycie(int zycia, bool gdzie);
void rysujserce();
void rysujmoc(int ile, float move);
#endif
