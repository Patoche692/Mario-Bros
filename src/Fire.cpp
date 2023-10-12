#include "Fire.h"

int Fire::get_nb(){ return m_nb; }

Fire::Fire(){
	m_nb = 0;
	m_images[0] = IMG_Load("Images/Fire-1.gif");
	m_images[1] = IMG_Load("Images/Fire-2.gif");
	m_images[2] = IMG_Load("Images/Fire-3.gif");
	m_images[3] = IMG_Load("Images/Fire-4.gif");
	m_images[4] = IMG_Load("Images/Fire-5.gif");
	m_images[5] = IMG_Load("Images/Fire-6.gif");
}

Fire::~Fire(){
	for (int i = 0; i < 6; ++i){
		SDL_FreeSurface(m_images[i]);
	}
}

void Fire::update(Goomba *goomba, Map *map, Sounds *sounds){
	m_timer++;
	bool supress(false);
	SDL_Rect posF;

	if (m_timer % 2 == 0){
		for (int i = 0; i < m_nb; ++i){

			supress = false;

			if (m_timer % 22 == 0){
				m_timer = 0;
				m_current[i] = m_current[i] <= 2 ? m_current[i] + 1 : 0;
			}

			if (!m_explode[i]){
				m_pos[i].x += m_xspeed[i];
				m_posRelX[i] += 5;
				int aposY = m_pos[i].y - (int)m_posRelY[i];
				m_posRelY[i] = m_posRelX[i] * m_posRelX[i] * (-0.01) + 1.2 * m_posRelX[i];

				posF.x = m_pos[i].x, posF.y = m_pos[i].y - m_posRelY[i];
				int dpl = -aposY + ((int)posF.y);

				for (int j = 0; j < goomba->get_nb(); ++j){
					if (!goomba->is_hurt(j) && !goomba->isDied(j)){
						int sgy = goomba->getType(j) == GOOMBAT ? 49 : 74;
						if ((posF.x + 20 >= goomba->getX(j) && posF.x <= goomba->getX(j) + 45 && posF.y + 20 >= goomba->getY(j) && posF.y <= goomba->getY(j) + sgy)){
							goomba->setDied(j);
							supress = true;
							continue;
						}
					}
				}
				if (supress){
					m_explode[i] = 1;
					sounds->playSound(KICK);
					continue;
				}

				/*else if (posF.y <= m_starty[i]){
					m_yspeed[i] *= -1;
				}*/

				else if (((map->get_mat(posF.x / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 0 && map->get_mat(posF.x / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 19))
					&& ((map->get_mat(posF.x / SIZE_TILES, (posF.y + 24 - dpl) / SIZE_TILES) == 0 || map->get_mat(posF.x / SIZE_TILES, (posF.y + 24 - dpl) / SIZE_TILES) == 19))){
					m_pos[i].y = (m_pos[i].y - (int)m_posRelY[i]) * 50 / 50 - 25;
					cout << "yes1 :" << m_posRelX[i];
					m_posRelX[i] = 0;
					m_posRelY[i] = 0;
				}
				else if ((map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 19 && map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 0) &&
					(map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + 24 - dpl) / SIZE_TILES) == 19 || map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + 24 - dpl) / SIZE_TILES) == 0)){
					m_pos[i].y = (m_pos[i].y - (int)m_posRelY[i]) * 50 / 50 - 25;
					m_posRelX[i] = 0;
					m_posRelY[i] = 0;
					cout << "yes2 :" << m_posRelX[i];
				}

				/*else if (((map->get_mat(posF.x / SIZE_TILES, (posF.y) / SIZE_TILES) != 0 && map->get_mat(posF.x / SIZE_TILES, (posF.y) / SIZE_TILES) != 19))
					&& ((map->get_mat((posF.x) / SIZE_TILES, (posF.y + dpl) / SIZE_TILES) == 0 || map->get_mat((posF.x) / SIZE_TILES, (posF.y + dpl) / SIZE_TILES) == 19))){
					m_yspeed[i] *= -1;
				}

				else if ((map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y) / SIZE_TILES) != 19 && map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y) / SIZE_TILES) != 0) &&
					(map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + dpl) / SIZE_TILES) == 19 || map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + dpl) / SIZE_TILES) == 0)){
					m_yspeed[i] *= -1;
				}
				*/
				else if ((map->get_mat((posF.x + 24) / SIZE_TILES, posF.y / SIZE_TILES) != 0 && map->get_mat((posF.x + 24) / SIZE_TILES, posF.y / SIZE_TILES) != 19)
					|| (map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 0 && map->get_mat((posF.x + 24) / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 19)){
					m_explode[i] = 1;
					sounds->playSound(COLLIDE);
					continue;
				}
				else if ((map->get_mat(posF.x / SIZE_TILES, posF.y / SIZE_TILES) != 0 && map->get_mat(posF.x / SIZE_TILES, posF.y / SIZE_TILES) != 19)
					|| ((map->get_mat(posF.x / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 0 && map->get_mat(posF.x / SIZE_TILES, (posF.y + 24) / SIZE_TILES) != 19))){
					m_explode[i] = 1;
					sounds->playSound(COLLIDE);
					continue;
				}
				else if (posF.x < 0 || posF.x + 24 - map->getXScroll() > 1600 || posF.y < 0 || posF.y + 24 > 900 || posF.x - map->getXScroll() < 0){
					m_explode[i] = 1;
					sounds->playSound(COLLIDE);
					continue;
				}
			}
		}
	}
}

void Fire::display(SDL_Surface *screen, int xscroll){
	SDL_Rect pos;
	if (m_nb){
		for (int i = 0; i < m_nb; ++i){
			if (m_explode[i]){
				m_current[i] = 4;
				m_time[i]++;
				if (m_time[i] >= 7){
					m_current[i] = 5;
				}
				if (m_time[i] == 20){
					supressAll(i);
					i--;
					continue;
				}
			}

			pos = { m_pos[i].x - xscroll, m_pos[i].y - m_posRelY[i], 0, 0 };
			SDL_BlitSurface(m_images[m_current[i]], NULL, screen, &pos);
		}
	}
}

void Fire::add(int x, int y, Input *input){
	m_nb++;
	SDL_Rect pos;
	pos.x = (input->get_right_pressed2() ? x + SIZE_TILES - 10 : x - 12);
	pos.y = y + 30;
	m_pos.push_back(pos);
	m_posRelX.push_back(72.5);
	m_posRelY.push_back(m_posRelX[m_posRelX.size() - 1] * m_posRelX[m_posRelX.size() - 1] * (-0.01) + 1 * m_posRelX[m_posRelX.size() - 1]);
	m_xspeed.push_back(input->get_right_pressed2() ? 14 : -14);
	m_yspeed.push_back(4);
	m_starty.push_back(y + 16);
	m_current.push_back(0);
	m_explode.push_back(0);
	m_time.push_back(0);
}

void Fire::supressAll(int i){
	m_pos.erase(m_pos.begin() + i);
	m_xspeed.erase(m_xspeed.begin() + i);
	m_yspeed.erase(m_yspeed.begin() + i);
	m_starty.erase(m_starty.begin() + i);
	m_current.erase(m_current.begin() + i);
	m_explode.erase(m_explode.begin() + i);
	m_time.erase(m_time.begin() + i);
	m_posRelX.erase(m_posRelX.begin() + i);
	m_posRelY.erase(m_posRelY.begin() + i);
	m_nb--;
}

int Fire::getX(int i){ return m_pos[i].x; }
int Fire::getY(int i){ return m_pos[i].y - m_posRelY[i]; }
void Fire::setExplode(int i){ m_explode[i] = 1; }

