#include "game.h"


const int frameRate = 7;

void play(SDL_Surface *ecran)
{

	bool continuer(true), endGame(false), win(true);
	int level = 1;
	SDL_Surface *black = IMG_Load("Images/Fond_noir.png");

	int time = 0;
	Mario mario(level);


	while (!endGame){
		SDL_Surface *back;

		if (level == 1 || level == 3)
			back = IMG_Load("Images/fond_3.gif");
		else
			back = IMG_Load("Images/fond_2.gif");

		continuer = true;
		win = true;
		Sounds sounds;
		Map map;
		Input input;
		map.load(level);
		mario.newFA(level);
		Goomba goomba(&map, level);
		SDL_Rect targetPos = map.getTargetPos();
		Target target(targetPos.x, targetPos.y);
		Score score(level);

		goomba.find(&map);
		targetPos = map.getXCastle();
		mario.setClearPos(targetPos);
		mario.set_continuer(&continuer, &win);
		mario.init(map.getMarioX() * SIZE_TILES, mario.getSize() == 0 ? map.getMarioY() * SIZE_TILES : map.getMarioY() * SIZE_TILES - 34);
		mario.setSounds(&sounds);
		map.set_mat(map.getMarioX(), map.getMarioY(), 0);
		alpha(ecran, black, 1, level);
		sounds.playTheme(MAIN);

		int startTime(0), lastTime(0), offset(0), timer(0);

		while (continuer)
		{
			startTime = SDL_GetTicks();

			int dirAnim = 2;
			goomba.setMap(&map);
			mario.setMap(&map);
			mario.set_goomba(&goomba);
			mario.updateLastPos();
			input.update_events();
			score.update();

			if (input.isPressed(SDLK_ESCAPE))
				continuer = false, endGame = true;

			if (input.isPressed(SDLK_LSHIFT))
				mario.setSpeed(4);
			else
				mario.setSpeed(3);

			if (input.isPressed(SDLK_SPACE)){
				if (!input.get_space_pressed() && !mario.getJumping()){
					sounds.playSound(JUMP);
					input.set_space_pressed(true);
					mario.set_start_time(SDL_GetTicks());
					mario.set_current_time(SDL_GetTicks());
					mario.setJumping(true);
					if (input.get_right_pressed2())
						mario.setCurrent(mario.getSurface(DROITE, 4));
					else
						mario.setCurrent(mario.getSurface(GAUCHE, 4));
				}
				else if (mario.get_offset() <= 300 && input.get_space_pressed()){
					mario.set_current_time(SDL_GetTicks());
					if (input.get_right_pressed2())
						mario.setCurrent(mario.getSurface(DROITE, 4));
					else
						mario.setCurrent(mario.getSurface(GAUCHE, 4));
				}
				else if (mario.get_offset() > 300 && input.get_space_pressed()){
					input.setPressed(SDLK_SPACE, false);
					input.set_space_pressed(false);
				}

			}

			else if (!input.isPressed(SDLK_SPACE)){
				input.set_space_pressed(false);
			}

			if (input.isPressed(SDLK_d)){
				input.set_right_pressed2(true);
				input.set_left_pressed2(false);
				if (mario.getX() + 31 > 1600 - mario.getSpeed()){
					mario.setX(1550);
					map.setScrolling(false);
				}
				else if (mario.getX() < 750 || map.getXScroll() >= WIDTH_MAP * SIZE_TILES - 16 * SIZE_TILES){
					mario.setX(mario.getX() + mario.getSpeed());
					map.setScrolling(false);
				}
				else if (mario.getX() >= 750){
					map.setScrolling(true);
					map.setXScroll(map.getXScroll() + mario.getSpeed());
					mario.setX(750);
				}

				if (!mario.getJumping()){
					mario.anim(DROITE);
					input.set_right_pressed(true);
				}
				else
					mario.setCurrent(mario.getSurface(DROITE, 4));
			}

			if (input.isPressed(SDLK_a)){
				input.set_right_pressed2(false);
				input.set_left_pressed2(true);
				if (mario.getX() < mario.getSpeed()){
					mario.setX(0);
					map.setScrolling(false);
				}
				else if (mario.getX() > 300 || map.getXScroll() <= 0){
					mario.setX(mario.getX() - mario.getSpeed());
					map.setScrolling(false);
				}
				else if (mario.getX() <= 300 || map.getXScroll() > 0){
					map.setScrolling(true);
					mario.setX(300);
					map.setXScroll(map.getXScroll() - mario.getSpeed());
				}

				if (!mario.getJumping()){
					mario.anim(GAUCHE);
					input.set_left_pressed(true);
				}
				else
					mario.setCurrent(mario.getSurface(GAUCHE, 4));
			}
			if (!input.isPressed(SDLK_d) && !input.isPressed(SDLK_a)){
				if (input.get_left_pressed() == true){
					mario.setCurrent(mario.getSurface(GAUCHE, 0));
					input.set_left_pressed(false);
				}
				else if (input.get_right_pressed() == true){
					mario.setCurrent(mario.getSurface(DROITE, 0));
					input.set_right_pressed(false);
				}
			}

			if (mario.getJumping()){
				mario.jump();
			}

			else
				input.set_space_pressed(false);

			mario.update(&input, target, &score);
			goomba.update();

			if (mario.getCollideUp()){
				input.set_space_pressed(false);
				mario.setCollideUp(false);
			}

			SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 128, 168, 248));
			dispBack(ecran, map.getXScroll(), back);
			mario.dispMush(ecran);
			goomba.display(ecran);
			map.display(ecran);
			mario.display(ecran);
			target.display(ecran, map.getXScroll());
			mario.dispOther(ecran);
			mario.dispFire(ecran);
			score.display(ecran);
			SDL_Flip(ecran);

			lastTime = SDL_GetTicks();

			if (lastTime - startTime < frameRate)
				SDL_Delay(frameRate - lastTime + startTime);
			else if (lastTime - startTime > frameRate)
				cout << "too low : " << lastTime - startTime << endl;
		}
		if (win){
			level++;
		}
		SDL_FreeSurface(back);
		alpha(ecran, black, 2, level);
	}


	SDL_FreeSurface(black);
}

