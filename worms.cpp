#include "worms.h"
#include <iostream>

Physics worms::wormPhs;

worms::worms()
{
	Physics wormPhs;
}


worms::~worms()
{
}

bool
worms::startMov(char _key) { //checks if the key is a move key for the worm, if so changes direction and starts monitoring.
	if (Keys[move_left]==_key) {//if the keys arent of this worm, it returns false, if it is, it returns true.
		if (state == idle) {
			dir = left;
			state = monitorMov;
		}else if (state == end_mov) {
			if (dir == left)
				state = moving;
		}
	}else if (Keys[move_right] == _key) {
		if (state == idle) {
			dir = right;
			state = monitorMov;
		}else if (state == end_mov) {
			if(dir==right)
				state = moving;
		}
	}else {
		return false;
	}
	return true;
}

bool
worms::stopMov(char _key){
	if (Keys[move_right] == _key){
		if (dir == right) {
			if (state == moving) {
				state = end_mov;
			}
			else if (state == monitorMov) {
				state = end_mov;
			}
		}
	}
	else if (Keys[move_left] == _key) {
		if (dir == left) {
			if (state == moving) {
				state = end_mov;

			}
			else if (state == monitorMov) {
				state = end_mov;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

int
worms::getDir() {
	return dir;
}

unsigned int
worms::getFrame() {
	return framecnt;
}

position
worms::getPos() {
	return pos;
}

stateType
worms::getState() {
	return state;
}

double 
worms::getPhys(char _option) {
	if (_option == 'g') {
		return wormPhs.getGrav();
	}else if(_option == 'x'){
		return wormPhs.getVx();
	}
	else if (_option == 'y') {
		return wormPhs.getVy();
	}
	else if (_option == 'a') {
		return wormPhs.getAng();
	}
	return -1;
}

void
worms::setKeys(unsigned int left, unsigned int right, unsigned int jmp) {
	Keys[move_left] = left;
	Keys[move_right] = right;
	Keys[jump] = jmp;
}

bool
worms::startJum(char _key){
	if(Keys[jump]==_key){
		if (state == idle) {
			state = jumping;
		}
		else if (state == end_jmp) {
			state = jumping;
		}
	}
	else {
		return false;
	}
	return true;
}

bool
worms::stopJum(char _key){
	if (Keys[jump] == _key) {
		if (state == jumping) {
			state = end_jmp;

		}
		return true;
	}
	return false;
}

void
worms::Update(){
	if (state != idle) {
		switch (state) {
			case monitorMov:
				if(framecnt >= 5){
					state = moving;
				}
				break;
			case moving:
				movePos();
				if (framecnt == 50)
					framecnt = 0;
				break;
			case jumping:
				jumpPos();
				if (framecnt == 36)
					framecnt = 0;
				break;
			case end_mov:
				if (framecnt <= 5 || framecnt > 50) {
					state = idle;
					framecnt = 0;
				}else
					movePos();
				break;
			case end_jmp:
				if ( framecnt == 36) {
					jumpPos();
					state = idle;
					framecnt = 0;
				}
				else
					jumpPos();
				break;
		}
		framecnt++;
	}
}

void
worms::movePos(){
	if (framecnt==22 || framecnt==36 || framecnt==50) {
		if (dir == right) {
			pos.setX(pos.getX()+wormPhs.getVx()/3);
		}
		else {
			pos.setX(pos.getX() - wormPhs.getVx() / 3);
		}
	}
}

void
worms::jumpPos() {
	if (framecnt == 4) {
		if (dir == right) {
			pos.setX(pos.getX() + 2.4);
		}
		else {
			pos.setX(pos.getX() - 2.4);
		}		 
	}																		 	
	else if ((framecnt > 4) && (framecnt <= 36)) {				
		if (dir == right) {
			pos.setX(pos.getX() + 2.32);
		}
		else {
			pos.setX(pos.getX() - 2.32);
		}
	}
	if (framecnt > 3 && framecnt <= 36) {  //incrementalmente la ecuacion de tiro oblivuo resulta:
		pos.setY(pos.getY() - 3.89711 + wormPhs.getGrav()*((framecnt-3) + 0.5)); //y2=y1-vY+g(t+1/2)
	}
}

void
worms::interruptMov() {
	state = idle;
}

void
worms::setPos(position newPos) {
	pos = newPos;
}

void
worms::setPos(double x, double y) {
	pos.setX(x);
	pos.setY(y);
}

double
Physics::getGrav() {
	return gravity;
}

double
Physics::getVx() {
	return speedX;
}

double
Physics::getVy() {
	return speedY;
}

double
Physics::getAng() {
	return lngjmpAngle;
}

void
worms::setDir(int dir_) {
	dir = (direction)dir_;
}