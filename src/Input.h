#ifndef DEF_INPUT
	
#define DEF_INPUT

#define NUMBER_EVENTS 322

#include <SDL.h>
#include <iostream>

using namespace std;

class Input
{

private:
	bool m_events[NUMBER_EVENTS];
	SDL_Joystick *m_joystick;
	SDL_Event m_event;
	bool leftPressed, rightPressed, spacePressed, leftSide, rightSide;
public:
	Input();
	~Input();
	void set_right_pressed(bool a);
	void set_left_pressed(bool a);
	void set_right_pressed2(bool a);
	void set_left_pressed2(bool a);
	bool get_right_pressed();
	bool get_left_pressed();
	bool get_right_pressed2();
	bool get_left_pressed2();
	void update_events();
	bool isPressed(int key);
	void set_space_pressed(bool a);
	bool get_space_pressed();
	void setPressed(int key, bool tf);
};

#endif // !DEF_INPUT
