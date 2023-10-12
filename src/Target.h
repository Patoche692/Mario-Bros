#ifndef DEF_TARGET
#define DEF_TARGET
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Fire.h"
#include "Map.h"
#include "Sounds.h"

class Target{
private:
	SDL_Rect m_pos;
	SDL_Surface *m_surf;
	bool m_isHurt;
public:
	Target(int x, int y);
	~Target();
	void update(Map *map, Fire *fire, Sounds *sounds);
	void display(SDL_Surface *screen, int Xscroll);
	int m_speedY;
};

#endif