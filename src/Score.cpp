#include "Score.h"

Score::Score(int level){ 
	_time = 400;
	char world[4];
	sprintf(_timechar, "%d", _time);
	sprintf(world, "1-%d", level);
	sprintf(_scoretxt, "000000");
	sprintf(_coinchar, "X 00");
	_coin = 0;

	_police = TTF_OpenFont("Police/police.ttf", 50);
	_currentCointxt = TTF_RenderText_Solid(_police, _coinchar, { 255, 255, 255 });
	_currentWorldtxt = TTF_RenderText_Solid(_police, world, { 255, 255, 255 });
	_currentScoretxt = TTF_RenderText_Solid(_police, _scoretxt, { 255, 255, 255 });
	_mariotxt = TTF_RenderText_Blended(_police, "MARIO", { 255, 255, 255 });
	_worldtxt = TTF_RenderText_Blended(_police, "WORLD", { 255, 255, 255 });
	_timetxt = TTF_RenderText_Blended(_police, "TIME", { 255, 255, 255 });
	_currentTimetxt = TTF_RenderText_Solid(_police, _timechar, { 255, 255, 255 });

	_score = 0;
}
Score::~Score(){ 
	TTF_CloseFont(_police);
}

void Score::display(SDL_Surface *screen){
	SDL_Rect pos = { 100, 0, 0, 0 };
	SDL_BlitSurface(_mariotxt, NULL, screen, &pos);
	pos.x = 800;
	SDL_BlitSurface(_worldtxt, NULL, screen, &pos);
	pos.x = 1200;
	SDL_BlitSurface(_timetxt, NULL, screen, &pos);
	pos.y += _timetxt->h - 20;
	pos.x += 15;
	SDL_BlitSurface(_currentTimetxt, NULL, screen, &pos);
	pos.x = 810;
	SDL_BlitSurface(_currentWorldtxt, NULL, screen, &pos);
	pos.x = 100;
	SDL_BlitSurface(_currentScoretxt, NULL, screen, &pos);
	pos.x = 470, pos.y = 20;
	SDL_BlitSurface(_currentCointxt, NULL, screen, &pos);
}

void Score::update(){
	_timer++;
	if (_timer % 50 == 0){
		_time--;
		if (_time >= 100)
			sprintf(_timechar, "%d", _time);
		else if (_time <= 99 && _time >= 10)
			sprintf(_timechar, "0%d", _time);
		else if (_time < 10)
			sprintf(_timechar, "00%d", _time);

		_currentTimetxt = TTF_RenderText_Solid(_police, _timechar, { 255, 255, 255 });
		_timer = 0;
	}
}

void Score::addScore(int score){ 
	_score += score;

	if (_score >= 100000)
		sprintf(_scoretxt, "%d", _score);
	else if (_score < 100000 && _score >= 10000)
		sprintf(_scoretxt, "0%d", _score);
	else if (_score < 10000 && _score >= 1000)
		sprintf(_scoretxt, "00%d", _score);
	else if (_score < 1000 && _score >= 100)
		sprintf(_scoretxt, "000%d", _score);
	else if (_score < 100 && _score >= 10)
		sprintf(_scoretxt, "0000%d", _score);
	else if (_score < 10)
		sprintf(_scoretxt, "00000%d", _score);

	_currentScoretxt = TTF_RenderText_Solid(_police, _scoretxt, { 255, 255, 255 });
}

void Score::addCoin(){ 
	_coin++;
	if (_coin < 10)
		sprintf(_coinchar, "X 0%d", _coin);
	else if (_coin >= 10)
		sprintf(_coinchar, "X %d", _coin);

	_currentCointxt = TTF_RenderText_Solid(_police, _coinchar, { 255, 255, 255 });
}