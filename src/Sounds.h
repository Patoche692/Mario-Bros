#ifndef DEF_SOUNDS
#define DEF_SOUNDS

#include <fmod.h>
#include <SDL.h>
#include <iostream>

#define NB_SOUNDS (7)
#define NB_THEME (3)
enum{ JUMP, COIN, KICK, FIREBALL, COLLIDE, BREAK, GROWS };
enum{ MAIN, DIE, WIN };
enum{THEMES, SOUNDS};

class Sounds{
private:
	FMOD_SOUND *m_sounds[NB_SOUNDS], *m_Theme[NB_THEME];
	FMOD_SYSTEM *m_system[NB_SOUNDS], *m_mainSystem;
	FMOD_CHANNELGROUP *canal;
public:
	Sounds();
	~Sounds();
	void playSound(int pos);
	void playTheme(int pos);
	void setThemePause();
};

#endif