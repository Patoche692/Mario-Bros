#ifndef DEF_MAP
#define DEF_MAP

#include <fstream>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

#define WIDTH_MAP (220)
#define HEIGHT_MAP (18)
#define SIZE_TILES (50)

class Map{
private:
	char m_mat[WIDTH_MAP][HEIGHT_MAP], m_anim[WIDTH_MAP][HEIGHT_MAP], m_offset[WIDTH_MAP][HEIGHT_MAP], m_upAnim[WIDTH_MAP][HEIGHT_MAP];
	int m_level;
	SDL_Surface *m_tilesAnim[5][4], *m_tiles[15], *m_coin[4];
	int Xscroll, m_currentAnim, m_timer;
	bool m_isScrolling;
public:
	Map();
	~Map();
	Map(int level);
	void load(int level);
	SDL_Rect getXCastle();
	void display(SDL_Surface *screen);
	char get_mat(int i, int j);
	int getXScroll();
	void setXScroll(int a);
	bool isScrolling();
	void setScrolling(bool a);
	void set_mat(int i, int j, int a);
	int getMarioX();
	int getMarioY();
	SDL_Rect getTargetPos();
	void anim(int i, int j, int size);
	bool isAnim(int x, int y);
};
#endif