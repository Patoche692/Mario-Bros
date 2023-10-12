#include "Anim.h"

void Anim::update(SDL_Rect *posM, Map *map, int *size, bool *gotFlower, Sounds *sounds, Score *score){
	int sx = *size == 0 ? 45 : 50;
	int sy = *size == 0 ? 49 : 83;

	if (m_type.size()){
		for (int i = 0; i < m_type.size(); ++i){
			if (m_type[i] == ACOIN){
				m_timer[i]++;
				if (m_timer[i] % 6 == 0){
					m_current[i] = m_current[i] == 3 ? 0 : m_current[i] + 1;
				}
				if (m_timer[i] % 2 == 0){
					m_posRelX[i] += 2;
					m_posRelY[i] = m_posRelX[i] * m_posRelX[i] * (-0.15) + 13 * m_posRelX[i];
					if (m_timer[i] >= 85){
						score->addScore(100);
						score->addCoin();
						supressAll(i);
						i--;
						continue;
					}
				}
			}

			else if (m_type[i] == AMUSHRED){
				SDL_Rect pos, m_posB;
				m_timer[i]++;
				m_apos[i].x = m_pos[i].x, m_apos[i].y = m_pos[i].y - m_posRelY[i];


				if ((m_timer[i] + 1) % 4 == 0 && m_timer[i] >= 30 && m_timer[i] <= 231){
					if (m_timer[i] <= 230){
						m_pos[i].y--;
						m_posB.x = m_pos[i].x, m_posB.y = m_pos[i].y - m_posRelY[i];
						if (posM->y + sy >= m_posB.y && posM->y <= m_posB.y + 25 && posM->x + sx >= m_posB.x && posM->x <= m_posB.x + 25){
							sounds->playSound(GROWS);
							score->addScore(200);
							supressAll(i);
							*size = 1;
							i--;
							continue;
						}
					}
					else if (m_timer[i] == 231){
						m_offset[i] = (m_pos[i].x - posM->x > 0 ? -2 : 2);
					}
				}
				if (m_timer[i] >= 231 && (m_timer[i] + 1) % 2 == 0){
					m_pos[i].x += m_offset[i];

					if (isJumping[i]){
						m_posRelX[i] += 1.5;
						m_posRelY[i] = m_posRelX[i] * m_posRelX[i] * -0.04 + 5 * m_posRelX[i] - 156.25;
					}

					m_posB.x = m_pos[i].x, m_posB.y = m_pos[i].y - m_posRelY[i];
					int dpl = m_posB.y - m_apos[i].y;

					if (m_pos[i].x <= 0)
						m_offset[i] *= -1;
					else if (m_pos[i].x + SIZE_TILES >= 220 * SIZE_TILES)
						m_offset[i] *= -1;

					if (posM->y + sy >= m_posB.y && posM->y <= m_posB.y + 25 && posM->x + sx >= m_posB.x && posM->x <= m_posB.x + 25){
						sounds->playSound(GROWS);
						score->addScore(200);
						supressAll(i);
						*size = 1;
						i--;
						continue;
					}

					else if ((map->get_mat(m_pos[i].x / SIZE_TILES, m_pos[i].y / SIZE_TILES + 1) == 0 || map->get_mat(m_pos[i].x / SIZE_TILES, m_pos[i].y / SIZE_TILES + 1) == 19) && !isJumping[i]
						&& (map->get_mat((m_pos[i].x + 49) / SIZE_TILES, m_pos[i].y / SIZE_TILES + 1) == 0 || map->get_mat((m_pos[i].x + 49) / SIZE_TILES, m_pos[i].y / SIZE_TILES + 1) == 19)){
						isJumping[i] = true;
						m_posRelX[i] = 62.5;
					}

					for (int j = m_pos[i].x / SIZE_TILES; j < m_pos[i].x / SIZE_TILES + 2; j++){
						for (int k = m_posB.y / SIZE_TILES; k < m_posB.y / SIZE_TILES + 2; ++k){
							pos.x = j * SIZE_TILES, pos.y = k * SIZE_TILES;

							if (map->get_mat(j, k) != 0 && map->get_mat(j, k) != 19){
								if (m_pos[i].x + 49 >= pos.x && m_pos[i].x <= pos.x + 49 && m_posB.y + 49 >= pos.y && m_posB.y + 49 <= pos.y + 10){
									isJumping[i] = false;
									m_posRelX[i] = 0;
									m_pos[i].y = pos.y - SIZE_TILES;
									m_posRelY[i] = 0;
								}

								else if (m_posB.y + 49 >= pos.y && m_posB.y <= pos.y + 49 && m_pos[i].x + 49 >= pos.x
									&& m_pos[i].x + 49 <= pos.x + m_offset[i])
									m_offset[i] *= -1;
								else if (m_posB.y + 49 >= pos.y && m_posB.y <= pos.y + 49 && m_pos[i].x <= pos.x + 49
									&& m_pos[i].x >= pos.x + m_offset[i])
									m_offset[i] *= -1;
							}
						}
					}
				}
			}
			else if (m_type[i] == ABREAK){
				float m;
				m_timer[i]++;
				if (m_timer[i] % 2 == 0){
					for (int j = 0; j < 4; ++j){
						if ((j + 1) % 2 == 0){
							m_pos[i + j].x -= 3;
						}
						else{
							m_pos[i + j].x += 3;
						}
						if (j <= 1)
							m = 7;
						else
							m = 5;

						m_posRelX[i + j] += 2.2;
						m_posRelY[i + j] = m_posRelX[i + j] * m_posRelX[i + j] * -0.06 + m * m_posRelX[i + j];
					}
				}

				else if (m_timer[i] >= 140){
					supressAll(i + 3);
					supressAll(i + 2);
					supressAll(i + 1);
					supressAll(i);
					i--;
					continue;
				}
				i += 3;
			}
			else if (m_type[i] == AFLOWER){
				m_timer[i]++;
				if ((m_timer[i] + 1) % 4 == 0 && m_timer[i] >= 30){
					if (m_timer[i] <= 230){
						m_pos[i].y--;
						if (posM->y + sy >= m_pos[i].y && posM->y <= m_pos[i].y + 25 && posM->x + sx >= m_pos[i].x && posM->x <= m_pos[i].x + 25){
							sounds->playSound(GROWS);
							score->addScore(200);
							supressAll(i);
							*size = 2;
							i--;
							continue;
						}
					}
					else{
						if (posM->y + sy >= m_pos[i].y && posM->y <= m_pos[i].y + 25 && posM->x + sx >= m_pos[i].x && posM->x <= m_pos[i].x + 25){
							sounds->playSound(GROWS);
							score->addScore(200);
							supressAll(i);
							*size = 2;
							i--;
							continue;
						}
					}
				}
			}
		}
	}
}



