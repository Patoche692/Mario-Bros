#ifndef DEF_FIRE
#define DEF_FIRE

#include "Input.h"
#include "Sounds.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Goomba.h"


class Fire{
private:
	SDL_Surface *m_images[6];
	vector<SDL_Rect> m_pos;
	vector<int> m_xspeed, m_yspeed, m_starty, m_current, m_explode, m_time;
	vector<float> m_posRelX, m_posRelY;
	int m_nb, m_timer;

public:
	Fire();
	~Fire();
	void display(SDL_Surface *screen, int xscroll);
	void update(Goomba *goomba, Map *map, Sounds *sounds);
	void add(int x, int y, Input *input);
	int get_nb();
	void supressAll(int i);
	int getX(int i);
	int getY(int i);
	void setExplode(int i);
};

#endif