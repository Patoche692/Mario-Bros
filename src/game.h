#ifndef DEF_MAIN

#define DEF_MAIN

#include <fmod.h>
#include <SDL_ttf.h>
#include "Input.h"
#include "Score.h"
#include "Mario.h"
#include "Map.h"
#include "Goomba.h"
#include "Sounds.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>


enum{ DROITE, GAUCHE };
void pause();
void play(SDL_Surface *ecran);
void alpha(SDL_Surface *ecran, SDL_Surface *surface, int flag, int level);
void dispBack(SDL_Surface *screen, int Xscroll, SDL_Surface *background);
#endif // !DEF_MAIN