void Anim::dispMush(SDL_Surface *screen, Map *map){
	SDL_Rect pos;
	for (int i = 0; i < m_type.size(); ++i){
		if ((m_timer[i] >= 30 && (m_type[i] == AMUSHRED || m_type[i] == AFLOWER))){
			pos = { m_pos[i].x - map->getXScroll(), m_pos[i].y - m_posRelY[i], 0, 0 };
			SDL_BlitSurface(m_images[m_type[i]][m_current[i]], NULL, screen, &pos);
		}
	}
}

void Anim::dispOther(SDL_Surface *screen, Map *map){
	SDL_Rect pos;
	for (int i = 0; i < m_type.size(); ++i){
		if (m_type[i] == ABREAK || m_type[i] == ACOIN){
			pos = { m_pos[i].x - map->getXScroll(), m_pos[i].y - m_posRelY[i], 0, 0 };
			SDL_BlitSurface(m_images[m_type[i]][m_current[i]], NULL, screen, &pos);
		}
	}
}

void Anim::add(int type, int x, int y){
	m_type.push_back(type);
	m_offset.push_back(0);
	m_timer.push_back(0);
	m_current.push_back(0);
	m_pos.push_back({ x, y, 0, 0 });
	m_posRelX.push_back(0);
	m_posRelY.push_back(0);
	m_apos.push_back({ 0, 0, 0, 0 });
	isJumping.push_back(false);
}
int Anim::getType(int x, int y){
	for (int i = 0; i < m_type.size(); ++i){
		if (m_pos[i].x == x && m_pos[i].y == y){
			return m_type[i];
		}
	}
}

int Anim::getOffset(int i){ return m_offset[i]; }
int Anim::getTimer(int i){ return m_timer[i]; }
void Anim::setTimer(int i, int j){ m_timer[i] = j; }
void Anim::setOffset(int i, int j){ m_offset[i] = j; }

Anim::Anim(int level){
	if (level == 1 || level >= 3){
		m_images[0][0] = IMG_Load("Images/Piece_1.gif");
		m_images[0][1] = IMG_Load("Images/Piece_2.gif");
		m_images[0][2] = IMG_Load("Images/Piece_3.gif");
		m_images[0][3] = IMG_Load("Images/Piece_4.gif");
		m_images[1][0] = IMG_Load("Images/champ_rouge.gif");
		m_images[2][0] = IMG_Load("Images/etoile_1.gif");
		m_images[3][0] = IMG_Load("Images/fleur.gif");
		m_images[4][0] = IMG_Load("Images/eclat.gif");
	}
	else if (level == 2){
		m_images[0][0] = IMG_Load("Images/Piece_1B.gif");
		m_images[0][1] = IMG_Load("Images/Piece_2B.gif");
		m_images[0][2] = IMG_Load("Images/Piece_3B.gif");
		m_images[0][3] = IMG_Load("Images/Piece_4B.gif");
		m_images[1][0] = IMG_Load("Images/champ_rouge.gif");
		m_images[2][0] = IMG_Load("Images/etoile_1.gif");
		m_images[3][0] = IMG_Load("Images/fleur.gif");
		m_images[4][0] = IMG_Load("Images/eclatB.gif");
	}
}

Anim::~Anim(){
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 4; ++j){
			SDL_FreeSurface(m_images[i][j]);
		}
	}
}
void Anim::supressAll(int pos){
	m_apos.erase(m_apos.begin() + pos);
	isJumping.erase(isJumping.begin() + pos);
	m_offset.erase(m_offset.begin() + pos);
	m_timer.erase(m_timer.begin() + pos);
	m_type.erase(m_type.begin() + pos);
	m_current.erase(m_current.begin() + pos);
	m_pos.erase(m_pos.begin() + pos);
	m_posRelX.erase(m_posRelX.begin() + pos);
	m_posRelY.erase(m_posRelY.begin() + pos);
}

