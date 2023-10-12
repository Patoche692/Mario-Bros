#include "Mario.h"

void Mario::set_goomba(Goomba *goomba){ m_goomba = goomba; }
void Mario::setMap(Map *map){ m_map = map;}
void Mario::updateLastPos(){ m_lastPos = { m_pos.x + m_map->getXScroll(), m_pos.y - m_posRelY, 0, 0 }; }

Mario::Mario(int level)
{
	m_lastRelY = 0;
	m_fire = new Fire();
	m_anim = new Anim(level);
	m_size = SMALL;
	m_pos.x = 100, m_pos.y = 13*SIZE_TILES, m_posRelX = 0, m_posRelX = 0;
	m_lastPos = { 0, 0, 0, 0 };
	gotFlower = false;
	isJumping = false;
	m_isGrowing = false;
	m_speed = 2;
	m_images[0][0][0] = IMG_Load("Images/MarioDroite-1.gif");
	m_images[0][0][1] = IMG_Load("Images/MarioDroite-2.gif");
	m_images[0][0][2] = IMG_Load("Images/MarioDroite-3.gif");
	m_images[0][0][3] = IMG_Load("Images/MarioDroite-4.gif");
	m_images[0][0][4] = IMG_Load("Images/MarioSaut-droite.gif");
	m_images[0][1][0] = IMG_Load("Images/MarioGauche-1.gif");
	m_images[0][1][1] = IMG_Load("Images/MarioGauche-2.gif");
	m_images[0][1][2] = IMG_Load("Images/MarioGauche-3.gif");
	m_images[0][1][3] = IMG_Load("Images/MarioGauche-4.gif");
	m_images[0][1][4] = IMG_Load("Images/MarioSaut-gauche.gif");
	m_images[1][0][0] = IMG_Load("Images/MarioDroite-G1.gif");
	m_images[1][0][1] = IMG_Load("Images/MarioDroite-G2.gif");
	m_images[1][0][2] = IMG_Load("Images/MarioDroite-G3.gif");
	m_images[1][0][3] = IMG_Load("Images/MarioDroite-G4.gif");
	m_images[1][0][4] = IMG_Load("Images/MarioSaut-droiteG.gif");
	m_images[1][1][0] = IMG_Load("Images/MarioGauche-G1.gif");
	m_images[1][1][1] = IMG_Load("Images/MarioGauche-G2.gif");
	m_images[1][1][2] = IMG_Load("Images/MarioGauche-G3.gif");
	m_images[1][1][3] = IMG_Load("Images/MarioGauche-G4.gif");
	m_images[1][1][4] = IMG_Load("Images/MarioSaut-gaucheG.gif");
	m_images[2][0][0] = IMG_Load("Images/MarioDroite-F1.gif");
	m_images[2][0][1] = IMG_Load("Images/MarioDroite-F2.gif");
	m_images[2][0][2] = IMG_Load("Images/MarioDroite-F3.gif");
	m_images[2][0][3] = IMG_Load("Images/MarioDroite-F4.gif");
	m_images[2][0][4] = IMG_Load("Images/MarioSaut-droiteF.gif");
	m_images[2][1][0] = IMG_Load("Images/MarioGauche-F1.gif");
	m_images[2][1][1] = IMG_Load("Images/MarioGauche-F2.gif");
	m_images[2][1][2] = IMG_Load("Images/MarioGauche-F3.gif");
	m_images[2][1][3] = IMG_Load("Images/MarioGauche-F4.gif");
	m_images[2][1][4] = IMG_Load("Images/MarioSaut-gaucheF.gif");
	m_current = m_images[0][0][0];
	m_currentDir = 0;
	m_currentNumber = 0;
	m_timer = 0;
	m_collideUp = false;
	m_previousOffset = 0;
}


Mario::~Mario(){
	for (int h = 0; h < 3; ++h)
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 5; ++j)
				SDL_FreeSurface(m_images[h][i][j]);
}

void Mario::setX(int x)
{
	m_pos.x = x;
}

void Mario::setY(int y)
{
	m_pos.y = y;
}

void Mario::setXRel(float xRel)
{
	m_posRelX = xRel;
}

void Mario::setYRel(int yRel){ m_posRelY = yRel; }

SDL_Surface *Mario::getCurrentSurface()
{
	return m_current;
}

SDL_Rect Mario::getPos()
{
	return m_pos;
}

