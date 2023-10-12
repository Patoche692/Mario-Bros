#include "Load.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK); // Initialisation de la SDL

	SDL_Surface *loadSurface = IMG_Load("Images/Load.png"), *rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 412, 104, 32, 0, 0, 0, 0),
		*menu = IMG_Load("Images/menu2.png"), *fondNoir = IMG_Load("Images/Fond_noir.png"), *rectangleMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, 512, 512, 32, 0, 0, 0, 0);
	SDL_Surface *ecran(SDL_SetVideoMode(50 * 32, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)); // Ouverture de la fenêtre
	SDL_Rect pos;
	Input input;


	pos.x = 0, pos.y = 0;
	int alphaVar = 1;
	SDL_BlitSurface(loadSurface, NULL, rectangle, &pos);
	SDL_BlitSurface(menu, NULL, rectangleMenu, &pos);
	pos.x = 800 - rectangle->w / 2 , pos.y = 450 - rectangle->h / 2;
	bool continuer(true);
	bool baisse = false;
	SDL_SetAlpha(rectangle, SDL_SRCALPHA | SDL_RLEACCEL, alphaVar);
	SDL_FreeSurface(loadSurface);
	SDL_FreeSurface(menu);
	TTF_Init();

	while (continuer)
	{
		SDL_SetAlpha(rectangle, SDL_SRCALPHA | SDL_RLEACCEL, alphaVar);

		if (!baisse){
			alphaVar++;
		}
		else
			alphaVar--;

		if (alphaVar >= 255)
			baisse = true;
		else if (alphaVar == 0)
			continuer = false;

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		SDL_BlitSurface(rectangle, NULL, ecran, &pos);
		SDL_Flip(ecran);

		SDL_Delay(5);
	}

	continuer = true;
	alphaVar = 0;
	pos.x = 800 - rectangleMenu->w / 2, pos.y = 450 - rectangleMenu->h / 2;
	bool endAnim = false;

	while (continuer){
		if (alphaVar < 250)
			alphaVar+=10;

		endAnim = false;

		SDL_SetAlpha(rectangleMenu, SDL_SRCALPHA | SDL_RLEACCEL, alphaVar);

		input.update_events();

		if (input.isPressed(SDLK_ESCAPE))
			continuer = false;

		else if (input.isPressed(SDLK_SPACE)){

			alpha1(ecran, rectangleMenu, 1);
			input.setPressed(SDLK_SPACE, false);
			play(ecran);
			alpha1(ecran, rectangleMenu, 2);
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		SDL_BlitSurface(rectangleMenu, NULL, ecran, &pos);
		SDL_Flip(ecran);

		SDL_Delay(5);

	}

	SDL_FreeSurface(rectangle);
	SDL_Quit(); // Arrêt de la SDL
	TTF_Quit();

	return EXIT_SUCCESS;
}

void alpha1(SDL_Surface *ecran, SDL_Surface *surface, int flag)
{

	SDL_Rect pos;
	pos.x = 800 - surface->w / 2, pos.y = 450 - surface->h / 2;

	int alpha;
	if (flag == 1){
		alpha = 250;
		while (alpha > 0){
			alpha -= 10;
			SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
			SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
			SDL_BlitSurface(surface, NULL, ecran, &pos);
			SDL_Flip(ecran);
			SDL_Delay(4);
		}
	}
	else{
		alpha = 5;
		while (alpha < 255){
			alpha += 10;
			SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
			SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
			SDL_BlitSurface(surface, NULL, ecran, &pos);
			SDL_Flip(ecran);
			SDL_Delay(4);
		}
	}
 
}  
