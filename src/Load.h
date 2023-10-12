#ifndef DEF_LOAD
#define DEF_LOAD

#include "Input.h"
#include "game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>


void audioCallback(void *udata, Uint8 *stream, int len);
void alpha1(SDL_Surface *ecran, SDL_Surface *surface, int flag);
SDL_AudioSpec audioSortie;

#endif