Sint16 Mario::getX(){ return m_pos.x; }
Sint16 Mario::getY(){ return m_pos.y; }
Sint16 Mario::getXRel(){ return m_posRelX; }
Sint16 Mario::getYRel(){ return m_posRelY; }

void Mario::setCurrent(SDL_Surface *current)
{
	m_current = current;
	m_currentNumber = 0;
}

SDL_Surface *Mario::getSurface(int dir, int pos)
{
	return m_images[m_size][dir][pos];
}

void Mario::display(SDL_Surface *screen)
{
	SDL_Rect copie;
	m_pos.y = m_pos.y;
	copie.x = m_pos.x, copie.y = m_pos.y - m_posRelY;
	SDL_BlitSurface(m_current, NULL, screen, &copie);
}

void Mario::dispFire(SDL_Surface *screen){ m_fire->display(screen, m_map->getXScroll()); }
void Mario::dispMush(SDL_Surface *screen){ m_anim->dispMush(screen, m_map); }
void Mario::dispOther(SDL_Surface *screen){ m_anim->dispOther(screen, m_map); }

void Mario::anim(int dir)
{
	m_timer++;
	if (m_timer == TIMER/* && !m_isGrowing && dir != 2*/){
		m_currentDir = dir;
		m_currentNumber = (m_currentNumber <= 2 ? m_currentNumber + 1 : 0);
		m_current = m_images[m_size][m_currentDir][m_currentNumber];
		m_timer = 0;
	}
	/*else if (m_timer >= TIMER && m_isGrowing && dir == 2){
		m_size = m_size == 1 ? 0 : 1;
		m_current = m_images[m_size][m_currentDir][m_currentNumber];
		if (m_timer == 300){
			m_timer = 0;
			m_isGrowing = false;
		}
	}*/
}

bool Mario::getJumping(){ return isJumping; }

void Mario::set_start_time(int a){ m_startTime = a; }
void Mario::setJumping(bool a){ isJumping = a; }
void Mario::set_current_time(int a){ m_currentTime = a; }
int Mario::get_current_time(){ return m_currentTime; }
int Mario::get_offset(){ return (m_currentTime - m_startTime); }

void Mario::jump()
{
	m_lastRelY = m_posRelY;
	m_previousOffset = m_offset;
	m_offset = (m_currentTime - m_startTime) / 250.0 + 1.8;
	m_posRelX += m_speed == 3 ? 2.7 : 3.1;
	setYRel((m_posRelX)*(m_posRelX)*(-0.01) + m_offset*(m_posRelX) + m_coeffJump);
}

