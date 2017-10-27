#pragma once
#ifndef _H_WORMS

#define _H_WORMS
#include "possition.h"
#include <cmath>
#include <allegro5\allegro.h>
enum stateType{ idle, monitorMov, moving, jumping, end_mov, end_jmp };
enum keyType{ move_left, move_right, jump};
enum direction {left, right};



class Physics
{
	const double gravity = 0.24;
	const double speedX = 27;
	const double speedY = 4.5*sin(lngjmpAngle);
	const double lngjmpAngle = 60 / 3.141592;
public:
	double getGrav();
	double getVx();
	double getVy();
	double getAng();
};


class worms
{
	stateType state = idle;
	unsigned int framecnt=0;
	direction dir;
	position pos;
	Physics static wormPhs;
	unsigned int Keys[3];
	void movePos();
	void jumpPos();
	
	
public:
	worms();
	~worms();
	void Update();
	bool startMov(char);
	bool stopMov(char);
	bool startJum(char);
	bool stopJum(char);
	void interruptMov();
	unsigned int getFrame();
	stateType getState();
	position getPos();
	int getDir();
	static double getPhys(char);
	void setDir(int);
	void setPos(position);
	void setPos(double x, double y);
	void setKeys(unsigned int left, unsigned int right, unsigned int jmp);
};

#endif