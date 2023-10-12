#include "Sounds.h"

Sounds::Sounds(){

	FMOD_System_Create(&m_mainSystem);
	FMOD_System_Init(m_mainSystem, 1, FMOD_INIT_NORMAL, NULL);

	for (int i = 0; i < NB_SOUNDS; ++i){
		FMOD_System_Create(&m_system[i]);
		FMOD_System_Init(m_system[i], 1, FMOD_INIT_NORMAL, NULL);
	}

	FMOD_System_CreateSound(m_mainSystem, "Sons/Super Mario Bros medley.wav", FMOD_LOOP_NORMAL, 0, &m_Theme[MAIN]);
	FMOD_System_CreateSound(m_mainSystem, "Sons/mariodie.wav", FMOD_CREATESAMPLE, 0, &m_Theme[DIE]);
	FMOD_System_CreateSound(m_mainSystem, "Sons/stage_clear.wav", FMOD_CREATESAMPLE, 0, &m_Theme[WIN]);

	FMOD_System_CreateSound(m_system[JUMP], "Sons/jump-small.wav", FMOD_CREATESAMPLE, 0, &m_sounds[JUMP]);
	FMOD_System_CreateSound(m_system[COIN], "Sons/coin.wav", FMOD_CREATESAMPLE, 0, &m_sounds[COIN]);
	FMOD_System_CreateSound(m_system[KICK], "Sons/stomp.wav", FMOD_CREATESAMPLE, 0, &m_sounds[KICK]);
	FMOD_System_CreateSound(m_system[FIREBALL], "Sons/fireball.wav", FMOD_CREATESAMPLE, 0, &m_sounds[FIREBALL]);
	FMOD_System_CreateSound(m_system[COLLIDE], "Sons/bump.wav", FMOD_CREATESAMPLE, 0, &m_sounds[COLLIDE]);
	FMOD_System_CreateSound(m_system[BREAK], "Sons/breakblock.wav", FMOD_CREATESAMPLE, 0, &m_sounds[BREAK]);
	FMOD_System_CreateSound(m_system[GROWS], "Sons/powerup.wav", FMOD_CREATESAMPLE, 0, &m_sounds[GROWS]);

	FMOD_Sound_SetLoopCount(m_Theme[0], -1);
}

Sounds::~Sounds(){

	for (int i = 0; i < NB_SOUNDS; ++i){
		FMOD_Sound_Release(m_sounds[i]);
		FMOD_System_Close(m_system[i]);
		FMOD_System_Release(m_system[i]);
	}
	for (int i = 0; i < NB_THEME; ++i){
		FMOD_Sound_Release(m_Theme[i]);
	}
	FMOD_System_Close(m_mainSystem);
	FMOD_System_Release(m_mainSystem);
}

void Sounds::playSound(int pos){
	FMOD_System_PlaySound(m_system[pos], FMOD_CHANNEL_FREE, m_sounds[pos], 0, NULL);
}

void Sounds::playTheme(int pos){
	if (pos == MAIN){
		FMOD_CHANNEL *channel;
		FMOD_System_PlaySound(m_mainSystem, FMOD_CHANNEL_FREE, m_Theme[pos], 0, &channel);
		FMOD_Channel_SetVolume(channel, 0.5);
	}
	else
		FMOD_System_PlaySound(m_mainSystem, FMOD_CHANNEL_FREE, m_Theme[pos], 0, NULL);
}

void Sounds::setThemePause(){
	FMOD_ChannelGroup_SetPaused(canal, 1);
}