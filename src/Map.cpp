#include "Map.h"
using namespace std;

Map::Map(){ m_level = 1, Xscroll = 0, m_currentAnim = 0, m_timer = 0; }
Map::~Map(){
	for (int i = 0; i < 15; ++i)
		SDL_FreeSurface(m_tiles[i]);

	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 4; ++j)
			SDL_FreeSurface(m_tilesAnim[i][j]);
	}
}
Map::Map(int level){ 
	m_level = level;
	Xscroll = 0, m_currentAnim = 0, m_timer = 0;
}
bool Map::isAnim(int x, int y){ return m_anim[x][y]; }

void Map::load(int level)
{
	string nom;
	if (level == 1)
		nom = "Levels/level 1.txt";
	else if (level == 2)
		nom = "Levels/level 2.txt";
	else if (level >= 3)
		nom = "Levels/level 3.txt";

	ifstream file(nom.c_str());

	for (int j = 0; j < HEIGHT_MAP; ++j)
	{
		for (int i = 0; i < WIDTH_MAP; ++i)
		{
			do{
				file.get(m_mat[i][j]);
				m_anim[i][j] = 0;
				m_offset[i][j] = 0;
				m_upAnim[i][j] = 0;
			} while (m_mat[i][j] == '\n');
			m_mat[i][j] -= '0';
		}
	}

	m_coin[0] = IMG_Load("Images/Piece_1p.gif");
	m_coin[1] = IMG_Load("Images/Piece_2p.gif");
	m_coin[2] = IMG_Load("Images/Piece_3p.gif");
	m_coin[3] = IMG_Load("Images/Piece_4p.gif");

	if (level == 1){
		m_tiles[0] = IMG_Load("Images/sol_1_1.gif");
		m_tiles[1] = IMG_Load("Images/sol_1_2.gif");
		m_tiles[2] = IMG_Load("Images/tube_2.gif");
		m_tiles[3] = IMG_Load("Images/tube_1.gif");
		m_tiles[4] = IMG_Load("Images/tubeG_1.gif");
		m_tiles[5] = IMG_Load("Images/tubeG_2.gif");
		m_tiles[6] = IMG_Load("Images/tubeG_3.gif");
		m_tiles[7] = IMG_Load("Images/tubeG_4.gif");
		m_tiles[8] = IMG_Load("Images/escalier.gif");
		m_tiles[9] = IMG_Load("Images/castle.gif");
		m_tiles[10] = IMG_Load("Images/bloc_vide.gif");
		m_tiles[11] = IMG_Load("Images/champ_1.gif");
		m_tiles[12] = IMG_Load("Images/champ_2.gif");
		m_tiles[13] = IMG_Load("Images/champ_3.gif");
		m_tiles[14] = IMG_Load("Images/champ_4.gif");
		m_tilesAnim[0][0] = IMG_Load("Images/mur_1.gif");
		m_tilesAnim[0][1] = IMG_Load("Images/mur_2.gif");
		m_tilesAnim[0][2] = IMG_Load("Images/mur_3.gif");
		m_tilesAnim[0][3] = IMG_Load("Images/mur_4.gif");
		m_tilesAnim[1][0] = IMG_Load("Images/bloc_mystere_1.gif");
		m_tilesAnim[1][1] = IMG_Load("Images/bloc_mystere_2.gif");
		m_tilesAnim[1][2] = IMG_Load("Images/bloc_mystere_3.gif");
		m_tilesAnim[1][3] = IMG_Load("Images/bloc_mystere_4.gif");
		m_tilesAnim[2][0] = IMG_Load("Images/Piece_1.gif");
		m_tilesAnim[2][1] = IMG_Load("Images/Piece_2.gif");
		m_tilesAnim[2][2] = IMG_Load("Images/Piece_3.gif");
		m_tilesAnim[2][3] = IMG_Load("Images/Piece_4.gif");
		m_tilesAnim[3][0] = IMG_Load("Images/mur_1.gif");
		m_tilesAnim[3][1] = IMG_Load("Images/mur_2.gif");
		m_tilesAnim[3][2] = IMG_Load("Images/mur_3.gif");
		m_tilesAnim[3][3] = IMG_Load("Images/mur_4.gif");
		m_tilesAnim[4][0] = IMG_Load("Images/bloc_mystere_1.gif");
		m_tilesAnim[4][1] = IMG_Load("Images/bloc_mystere_2.gif");
		m_tilesAnim[4][2] = IMG_Load("Images/bloc_mystere_3.gif");
		m_tilesAnim[4][3] = IMG_Load("Images/bloc_mystere_4.gif");
	}
	else if (level == 2){
		m_tiles[0] = IMG_Load("Images/sol_1_1B.gif");
		m_tiles[1] = IMG_Load("Images/sol_1_2B.gif");
		m_tiles[2] = IMG_Load("Images/tube_2.gif");
		m_tiles[3] = IMG_Load("Images/tube_1.gif");
		m_tiles[4] = IMG_Load("Images/tubeG_1B.gif");
		m_tiles[5] = IMG_Load("Images/tubeG_2B.gif");
		m_tiles[6] = IMG_Load("Images/tubeG_3B.gif");
		m_tiles[7] = IMG_Load("Images/tubeG_4B.gif");
		m_tiles[8] = IMG_Load("Images/escalierB.gif");
		m_tiles[9] = IMG_Load("Images/castle.gif");
		m_tiles[10] = IMG_Load("Images/bloc_videB.gif");
		m_tiles[11] = IMG_Load("Images/champ_1.gif");
		m_tiles[12] = IMG_Load("Images/champ_2.gif");
		m_tiles[13] = IMG_Load("Images/champ_3.gif");
		m_tiles[14] = IMG_Load("Images/champ_4.gif");
		m_tilesAnim[0][0] = IMG_Load("Images/mur_1B.gif");
		m_tilesAnim[0][1] = IMG_Load("Images/mur_2B.gif");
		m_tilesAnim[0][2] = IMG_Load("Images/mur_3B.gif");
		m_tilesAnim[0][3] = IMG_Load("Images/mur_4B.gif");
		m_tilesAnim[1][0] = IMG_Load("Images/bloc_mystere_1B.gif");
		m_tilesAnim[1][1] = IMG_Load("Images/bloc_mystere_2B.gif");
		m_tilesAnim[1][2] = IMG_Load("Images/bloc_mystere_3B.gif");
		m_tilesAnim[1][3] = IMG_Load("Images/bloc_mystere_4B.gif");
		m_tilesAnim[2][0] = IMG_Load("Images/Piece_1B.gif");
		m_tilesAnim[2][1] = IMG_Load("Images/Piece_2B.gif");
		m_tilesAnim[2][2] = IMG_Load("Images/Piece_3B.gif");
		m_tilesAnim[2][3] = IMG_Load("Images/Piece_4B.gif");
		m_tilesAnim[3][0] = IMG_Load("Images/mur_1B.gif");
		m_tilesAnim[3][1] = IMG_Load("Images/mur_2B.gif");
		m_tilesAnim[3][2] = IMG_Load("Images/mur_3B.gif");
		m_tilesAnim[3][3] = IMG_Load("Images/mur_4B.gif");
		m_tilesAnim[4][0] = IMG_Load("Images/bloc_mystere_1B.gif");
		m_tilesAnim[4][1] = IMG_Load("Images/bloc_mystere_2B.gif");
		m_tilesAnim[4][2] = IMG_Load("Images/bloc_mystere_3B.gif");
		m_tilesAnim[4][3] = IMG_Load("Images/bloc_mystere_4B.gif");
	}
	else if (level >= 3){
		m_tiles[0] = IMG_Load("Images/sol_1_1.gif");
		m_tiles[1] = IMG_Load("Images/sol_1_2.gif");
		m_tiles[2] = IMG_Load("Images/tube_2.gif");
		m_tiles[3] = IMG_Load("Images/tube_1.gif");
		m_tiles[4] = IMG_Load("Images/tubeG_1.gif");
		m_tiles[5] = IMG_Load("Images/tubeG_2.gif");
		m_tiles[6] = IMG_Load("Images/tubeG_3.gif");
		m_tiles[7] = IMG_Load("Images/tubeG_4.gif");
		m_tiles[8] = IMG_Load("Images/escalier.gif");
		m_tiles[9] = IMG_Load("Images/castle.gif");
		m_tiles[10] = IMG_Load("Images/bloc_vide.gif");
		m_tiles[11] = IMG_Load("Images/champ_1.gif");
		m_tiles[12] = IMG_Load("Images/champ_2.gif");
		m_tiles[13] = IMG_Load("Images/champ_3.gif");
		m_tiles[14] = IMG_Load("Images/champ_4.gif");
		m_tilesAnim[0][0] = IMG_Load("Images/mur_1.gif");
		m_tilesAnim[0][1] = IMG_Load("Images/mur_2.gif");
		m_tilesAnim[0][2] = IMG_Load("Images/mur_3.gif");
		m_tilesAnim[0][3] = IMG_Load("Images/mur_4.gif");
		m_tilesAnim[1][0] = IMG_Load("Images/bloc_mystere_1.gif");
		m_tilesAnim[1][1] = IMG_Load("Images/bloc_mystere_2.gif");
		m_tilesAnim[1][2] = IMG_Load("Images/bloc_mystere_3.gif");
		m_tilesAnim[1][3] = IMG_Load("Images/bloc_mystere_4.gif");
		m_tilesAnim[2][0] = IMG_Load("Images/Piece_1.gif");
		m_tilesAnim[2][1] = IMG_Load("Images/Piece_2.gif");
		m_tilesAnim[2][2] = IMG_Load("Images/Piece_3.gif");
		m_tilesAnim[2][3] = IMG_Load("Images/Piece_4.gif");
		m_tilesAnim[3][0] = IMG_Load("Images/mur_1.gif");
		m_tilesAnim[3][1] = IMG_Load("Images/mur_2.gif");
		m_tilesAnim[3][2] = IMG_Load("Images/mur_3.gif");
		m_tilesAnim[3][3] = IMG_Load("Images/mur_4.gif");
		m_tilesAnim[4][0] = IMG_Load("Images/bloc_mystere_1.gif");
		m_tilesAnim[4][1] = IMG_Load("Images/bloc_mystere_2.gif");
		m_tilesAnim[4][2] = IMG_Load("Images/bloc_mystere_3.gif");
		m_tilesAnim[4][3] = IMG_Load("Images/bloc_mystere_4.gif");
	}
}

