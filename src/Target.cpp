#include "Target.h"

Target::Target(int x, int y){
	m_surf = IMG_Load("Images/cible.gif");
	m_pos.x = x, m_pos.y = y;
	m_speedY = 2;
	m_isHurt = false;
}

Target::~Target(){
	SDL_FreeSurface(m_surf);
}

void Target::update(Map *map, Fire *fire, Sounds *sounds){
	if (!m_isHurt){
		m_pos.y += m_speedY;

		if (m_pos.y < 0 || m_pos.y + 64 >= 18 * SIZE_TILES)
			m_speedY *= -1;

		else if (map->get_mat(m_pos.x / SIZE_TILES, m_pos.y / SIZE_TILES) != 0 && map->get_mat(m_pos.x / SIZE_TILES, m_pos.y / SIZE_TILES) != 19)
			m_speedY *= -1;

		else if (map->get_mat(m_pos.x / SIZE_TILES, (m_pos.y + 63) / SIZE_TILES) != 0 && map->get_mat(m_pos.x / SIZE_TILES, (m_pos.y + 63) / SIZE_TILES) != 19)
			m_speedY *= -1;

		for (int i = 0; i < fire->get_nb(); i++){
			if (fire->getX(i) + 6 >= m_pos.x + 20 && fire->getX(i) <= m_pos.x + 43 && fire->getY(i) + 11 >= m_pos.y && fire->getY(i) <= m_pos.y + 63){
				fire->setExplode(i);
				sounds->playSound(COLLIDE);
				m_isHurt = true;
			}
		}
	}
}

void Target::display(SDL_Surface *screen, int Xscroll){
	if (!m_isHurt){
		SDL_Rect pos = { m_pos.x - Xscroll, m_pos.y, 0, 0 };
		SDL_BlitSurface(m_surf, NULL, screen, &pos);
	}
}