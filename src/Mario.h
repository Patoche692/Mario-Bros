#ifndef MARIO_H

#define MARIO_H

#include "Goomba.h"
#include "Map.h"
#include "Input.h"
#include "Sounds.h"
#include "Score.h"
#include "Fire.h"
#include "Anim.h"
#include "Target.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#define SPEED (2)

using namespace std;
enum{SMALL, TALL, FIREM};

const int TIMER(12);

class Mario
{
private:

	SDL_Rect m_pos, m_lastPos, m_clear;
	Fire *m_fire;
	Anim *m_anim;
	float m_posRelX;
	SDL_Surface *m_images[3][2][5], *m_current;
	bool isJumping, m_collideUp, *m_continuer, gotFlower, *m_win, m_isGrowing;
	int m_currentDir, m_posRelY, m_size, m_lastRelY, m_speed;
	int m_currentNumber, m_coeffJump;
	float m_timer, m_startTime, m_currentTime, m_offset, m_previousOffset;
	Sounds *m_sounds;
	Map *m_map;
	Goomba *m_goomba;

public:
	Mario(int level);
	~Mario();
	void updateLastPos();
	void setX(int x);
	void setY(int y);
	void setXRel(float xRel);
	void setYRel(int yRel);
	void setSounds(Sounds *sounds);
	void setClearPos(SDL_Rect pos);
	Sint16 getX();
	Sint16 getY();
	Sint16 getXRel();
	Sint16 getYRel();
	SDL_Surface *getCurrentSurface();
	SDL_Rect getPos();
	void setCurrent(SDL_Surface *current);
	SDL_Surface *getSurface(int dir, int pos);
	void display(SDL_Surface *screen);
	void anim(int dir);
	bool getJumping();
	void set_start_time(int a);
	void setJumping(bool a);
	void set_current_time(int a);
	void jump();
	int get_current_time();
	int get_offset();
	void update(Input *m_input, Target& target, Score *score);
	void setMap(Map *map);
	bool getCollideUp();
	void setCollideUp(bool tf);
	Map getMap();
	void set_goomba(Goomba *goomba);
	void set_continuer(bool *continuer, bool *win);
	void dispFire(SDL_Surface *screen);
	void dispMush(SDL_Surface *screen);
	void dispOther(SDL_Surface *screen);
	void newFA(int level);
	int getSize();
	void init(int x, int y);
	void setSpeed(int speed);
	int getSpeed();
};

#endif