void alpha(SDL_Surface *ecran, SDL_Surface *surface, int flag, int level)
{
	Map map;
	map.load(level);
	Mario mario(level);
	Input input;
	SDL_Rect pos;
	pos.x = 0, pos.y = 0;
	mario.setMap(&map);
	SDL_Surface *back = level == 1 ? IMG_Load("Images/fond_3.gif") : level == 2 ? IMG_Load("Images/fond_2.gif") : IMG_Load("Images/fond_3.gif");

	mario.setX(map.getMarioX() * SIZE_TILES);
	mario.setY(map.getMarioY() * SIZE_TILES);

	int alpha;
	if (flag == 1){
		alpha = 250;
		while (alpha > 0){
			alpha -= 10;
			SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
			SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
			dispBack(ecran, map.getXScroll(), back);
			map.display(ecran);
			mario.display(ecran);
			SDL_BlitSurface(surface, NULL, ecran, &pos);
			SDL_Flip(ecran);
			SDL_Delay(4);
		}
	}
	else{
		alpha = 30;
		int time = 0;
		while (time < 20){
			time++;
			SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
			SDL_BlitSurface(surface, NULL, ecran, &pos);
			SDL_Flip(ecran);
			SDL_Delay(4);
		}
	}
	SDL_FreeSurface(back);
}

void dispBack(SDL_Surface *screen, int Xscroll, SDL_Surface *background){
	SDL_Rect pos;
	for (int i = Xscroll / 1800; i < Xscroll / 1800 + 3; ++i){
		pos.x = i * 900 - Xscroll / 2, pos.y = 0;
		SDL_BlitSurface(background, NULL, screen, &pos);
	}
}