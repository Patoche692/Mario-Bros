#include "Goomba.h"

int Goomba::is_hurt(int i){ return m_hurt[i]; }
void Goomba::set_hurt(int i, int j){ 
	m_hurt[i] = j; 
	if (m_type[i] == 1 && j == 1)
		m_pos[i].y += 31;
}
int Goomba::get_nb(){ return m_nb; }
void Goomba::set_current(int i, int j){ m_currentImage[i] = j; }
int Goomba::getX(int i){ return m_pos[i].x; }
int Goomba::getY(int i){ return m_pos[i].y - m_posJY[i]; }
void Goomba::setX(int i, int x){ m_pos[i].x = x; }
void Goomba::setY(int i, int y){ m_pos[i].y = y; }
void Goomba::setMap(Map *map){ m_map = map; }
void Goomba::setDied(int i){ m_died[i] = 1; }
int Goomba::isDied(int i){ return m_died[i]; }
int Goomba::getType(int pos){ return m_type[pos]; }
void Goomba::setMoving(int i, int j){ m_isMoving[i] = j; }
int Goomba::getMoving(int i){ return m_isMoving[i]; }
void Goomba::setSpeed(int i, int j){ m_speed[i] = j; }

void Goomba::find(Map *map){
	pos pos;
	setMap(map);
	m_nb = 0;
	for (int i = 0; i < WIDTH_MAP; ++i){
		for (int j = 0; j < HEIGHT_MAP; ++j){
			if (map->get_mat(i, j) >= 23 && map->get_mat(i, j) <= 25){
				m_type.push_back(map->get_mat(i, j) == 23 ? 0 : (map->get_mat(i, j) == 24 ? 1 : 2));
				pos.x = i * SIZE_TILES + (m_type[m_type.size() - 1] == 2 ? 25 : 0);
				pos.y = j * SIZE_TILES - (m_type[m_type.size() - 1] == 0 ? 0 : (m_type[m_type.size() - 1] == 1 ? 25 : -50));
				map->set_mat(i, j, 0);
				m_pos.push_back(pos);
				m_died.push_back(0);
				m_speed.push_back(-0.7);
				m_hurt.push_back(0);
				m_timerInd.push_back(0);
				m_currentImage.push_back(0);
				m_posRelY.push_back(0);
				m_posJY.push_back(0);
				m_posJX.push_back(0.0);
				m_isJumping.push_back(false);
				m_lastY.push_back(0);
				m_detected.push_back(false);
				m_isMoving.push_back(m_type[m_type.size() - 1] == 2 ? 1 : 0);
				m_nb++;
			}
		}
	}
}

Goomba::Goomba(Map *map, int level){ 

	if (level == 1 || level >= 3){
		m_images[0][0] = IMG_Load("Images/Goomba_1.gif");
		m_images[0][1] = IMG_Load("Images/Goomba_2.gif");
		m_images[0][2] = IMG_Load("Images/Goomba_1.gif");
		m_images[0][3] = IMG_Load("Images/Goomba_2.gif");
		m_images[0][4] = IMG_Load("Images/Goomba_3.gif");
		m_images[0][5] = IMG_Load("Images/Goomba_4.gif");
		m_images[1][0] = IMG_Load("Images/koopa-gauche1.gif");
		m_images[1][1] = IMG_Load("Images/koopa-gauche2.gif");
		m_images[1][2] = IMG_Load("Images/koopa-droite1.gif");
		m_images[1][3] = IMG_Load("Images/koopa-droite1.gif");
		m_images[1][4] = IMG_Load("Images/koopa-5.gif");
		m_images[1][5] = IMG_Load("Images/koopa-6.gif");
		m_images[2][0] = IMG_Load("Images/carn-1.gif");
		m_images[2][1] = IMG_Load("Images/carn-2.gif");
	}
	else{
		m_images[0][0] = IMG_Load("Images/Goomba_1B.gif");
		m_images[0][1] = IMG_Load("Images/Goomba_2B.gif");
		m_images[0][2] = IMG_Load("Images/Goomba_1B.gif");
		m_images[0][3] = IMG_Load("Images/Goomba_2B.gif");
		m_images[0][4] = IMG_Load("Images/Goomba_3B.gif");
		m_images[0][5] = IMG_Load("Images/Goomba_4B.gif");
		m_images[1][0] = IMG_Load("Images/koopa-gauche1.gif");
		m_images[1][1] = IMG_Load("Images/koopa-gauche2.gif");
		m_images[1][2] = IMG_Load("Images/koopa-droite1.gif");
		m_images[1][3] = IMG_Load("Images/koopa-droite1.gif");
		m_images[1][4] = IMG_Load("Images/koopa-5.gif");
		m_images[1][5] = IMG_Load("Images/koopa-6.gif");
		m_images[2][0] = IMG_Load("Images/carn-1.gif");
		m_images[2][1] = IMG_Load("Images/carn-2.gif");
	}
	m_timer = 0;

}

