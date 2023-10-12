#ifndef DEF_GOOMBA
#define DEF_GOOMBA

#include "Map.h"
#include <vector>
#include <SDL.h>

using namespace std;
#define GOOMBA_SPEED (1)
enum{GOOMBAT, KOOPAT, CARNT};

typedef struct pos{
	float x;
	float y;
} pos;


class Goomba{
private:
	vector<pos> m_pos;
	vector<int> m_currentImage, m_hurt, m_timerInd, m_died, m_posRelY, m_posJY, m_lastY, m_type, m_isMoving;
	vector<float> m_posJX, m_speed;
	vector<bool> m_isJumping, m_detected;
	SDL_Surface *m_images[3][6];
	int m_timer, m_nb;
	Map *m_map;
public:
	Goomba(Map *map, int level);
	~Goomba();
	void find(Map *map);
	int getX(int i);
	int getY(int i);
	int get_nb();
	void setX(int i, int x);
	void setY(int i, int y);
	void update();
	void setMap(Map *map);
	void display(SDL_Surface *screen);
	void set_current(int i, int j);
	int is_hurt(int i);
	void set_hurt(int i, int j);
	void setDied(int i);
	int isDied(int i);
	void supressAll(int pos);
	int getType(int pos);
	void setMoving(int i, int j);
	int getMoving(int i);
	void setSpeed(int i, int j);
};

#endif