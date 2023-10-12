#include "Input.h"

Input::Input()
{
	for (int i = 0; i < NUMBER_EVENTS; ++i){
		m_events[i] = false;
	}
	m_joystick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
	rightPressed = false, leftPressed = false, spacePressed = false, rightSide = true, leftSide = false;
}

bool Input::isPressed(int key)
{
	return (m_events[key] == true ? true : false);
}

void Input::update_events()
{

	while (SDL_PollEvent(&m_event))
	{
		if (!SDL_NumJoysticks()){
			if (m_event.type == SDL_KEYDOWN)
				m_events[m_event.key.keysym.sym] = true;

			else if (m_event.type == SDL_KEYUP)
				m_events[m_event.key.keysym.sym] = false;
		}

		else{
			if (m_event.type == SDL_JOYBUTTONDOWN){
				switch (m_event.jbutton.button){
				case 0:
					m_events[SDLK_SPACE] = 1;
					break;
				case 4:
					m_events[SDLK_LSHIFT] = 1;
					break;
				case 6:
					m_events[SDLK_ESCAPE] = 1;
					break;
				}
			}
			else if (m_event.type == SDL_JOYBUTTONUP){
				switch (m_event.jbutton.button){
				case 0:
					m_events[SDLK_SPACE] = 0;
					break;
				case 4:
					m_events[SDLK_LSHIFT] = 0;
					break;
				case 6:
					m_events[SDLK_ESCAPE] = 0;
					break;
				}
			}

			else if (m_event.type == SDL_JOYAXISMOTION){
				if (m_event.jaxis.axis == 0 && m_event.jaxis.value < -20000){
					m_events[SDLK_a] = 1;
				}
				else if (m_event.jaxis.axis == 0 && m_event.jaxis.value > 20000)
					m_events[SDLK_d] = 1;

				else if (m_event.jaxis.axis == 0 && m_event.jaxis.value < 20000 && m_event.jaxis.value > -20000){
					m_events[SDLK_a] = 0;
					m_events[SDLK_d] = 0;
				}
				else if (m_event.jaxis.axis == 2 && m_event.jaxis.value == -32640)
					m_events[SDLK_s] = 1;
				else if (m_event.jaxis.axis == 0 && m_event.jaxis.value < 32640 && m_event.jaxis.value > -32640)
					m_events[SDLK_s] = 0;
			}
		}
	}
}

Input::~Input(){ /*SDL_JoystickClose(m_joystick);*/ }

void Input::set_right_pressed(bool a){ rightPressed = a; }
void Input::set_left_pressed(bool a){ leftPressed = a; }
bool Input::get_left_pressed(){ return leftPressed; }
bool Input::get_right_pressed(){ return rightPressed; }
void Input::set_right_pressed2(bool a){ rightSide = a; }
void Input::set_left_pressed2(bool a){ leftSide = a; }
bool Input::get_left_pressed2(){ return leftSide; }
bool Input::get_right_pressed2(){ return rightSide; }
void Input::set_space_pressed(bool a){ spacePressed = a; }
bool Input::get_space_pressed(){ return spacePressed; }
void Input::setPressed(int key, bool tf){ m_events[key] = tf; }