#ifndef DEF_SCORE
#define DEF_SCORE

#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

using namespace std;

class Score{
private:
	TTF_Font* _police;
	SDL_Surface *_mariotxt, *_worldtxt, *_currentWorldtxt, *_timetxt, *_currentTimetxt, *_currentScoretxt, *_currentCointxt;
	int _score, _timer, _time, _coin;
	char _scoretxt[20], _timechar[20], _coinchar[4];
public:
	Score(int level);
	~Score();
	void display(SDL_Surface *screen);
	void update();
	void addScore(int score);
	void addCoin();
};

#endif