void Map::display(SDL_Surface *screen)
{
	m_timer++;

	if (m_timer % 18 == 0)
		m_currentAnim = m_currentAnim == 3 ? 0 : m_currentAnim + 1, m_timer = 0;

	SDL_Rect pos;
	for (int i = Xscroll / SIZE_TILES; i < (Xscroll + SIZE_TILES) / SIZE_TILES + (i <= WIDTH_MAP - 1 ? 33 : 32); ++i){
		for (int j = 0; j < HEIGHT_MAP; ++j){
			if (!m_anim[i][j]){
				if (m_mat[i][j] == 0)
					continue;
				pos.x = i * SIZE_TILES - Xscroll, pos.y = j * SIZE_TILES;
				if (m_mat[i][j] >= 17 && m_mat[i][j] <= 21){
					SDL_BlitSurface(m_tilesAnim[m_mat[i][j] - 17][m_currentAnim], NULL, screen, &pos);
					continue;
				}
				else if (m_mat[i][j] < 17){
					SDL_BlitSurface(m_tiles[m_mat[i][j] - 1], NULL, screen, &pos);
					continue;
				}
			}
			else{
				if (!m_upAnim[i][j]){
					m_offset[i][j] -= 2;
					if (m_offset[i][j] == -24)
						m_upAnim[i][j] = 1;
				}
				else{
					m_offset[i][j] += 2;
					if (!m_offset[i][j]){
						m_anim[i][j] = 0;
						m_offset[i][j] = 0;
						m_upAnim[i][j] = 0;
					}
				}
				pos.x = i * SIZE_TILES - Xscroll, pos.y = j * SIZE_TILES + m_offset[i][j];
				if (m_mat[i][j] < 17)
					SDL_BlitSurface(m_tiles[m_mat[i][j] - 1], NULL, screen, &pos);
				else if (m_mat[i][j] >= 17 && m_mat[i][j] <= 21)
					SDL_BlitSurface(m_tilesAnim[m_mat[i][j] - 17][m_currentAnim], NULL, screen, &pos);
			}
		}
	}
	pos.x = 420, pos.y = 30;
	SDL_BlitSurface(m_coin[m_currentAnim], NULL, screen, &pos);
}


