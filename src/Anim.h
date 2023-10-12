#ifndef DEF_ANIM
#define DEF_ANIM

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Sounds.h"
#include "Score.h"

using namespace std;

enum{ ACOIN, AMUSHRED, ASTAR, AFLOWER, ABREAK };

class Anim{
private:
	vector<int> m_offset, m_timer, m_type, m_current;
	vector<bool> isJumping;
	SDL_Surface *m_images[5][4];
	vector<SDL_Rect> m_pos, m_apos;
	vector<float> m_posRelX, m_posRelY;
public:
	Anim(int level);
	~Anim();
	void dispMush(SDL_Surface *screen, Map *map);
	void dispOther(SDL_Surface *screen, Map *map);
	void update(SDL_Rect *posM, Map *map, int *size, bool *gotFlower, Sounds *sounds, Score *score);
	void add(int type, int x, int y);
	int getOffset(int i);
	int getTimer(int i);
	void setTimer(int i, int j);
	void setOffset(int i, int j);
	int getType(int x, int y);
	void supressAll(int pos);
};


#endif