Goomba::~Goomba(){
	for (int k = 0; k < 3; ++k)
		for (int i = 0; i < 6; ++i)
			SDL_FreeSurface(m_images[k][i]);

}


void Goomba::update(){
	if (m_nb != 0){
		SDL_Rect posG;
		m_timer++;
		int sy;
		for (int i = 0; i < m_nb; ++i){
			if (!m_detected[i] && m_pos[i].x <= m_map->getXScroll() + 32 * 50 && m_pos[i].x + 49 >= m_map->getXScroll()){
				m_detected[i] = true;
			}

			if (m_hurt[i] && !m_type[i]){
				m_timerInd[i]++;
				if (m_timerInd[i] >= 60){
					supressAll(i);
					if (i == m_nb){
						continue;
					}
				}
			}
			else if (m_died[i]){
				m_currentImage[i] = 5;
				m_timerInd[i] += 1;
				m_posRelY[i] = m_timerInd[i] * m_timerInd[i] * -0.04 + 2 * m_timerInd[i];
				if (m_pos[i].y - m_posRelY[i] >= 900)
					supressAll(i);
				if (i == m_nb){
					continue;
				}
			}

			if (m_timer % 22 == 0 && !m_died[i]){
				if (m_hurt[i])
					m_currentImage[i] = 4;
				else if (m_currentImage[i] == 1 || m_currentImage[i] == 3)
					m_currentImage[i]--;
				else if (m_currentImage[i] == 0 || m_currentImage[i] == 2)
					m_currentImage[i]++;

				m_timer = 0;
			}

			if (((!m_hurt[i] && !m_died[i] && m_detected[i]) || (m_type[i] == 1 && m_isMoving[i])) && m_type[i] != 2){
				sy = m_type[i] == 0 ? 49 : m_hurt[i] ? 43 : 74;
				m_lastY[i] = m_pos[i].y - m_posJY[i];
				m_pos[i].x += m_speed[i];
				if (m_isJumping[i]){
					m_posJX[i] += 2.2;
					m_posJY[i] = (int)(m_posJX[i] * m_posJX[i] * (-0.01) + 3 * m_posJX[i] - 225);
				}
				posG.x = m_pos[i].x, posG.y = m_pos[i].y - m_posJY[i];
				int dpl = posG.y - m_lastY[i];

				if (m_type[i] != 2){
					int sdy;
					for (int j = 0; j < m_type.size(); ++j){
						if (!m_isMoving[j] && !m_hurt[j] && !m_died[j]){
							sdy = m_type[j] == 0 ? 49 : m_hurt[j] ? 43 : 74;
							if (posG.x + 49 >= m_pos[j].x && posG.x <= m_pos[j].x + 49
								&& posG.y + sdy >= m_pos[j].y - m_posJY[j] && posG.y <= m_pos[j].y - m_posJY[j] + sy){
								if (m_isMoving[i])
									m_died[j] = 1;
								else{
									m_speed[i] *= -1;
									m_speed[j] *= -1;
								}
							}
						}
					}
				}

				if ((m_map->get_mat(posG.x / SIZE_TILES, posG.y / SIZE_TILES) != 0 &&
					m_map->get_mat(posG.x / SIZE_TILES, posG.y / SIZE_TILES) != 19 &&
					(m_map->get_mat((posG.x + m_speed[i]) / SIZE_TILES, posG.y / SIZE_TILES) == 0 ||
					m_map->get_mat((posG.x + m_speed[i]) / SIZE_TILES, posG.y / SIZE_TILES) != 19)) || posG.x < 0){
					m_speed[i] *= -1;
					m_pos[i].x = (int)(m_pos[i].x) / SIZE_TILES * SIZE_TILES + (m_pos[i].x >= 0 ? SIZE_TILES : 0);
					posG.x = m_pos[i].x, posG.y = m_pos[i].y - m_posJY[i];
					if (m_speed[i] < 0 && !m_hurt[i])
						m_currentImage[i] = 0;
					else if (!m_hurt[i])
						m_currentImage[i] = 2;
				}

				else if ((m_map->get_mat((posG.x + 49) / SIZE_TILES, posG.y / SIZE_TILES) != 0 &&
					m_map->get_mat((posG.x + 49) / SIZE_TILES, posG.y / SIZE_TILES) != 19 &&
					(m_map->get_mat((posG.x + 49 - m_speed[i]) / SIZE_TILES, posG.y / SIZE_TILES) == 0 ||
					m_map->get_mat((posG.x + 49 - m_speed[i]) / SIZE_TILES, posG.y / SIZE_TILES) == 19)) || posG.x + SIZE_TILES > WIDTH_MAP * SIZE_TILES){
					m_speed[i] *= -1;
					m_pos[i].x = (int)(m_pos[i].x) / SIZE_TILES * SIZE_TILES;
					posG.x = m_pos[i].x, posG.y = m_pos[i].y - m_posJY[i];
					if (m_speed[i] < 0 && !m_hurt[i])
						m_currentImage[i] = 0;
					else if (!m_hurt[i])
						m_currentImage[i] = 2;
				}

				else if (!m_isJumping[i] && (m_map->get_mat(posG.x / 50, (posG.y + (sy - 49)) / 50 + 1) == 0 ||
					m_map->get_mat((posG.x + (sy - 49)) / 50, posG.y / 50 + 1) == 19) &&
					(m_map->get_mat((posG.x + (sy - 49) + 49) / 50, posG.y / 50 + 1) == 0 ||
					m_map->get_mat((posG.x + (sy - 49) + 49) / 50, posG.y / 50 + 1) == 19)){
					m_isJumping[i] = true;
					m_posJX[i] = 150;
				}
				if (m_isJumping[i] && (m_map->get_mat(posG.x / 50, (posG.y + sy) / 50) != 0 &&
					m_map->get_mat(posG.x / 50, (posG.y + sy) / 50) != 19) &&
					(m_map->get_mat(posG.x / 50, (posG.y + sy - dpl) / 50) == 0 ||
					m_map->get_mat(posG.x / 50, (posG.y + sy - dpl) / 50) == 19)){
					m_pos[i].y = ((int)m_pos[i].y - m_posJY[i]) / 50 * 50 + (sy > 49 ? (sy - 49) : 49 - sy);
					m_posJX[i] = 0, m_posJY[i] = 0;
					posG.x = m_pos[i].x, posG.y = m_pos[i].y;
					m_isJumping[i] = false;
				}
				else if (m_isJumping[i] && (m_map->get_mat((posG.x + 49) / 50, (posG.y + sy) / 50) != 0 &&
					m_map->get_mat((posG.x + 49) / 50, (posG.y + sy) / 50) != 19) &&
					(m_map->get_mat((posG.x + 49) / 50, (posG.y + sy - dpl) / 50) == 0 ||
					m_map->get_mat((posG.x + 49) / 50, (posG.y + sy - dpl) / 50) == 19)){
					m_pos[i].y = ((int)m_pos[i].y - m_posJY[i]) / 50 * 50 + (sy > 49 ? (sy - 49) : 49 - sy);
					m_posJX[i] = 0, m_posJY[i] = 0;
					posG.x = m_pos[i].x, posG.y = m_pos[i].y;
					m_isJumping[i] = false;
				}
				else if ((m_map->get_mat(posG.x / SIZE_TILES, (posG.y + sy) / SIZE_TILES) != 0 &&
					m_map->get_mat(posG.x / SIZE_TILES, (posG.y + sy) / SIZE_TILES) != 19 &&
					(m_map->get_mat((posG.x + m_speed[i]) / SIZE_TILES, (posG.y + sy) / SIZE_TILES) == 0 ||
					m_map->get_mat((posG.x + m_speed[i]) / SIZE_TILES, (posG.y + sy) / SIZE_TILES) != 19))){
					m_speed[i] *= -1;
					m_pos[i].x = (int)(m_pos[i].x) / SIZE_TILES * SIZE_TILES + (m_pos[i].x >= 0 ? SIZE_TILES : 0);
					posG.x = m_pos[i].x, posG.y = m_pos[i].y - m_posJY[i];
					if (m_speed[i] < 0 && !m_hurt[i])
						m_currentImage[i] = 0;
					else if (!m_hurt[i])
						m_currentImage[i] = 2;
				}
				else if ((m_map->get_mat((posG.x + 49) / SIZE_TILES, (posG.y + sy) / SIZE_TILES) != 0 &&
					m_map->get_mat((posG.x + 49) / SIZE_TILES, (posG.y + sy) / SIZE_TILES) != 19 &&
					(m_map->get_mat((posG.x + 49 - m_speed[i]) / SIZE_TILES, (posG.y + sy) / SIZE_TILES) == 0 ||
					m_map->get_mat((posG.x + 49 - m_speed[i]) / SIZE_TILES, (posG.y + sy) / SIZE_TILES) == 19))){
					m_speed[i] *= -1;
					m_pos[i].x = (int)(m_pos[i].x) / SIZE_TILES * SIZE_TILES;
					posG.x = m_pos[i].x, posG.y = m_pos[i].y - m_posJY[i];
					if (m_speed[i] < 0 && !m_hurt[i])
						m_currentImage[i] = 0;
					else if (!m_hurt[i])
						m_currentImage[i] = 2;
				}

			}
			else if (m_type[i] == CARNT){
				m_timerInd[i]++;
				if (m_timerInd[i] <= 150){
					m_pos[i].y-=0.5;
				}
				else if (m_timerInd[i] <= 400 && m_timerInd[i] >= 250)
					m_pos[i].y+=0.5;
				if (m_timerInd[i] >= 540 && m_isMoving[i])
					m_timerInd[i] = 0;
			}

		}
	}
}