char Map::get_mat(int i, int j){ return (j >= 0 ? m_mat[i][j] : 0); }
int Map::getXScroll(){ return Xscroll; }
void Map::setXScroll(int a){ Xscroll = a; }
bool Map::isScrolling(){ return m_isScrolling; }
void Map::setScrolling(bool a) { m_isScrolling = a; }
void Map::set_mat(int i, int j, int a){ m_mat[i][j] = a; }

int Map::getMarioX()
{
	for (int i = 0; i < WIDTH_MAP; ++i){
		for (int j = 0; j < HEIGHT_MAP; ++j){
			if (m_mat[i][j] == 78)
				return i;
		}
	}
}
int Map::getMarioY()
{
	for (int i = 0; i < WIDTH_MAP; ++i){
		for (int j = 0; j < HEIGHT_MAP; ++j){
			if (m_mat[i][j] == 78)
				return j;
		}
	}
}

void Map::anim(int i, int j, int size){
	if ((m_mat[i][j] == 17 || m_mat[i][j] == 18 || m_mat[i][j] == 20 || m_mat[i][j] == 21)){
		if (m_mat[i][j] != 17)
			m_anim[i][j] = 1;

		if (m_mat[i][j] == 20 || m_mat[i][j] == 21 || m_mat[i][j] == 18)
			m_mat[i][j] = 11;

		else if (m_mat[i][j] == 17 && size != 0)
			m_mat[i][j] = 0;

		else if (m_mat[i][j] == 17 && size == 0)
			m_anim[i][j] = 1;
	}
}

SDL_Rect Map::getTargetPos(){
	SDL_Rect tmp;
	for (int i = 0; i < WIDTH_MAP; ++i){
		for (int j = 0; j < HEIGHT_MAP; ++j){
			if (m_mat[i][j] == 77){
				tmp.x = i * SIZE_TILES, tmp.y = j * SIZE_TILES;
				m_mat[i][j] = 0;
			}
		}
	}
	return tmp;
}

SDL_Rect Map::getXCastle(){
	SDL_Rect tmp;
	for (int i = 0; i < WIDTH_MAP; ++i){
		for (int j = 0; j < HEIGHT_MAP; ++j){
			if (m_mat[i][j] == 10){
				tmp.x = (i + 2) * SIZE_TILES, tmp.y = (j + 4) * SIZE_TILES;
				return tmp;
			}
		}
	}
}