void Mario::update(Input *m_input, Target& target, Score *score) /* Fonction pour toutes les collisions de Mario */
{
	SDL_Rect pos, posM;
	int sx = m_size == 0 ? 42 : 42;
	int sy = m_size == 0 ? 49 : 83;
	int previousSize = m_size;
	int x17(0), y17(0);

	bool collideDown = false;
	posM.x = m_pos.x + m_map->getXScroll(), posM.y = m_pos.y - m_posRelY;
	int dpl = -m_lastPos.y + posM.y;

	if (m_fire->get_nb()){
		m_fire->update(m_goomba, m_map, m_sounds);
	}


	target.update(m_map, m_fire, m_sounds);

	m_anim->update(&posM, m_map, &m_size, &gotFlower, m_sounds, score);
	if (previousSize != m_size){
		if (m_size == TALL){
			m_isGrowing = true;
			m_pos.y -= 34;
			posM.y -= 34;
			m_current = m_images[1][0][0];
			int sx = 30;
			int sy = 53;
		}
		else if (m_size == FIREM){
			m_input->setPressed(SDLK_s, false);
			m_current = m_images[2][0][0];
		}
	}

	if (m_input->isPressed(SDLK_s) && m_size == FIREM){
		m_input->setPressed(SDLK_s, false);
		m_sounds->playSound(FIREBALL);
		m_fire->add(posM.x, posM.y, m_input);
	}

	for (int i = posM.x / SIZE_TILES; i < posM.x / SIZE_TILES + 3; ++i){
		for (int j = posM.y / SIZE_TILES; j < posM.y / SIZE_TILES + 3; ++j){
			if (m_map->get_mat(i, j) != 0 && m_map->get_mat(i, j) != 12){
				pos.x = i * SIZE_TILES, pos.y = j * SIZE_TILES;

				if (posM.y + sy >= pos.y && posM.y <= pos.y + 49 && posM.x <= pos.x + sx && posM.x >= pos.x + sx - m_speed){
					if (m_map->get_mat(i, j) == 19){
						score->addCoin();
						m_sounds->playSound(COIN);
						m_map->set_mat(i, j, 0);
						continue;
					}

					else{
						if (!m_map->isScrolling())
							m_pos.x = pos.x + sx + 1 - m_map->getXScroll();
						else
							m_map->setXScroll(m_map->getXScroll() / SIZE_TILES * SIZE_TILES + sx + 1);

						posM.x = m_pos.x + m_map->getXScroll(), posM.y = m_pos.y - m_posRelY;
					}
				}
				else if (posM.y + sy >= pos.y && posM.y <= pos.y + 49 && posM.x + sx >= pos.x && posM.x + sx <= pos.x + m_speed){

					if (m_map->get_mat(i, j) == 19){
						score->addCoin();
						m_sounds->playSound(COIN);
						m_map->set_mat(i, j, 0);
						continue;
					}

					else{
						if (!m_map->isScrolling())
							m_pos.x = pos.x - sx - 1 - m_map->getXScroll();
						else
							m_map->setXScroll(m_map->getXScroll() / SIZE_TILES * SIZE_TILES + SIZE_TILES - sx - 1);

						posM.x = m_pos.x + m_map->getXScroll(), posM.y = m_pos.y - m_posRelY;
					}
				}

				if (posM.x + sx >= pos.x && posM.x <= pos.x + sx && posM.y + sy >= pos.y && posM.y + sy <= pos.y + dpl){

					if (m_map->get_mat(i, j) == 19){
						score->addCoin();
						m_sounds->playSound(COIN);
						m_map->set_mat(i, j, 0);
						continue;
					}

					else{
						if (m_input->get_right_pressed2())
							m_current = m_images[m_size][0][0];
						else
							m_current = m_images[m_size][1][0];

						setY(pos.y - (sy + 1));
						posM.y = m_pos.y;
						setJumping(false);
						setXRel(0);
						setYRel(0);
						set_start_time(0);
						set_current_time(0);
						m_coeffJump = 0;
						collideDown = true;
						posM.x = m_pos.x + m_map->getXScroll(), posM.y = m_pos.y - m_posRelY;
					}
				}
				else if (posM.x + sx >= pos.x && posM.x <= pos.x + sx && posM.y <= pos.y + 49 && posM.y >= pos.y + 49 + dpl){
					if (m_map->get_mat(i, j) == 19){
						score->addCoin();
						m_sounds->playSound(COIN);
						m_map->set_mat(i, j, 0);
						continue;
					}

					else{
						m_collideUp = true;
						m_input->setPressed(SDLK_SPACE, false);
						m_input->set_space_pressed(false);
						if (posM.x - pos.x >= 16 && (m_map->get_mat(i + 1, j) == 17 || m_map->get_mat(i + 1, j) == 18
							|| m_map->get_mat(i + 1, j) == 20 || m_map->get_mat(i + 1, j) == 21)){

							if (m_map->get_mat(i + 1, j) == 20 || m_map->get_mat(i + 1, j) == 18){
								m_sounds->playSound(COIN);
								m_anim->add(ACOIN, (i + 1) * SIZE_TILES, j * SIZE_TILES);
							}
							else if (m_map->get_mat(i + 1, j) == 21){
								m_anim->add(m_size == 0 ? AMUSHRED : AFLOWER, (i + 1) * SIZE_TILES, j * SIZE_TILES);
							}
							else if (m_map->get_mat(i + 1, j) == 17 && m_size != 0){
								x17 = i, y17 = j;
								m_sounds->playSound(BREAK);
								for (int k = 0; k < 4; ++k)
									m_anim->add(ABREAK, (i + 1) * SIZE_TILES, j * SIZE_TILES);
							}
							else
								m_sounds->playSound(COLLIDE);

							m_map->anim(i + 1, j, m_size);
						}
						else if (m_map->get_mat(i, j) == 17 || m_map->get_mat(i, j) == 18
							|| m_map->get_mat(i, j) == 20 || m_map->get_mat(i, j) == 21){

							if (m_map->get_mat(i, j) == 20 || m_map->get_mat(i, j) == 18){
								m_anim->add(ACOIN, i * SIZE_TILES, j * SIZE_TILES);
								m_sounds->playSound(COIN);
							}
							else if (m_map->get_mat(i, j) == 21){
								m_anim->add(m_size == 0 ? AMUSHRED : AFLOWER, i * SIZE_TILES, j * SIZE_TILES);
							}
							else if (m_map->get_mat(i, j) == 17 && m_size != 0){
								x17 = i, y17 = j;
								m_sounds->playSound(BREAK);
								for (int k = 0; k < 4; ++k)
									m_anim->add(ABREAK, i * SIZE_TILES, j * SIZE_TILES);
							}
							else
								m_sounds->playSound(COLLIDE);

							m_map->anim(i, j, m_size);
						}
						m_posRelY = m_lastRelY;
						m_posRelX = 150;
						m_currentTime = 300;
						m_startTime = 0;
						m_coeffJump = -225 + m_posRelY;
						posM.x = m_pos.x + m_map->getXScroll(), posM.y = m_pos.y - m_posRelY;
					}
				}
			}
		}
	}

	if (posM.x + sx >= m_clear.x && posM.x <= m_clear.x + 49 && posM.y + sy >= m_clear.y && posM.y <= m_clear.y + 49){
		m_sounds->playTheme(WIN);
		SDL_Delay(5000);
		*m_continuer = false;
		return;
	}

	if (posM.y + sy >= 18 * SIZE_TILES){
		*m_win = false;
		m_sounds->playTheme(DIE);
		SDL_Delay(3000);
		*m_continuer = false;
		return;
	}

	int o = m_size == 0 ? 1 : 2;
	if ((m_map->get_mat((posM.x + 8) / SIZE_TILES, posM.y / SIZE_TILES + o) == 0 || m_map->get_mat((posM.x + 8) / SIZE_TILES, posM.y / SIZE_TILES + o) == 19)
		&& (m_map->get_mat((posM.x + sx) / SIZE_TILES, posM.y / SIZE_TILES + o) == 0 || m_map->get_mat((posM.x + sx) / SIZE_TILES, posM.y / SIZE_TILES + o) == 0) && !isJumping){
		isJumping = true;
		posM.x = m_pos.x + m_map->getXScroll();
		m_currentTime = 300;
		m_startTime = 0;
		m_posRelX = 150;
		m_coeffJump = -225;
	}


	if (m_goomba->get_nb() != 0){
		for (int i = 0; i < m_goomba->get_nb(); ++i){
			if (!m_goomba->is_hurt(i) && !m_goomba->isDied(i)){
				if (m_goomba->getType(i) == 2 && ((posM.x - m_goomba->getX(i) >= -80 && posM.x - m_goomba->getX(i) <= 0)
					|| (posM.x - m_goomba->getX(i) <= 80 && posM.x - m_goomba->getX(i) >= 0))){
					m_goomba->setMoving(i, 0);
				}
				else if (m_goomba->getType(i) == 2 && ((posM.x - m_goomba->getX(i) <= -50)
					|| (posM.x - m_goomba->getX(i) >= 50))){
					m_goomba->setMoving(i, 1);
				}

				int sgy = m_goomba->getType(i) == GOOMBAT ? 49 : 74;
				if (posM.x + sx >= m_goomba->getX(i) && posM.x <= m_goomba->getX(i) + 49 && posM.y + sy >= m_goomba->getY(i) &&
					dpl > 0 && posM.y + sy <= m_goomba->getY(i) + dpl && (m_goomba->getType(i) == 1 || !m_goomba->getType(i))){
					if (!m_input->isPressed(SDLK_SPACE)){
						collideDown = true;
						m_currentTime = 0;
						m_startTime = 200;
					}
					else{
						m_sounds->playSound(JUMP);
						m_input->set_space_pressed(true);
						set_start_time(SDL_GetTicks());
						set_current_time(SDL_GetTicks());
						setCurrent(getSurface(0, 4));
					}
					m_sounds->playSound(KICK);
					score->addScore(100);
					isJumping = true;
					m_pos.y = m_pos.y - m_posRelY;
					m_goomba->set_current(i, 4);
					m_posRelX = 0;
					m_posRelY = 0;
					m_coeffJump = 0;
					posM.x = m_pos.x + m_map->getXScroll(), posM.y = m_pos.y - m_posRelY;
					m_goomba->set_hurt(i, 1);
				}
				else if ((posM.y + sy - 8 >= m_goomba->getY(i) && posM.y <= m_goomba->getY(i) + sgy &&
					posM.x + sx >= m_goomba->getX(i) && posM.x <= m_goomba->getX(i) + 49)){

					if (m_size == 0){
						m_sounds->playTheme(DIE);
						SDL_Delay(3000);
						*m_win = false;
						*m_continuer = false;
						return;
					}
					else{
						m_size = 0;
					}
				}
				if (m_map->isAnim(m_goomba->getX(i) / SIZE_TILES, m_goomba->getY(i) / SIZE_TILES + 1)){
					m_goomba->setDied(i);
					m_sounds->playSound(KICK);
				}
				else if (m_map->isAnim(m_goomba->getX(i) / SIZE_TILES + 1, m_goomba->getY(i) / SIZE_TILES + 1)){
					m_goomba->setDied(i);
					m_sounds->playSound(KICK);
				}
				else if ((m_goomba->getX(i) / SIZE_TILES == x17 && m_goomba->getY(i) / SIZE_TILES + 1 == y17)
					|| (m_goomba->getX(i) + 49) / SIZE_TILES == x17 && m_goomba->getY(i) / SIZE_TILES + 1 == y17){
					m_goomba->setDied(i);
					m_sounds->playSound(KICK);
				}
			}
			else if (m_goomba->is_hurt(i) && m_goomba->getType(i) == KOOPAT){
				if (posM.x + sx >= m_goomba->getX(i) && posM.x <= m_goomba->getX(i) + sx && posM.y + sy >= m_goomba->getY(i) &&
					dpl > 0 && posM.y + sy <= m_goomba->getY(i) + dpl){
					if (!m_input->isPressed(SDLK_SPACE)){
						m_currentTime = 0;
						m_startTime = 200;
					}
					else{
						m_sounds->playSound(JUMP);
						m_input->set_space_pressed(true);
						set_start_time(SDL_GetTicks());
						set_current_time(SDL_GetTicks());
						setCurrent(getSurface(0, 4));
					}
					m_sounds->playSound(KICK);
					isJumping = true;
					m_pos.y = m_goomba->getY(i) - sy - 1;
					m_posRelX = 0;
					m_posRelY = 0;
					m_coeffJump = 0;
					m_goomba->setMoving(i, (m_goomba->getMoving(i) ? 0 : 1));
					m_goomba->setSpeed(i, 6);
					m_goomba->set_current(i, 4);
					posM.x = m_pos.x + m_map->getXScroll(), posM.y = m_pos.y - m_posRelY;
				}
				else if (!m_goomba->getMoving(i) && posM.x + sx >= m_goomba->getX(i) && posM.x <= m_goomba->getX(i) + sx
					&& posM.y + sy >= m_goomba->getY(i) + dpl && posM.y <= m_goomba->getY(i) + sy){
					m_goomba->setMoving(i, 1);
					m_goomba->set_current(i, 4);
					m_goomba->setSpeed(i, posM.x < m_goomba->getX(i) ? 6 : -6);
				}
				else if (m_goomba->getMoving(i) && posM.x + sx - 5 >= m_goomba->getX(i) && posM.x <= m_goomba->getX(i) + sx - 5
					&& posM.y + sy >= m_goomba->getY(i) + dpl && posM.y <= m_goomba->getY(i) + sy){
					m_sounds->playTheme(DIE);
					SDL_Delay(3000);
					*m_win = false;
					*m_continuer = false;
					return;
				}
			}
		}
	}
}

bool Mario::getCollideUp(){ return m_collideUp; }
void Mario::setCollideUp(bool tf){ m_collideUp = tf; }
Map Mario::getMap(){ return *m_map; }

void Mario::set_continuer(bool *continuer, bool *win){
	m_continuer = continuer;
	m_win = win;
}

void Mario::setSounds(Sounds *sounds){
	m_sounds = sounds;
}

void Mario::setClearPos(SDL_Rect pos){ m_clear = pos; }
void Mario::newFA(int level){
	m_fire = new Fire();
	m_anim = new Anim(level);
}

int Mario::getSize(){ return m_size; }

void Mario::init(int x, int y){
	m_pos = { x, y, 0, 0 };
	m_posRelX = 0;
	m_posRelY = 0;
	setJumping(false);
	set_start_time(0);
	set_current_time(0);
	m_coeffJump = 0;
	m_offset = 0;
	m_current = m_images[m_size][0][0];
}

void Mario::setSpeed(int speed){ m_speed = speed; }
int Mario::getSpeed(){ return m_speed; }