void Goomba::display(SDL_Surface *screen){
	if (m_nb != 0){
		SDL_Rect pos;
		for (int i = 0; i < m_nb; ++i){
			if (m_pos[i].x + 50 >= m_map->getXScroll() && m_pos[i].x <= m_map->getXScroll() + 1600){
				pos.x = m_pos[i].x - m_map->getXScroll(), pos.y = m_pos[i].y - m_posRelY[i] - m_posJY[i];
				SDL_BlitSurface(m_images[m_type[i]][m_currentImage[i]], NULL, screen, &pos);
			}
		}
	}
}

void Goomba::supressAll(int pos){

	m_speed.erase(m_speed.begin() + pos);
	m_currentImage.erase(m_currentImage.begin() + pos);
	m_hurt.erase(m_hurt.begin() + pos);
	m_timerInd.erase(m_timerInd.begin() + pos);
	m_pos.erase(m_pos.begin() + pos);
	m_posRelY.erase(m_posRelY.begin() + pos);
	m_died.erase(m_died.begin() + pos);
	m_posJY.erase(m_posJY.begin() + pos);
	m_posJX.erase(m_posJX.begin() + pos);
	m_isJumping.erase(m_isJumping.begin() + pos);
	m_lastY.erase(m_lastY.begin() + pos);
	m_detected.erase(m_detected.begin() + pos);
	m_type.erase(m_type.begin() + pos);
	m_isMoving.erase(m_isMoving.begin() + pos);
	m_nb--;
}
