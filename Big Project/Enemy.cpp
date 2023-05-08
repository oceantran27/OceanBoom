#include "Enemy.h"
#include <queue>
#include <cstring>

#define LIMIT_LAG 20

typedef std::pair<int, int> Pair;

//Find the shortest path between enemy and bomber

struct Cell
{
	int col, row;
	Cell* parent;

	Cell()
	{
		row = -1;
		col = -1;
		parent = NULL;
	}
	~Cell()
	{
		delete(parent);
		parent = NULL;
	}
	Cell(int row_, int col_)
	{
		this->row = row_;
		this->col = col_;
	}

};

Pair tracePath(Cell* dest, Pair src)
{
	Cell* p = dest;
	while (p->parent->row != src.first || p->parent->col != src.second)
	{
		Cell* tmp = p;
		p = p->parent;
		tmp = NULL;
		delete(tmp);
	}

	return std::make_pair(p->row, p->col);
}

bool isValid(int row, int col)
{
	return (row >= 0) && (row < MAX_MAP_Y)
		&& (col >= 0) && (col < MAX_MAP_X);
}

bool isUnBlocked(int grid[][MAX_MAP_X], int row, int col)
{
	return grid[row][col] == BLANK_CELL;
}

Pair bfs(int grid[][MAX_MAP_X], Pair src, Pair dest)
{
	bool visit[MAX_MAP_Y][MAX_MAP_X];
	memset(visit, false, sizeof(visit));
	std::queue<Cell*> neighbor;
	Cell* pSrc = new Cell(src.first, src.second);
	neighbor.push(pSrc);
	visit[src.first][src.second] = true;
	while (!neighbor.empty())
	{
		Cell* current = neighbor.front();
		neighbor.pop();

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((i == 0 && j == 0) || (i != 0 && j != 0))
				{
					continue;
				}
				if (isValid(current->row + i, current->col + j))
				{
					if (!visit[current->row + i][current->col + j] && isUnBlocked(grid, current->row + i, current->col + j))
					{
						Cell* child = new Cell(current->row + i, current->col + j);
						child->parent = current;
						neighbor.push(child);
						visit[child->row][child->col] = true;

						if (visit[dest.first][dest.second])
						{
							return tracePath(child, src);
						}
					}
				}
			}
		}
	}
	return std::make_pair(-1, -1);
}

/*---------------------------------------------------------------------------------------------*/

Enemy::Enemy()
{
	x_val = 0;
	y_val = 0;

	x_pos = 0;
	y_pos = 0;

	width_frame = 0;
	height_frame = 0;

	type = -1;

	is_freeze = false;
	is_dead = false;
	is_speed_up = false;
	is_coll = false;

	mix_die = Mix_LoadWAV("Sound/die.wav");
	mix_freeze = Mix_LoadWAV("Sound/monster.wav");

	status = WALK_DOWN;
}

Enemy::~Enemy()
{
	Mix_FreeChunk(mix_die);
	mix_die = NULL;
	Mix_FreeChunk(mix_freeze);
	mix_freeze = NULL;
}

void Enemy::handleMove(Player& pPlayer, Map& main_map_)
{
	x_val = 0;
	y_val = 0;

	if (status == FREEZE || status == DEAD || status == WALK_NONE)
	{
		x_val = 0;
		y_val = 0;
	}
	else if (status == WALK_LEFT)
	{
		x_val -= enemy_speed[type];
	}
	else if (status == WALK_RIGHT)
	{
		x_val += enemy_speed[type];
	}
	else if (status == WALK_UP)
	{
		y_val -= enemy_speed[type];
	}
	else if (status == WALK_DOWN)
	{
		y_val += enemy_speed[type];
	}

	if (!is_dead)
	{
		if (!is_freeze)
		{
			if (type == 1)
			{
				//Random move
				srand(SDL_GetTicks());
				if (!checkToMap(pPlayer, main_map_))
				{
					status = rand() % 4 + 1;
				}
			}
			else
			{
				int enemy_x = (x_pos + 0.5 * width_frame) / CELL_SIZE;
				int enemy_y = (y_pos + 0.5 * height_frame) / CELL_SIZE;

				int player_x = (pPlayer.getXPos() + 0.5 * pPlayer.getWidthFrame()) / CELL_SIZE;
				int player_y = (pPlayer.getYPos() + 0.75 * pPlayer.getHeightFrame()) / CELL_SIZE;
				Pair next_step = bfs(main_map_.tile_map, std::make_pair(enemy_y, enemy_x), std::make_pair(player_y, player_x));
				if (next_step.first != -1 && next_step.second != -1)
				{
					//Found and follow
					int y = next_step.first;
					int x = next_step.second;

					if (x > enemy_x)
					{
						status = WALK_RIGHT;
					}
					else if (x < enemy_x)
					{
						status = WALK_LEFT;
					}
					else if (y > enemy_y)
					{
						status = WALK_DOWN;
					}
					else if (y < enemy_y)
					{
						status = WALK_UP;
					}
					checkToMap(pPlayer, main_map_);
				}
				else 
				{
					//Random move
					srand(SDL_GetTicks());
					if (!checkToMap(pPlayer, main_map_))
					{
						status = rand() % 4 + 1;
					}
				}
			}
		}
		else
		{
			status = FREEZE;
			Uint32 current_freeze_time = SDL_GetTicks();
			if (current_freeze_time >= freeze_time)
			{
				is_freeze = false;
				status = WALK_DOWN;
				enemy_life[type]++;
			}
			else
			{
				checkDead(pPlayer);
			}
		}
	}
}

void Enemy::showEnemy(SDL_Renderer* des)
{
	switch (type)
	{
	case 1:
		if (status == FREEZE)
		{
			loadImg("Enemy/1_Freeze.png", des);
		}
		else if (status == WALK_LEFT)
		{
			loadImg("Enemy/1_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			loadImg("Enemy/1_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			loadImg("Enemy/1_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			loadImg("Enemy/1_Down.png", des);
		}
		else if (status == DEAD)
		{
			loadImg("Enemy/1_Dead.png", des);
		}
		break;

	case 2:
		if (status == FREEZE)
		{
			loadImg("Enemy/2_Freeze.png", des);
		}
		else if (status == WALK_LEFT)
		{
			loadImg("Enemy/2_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			loadImg("Enemy/2_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			loadImg("Enemy/2_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			loadImg("Enemy/2_Down.png", des);
		}
		else if (status == DEAD)
		{
			loadImg("Enemy/2_Dead.png", des);
		}
		break;

	case 3:
		//Display blood
		int i = 0;
		while (i < 10)
		{
			if (i < (enemy_life[type] / 20) )
			{
				loadImg("Enemy/life_boss.png", des);
			}
			else
			{
				loadImg("Enemy/clone_life_boss.png", des);
			}
			SDL_Rect renderQuad_ = { ((i + 1.5) * 10) + rect.x, rect.y - 2 * rect.h, rect.w, rect.h };
			SDL_RenderCopy(des, pObject, NULL, &renderQuad_);
			i++;
		}

		if (status == FREEZE)
		{
			loadImg("Enemy/3_Freeze.png", des);
		}
		else if (status == WALK_LEFT)
		{
			loadImg("Enemy/3_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			loadImg("Enemy/3_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			loadImg("Enemy/3_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			loadImg("Enemy/3_Down.png", des);
		}
		else if (status == DEAD)
		{
			loadImg("Enemy/3_Dead.png", des);
		}
		break;
	}

	width_frame = rect.w;
	height_frame = rect.h;
	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, NULL, &renderQuad);
}

bool Enemy::checkToMap(Player& pPlayer, Map& main_map_)
{
	x_pos += x_val;
	y_pos += y_val;

	is_coll = isCollideExplosion(main_map_);

	if (!is_coll)
	{
		return isCollideCell(main_map_);
	}
	return true;
}

void Enemy::checkDead(Player& pPLayer)
{
	int center_player_x = pPLayer.getXPos() + 0.5*pPLayer.getWidthFrame();
	int center_player_y = pPLayer.getYPos() + 0.5*pPLayer.getHeightFrame();

	int x1 = x_pos;
	int x2 = x_pos + width_frame;
	int y1 = y_pos;
	int y2 = y_pos + height_frame;

	if ((center_player_x > x1 && center_player_x < x2 && center_player_y > y1 && center_player_y < y2))
	{
		Mix_PlayChannel(-1, mix_die, 0);
		status = DEAD;
		is_dead = true;
		dead_time = SDL_GetTicks() + DEAD_TIMER;
	}
}

bool Enemy::isCollideCell(Map& main_map_)
{
	int old_x_pos = x_pos - x_val;
	int old_y_pos = y_pos - y_val;

	int x1, x2;
	int y1, y2;

	real_y_pos = y_pos + 0.4 * height_frame;

	//Check for collision of enemies and obstacles

	x1 = (x_pos + ERROR_NUM) / CELL_SIZE;
	x2 = (x_pos + width_frame - ERROR_NUM) / CELL_SIZE;

	y1 = (real_y_pos + ERROR_NUM) / CELL_SIZE;
	y2 = (y_pos + height_frame - 5*ERROR_NUM) / CELL_SIZE;

	int main_top_right = main_map_.tile_map[y1][x2];
	int main_bot_right = main_map_.tile_map[y2][x2];
	int main_top_left = main_map_.tile_map[y1][x1];
	int main_bot_left = main_map_.tile_map[y2][x1];

	bool check_main_top_right = main_top_right != BLANK_CELL;
	bool check_main_top_left = main_top_left != BLANK_CELL;
	bool check_main_bot_right = main_bot_right != BLANK_CELL;
	bool check_main_bot_left = main_bot_left != BLANK_CELL;

	//move right
	if (x_val > 0)
	{
		if (check_main_top_right || check_main_bot_right)
		{
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * CELL_SIZE;
			int head_lag_part = (y1 + 1) * CELL_SIZE - real_y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_right && main_map_.tile_map[y2 - 1][x1 + 1] == BLANK_CELL
				&& type == 2)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
				int y3 = y_pos / CELL_SIZE;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y1 + 1][x1 + 1] == BLANK_CELL
				&& type == 2)
			{
				y_pos += head_lag_part + ERROR_NUM;
			}
			else
			{
				x_pos = old_x_pos;
				x_val = 0;
				return false;
			}
		}
	}
	//move left
	else if (x_val < 0)
	{
		if (check_main_top_left || check_main_bot_left)
		{
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * CELL_SIZE;
			int head_lag_part = (y1 + 1) * CELL_SIZE - real_y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y2 - 1][x2 - 1] == BLANK_CELL
				&& type == 2)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_left && main_map_.tile_map[y1 + 1][x2 - 1] == BLANK_CELL
				&& type == 2)
			{
				y_pos += head_lag_part + ERROR_NUM;
			}
			else
			{
				x_pos = old_x_pos;
				x_val = 0;
				return false;
			}
		}
	}
	//move up
	if (y_val > 0)
	{
		if (check_main_bot_right || check_main_bot_left)
		{
			int foot_right_lag_part = x_pos + width_frame - (x1 + 1) * CELL_SIZE;
			int foot_left_lag_part = (x1 + 1) * CELL_SIZE - x_pos;
			if (foot_left_lag_part <= LIMIT_LAG && foot_left_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y1 + 1][x2] == BLANK_CELL
				&& type == 2)
			{
				x_pos += foot_left_lag_part + ERROR_NUM;
			}
			else if (foot_right_lag_part <= LIMIT_LAG && foot_right_lag_part > 0
				&& check_main_bot_right && main_map_.tile_map[y1 + 1][x1] == BLANK_CELL
				&& type == 2)
			{
				x_pos -= foot_right_lag_part + ERROR_NUM;
			}
			else
			{
				y_pos = old_y_pos;
				y_val = 0;

				return false;
			}
		}
	}
	//move down
	else if (y_val < 0)
	{
		if (check_main_top_right || check_main_top_left)
		{
			int head_right_lag_part = x_pos + width_frame - (x1 + 1) * CELL_SIZE;
			int head_left_lag_part = (x1 + 1) * CELL_SIZE - x_pos;
			if (head_left_lag_part <= LIMIT_LAG && head_left_lag_part >= 0
				&& check_main_top_left && main_map_.tile_map[y2 - 1][x2] == BLANK_CELL
				&& type == 2)
			{
				x_pos += head_left_lag_part + ERROR_NUM;
			}
			else if (head_right_lag_part <= LIMIT_LAG && head_right_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y2 - 1][x1] == BLANK_CELL
				&& type == 2)
			{
				x_pos -= head_right_lag_part + ERROR_NUM;
			}
			else
			{
				y_pos = old_y_pos;
				y_val = 0;
				return false;
			}
		}
	}

	return true;
}

bool Enemy::isCollideExplosion(Map& main_map_)
{
	int old_x_pos = x_pos - x_val;
	int old_y_pos = y_pos - y_val;

	int x1, x2, x3, x4;
	int y1, y2, y3, y4;

	//Check for collision of enemies and bomb

	x1 = (x_pos + ERROR_NUM) / CELL_SIZE;
	x2 = (x_pos + width_frame - ERROR_NUM) / CELL_SIZE;

	y1 = (y_pos + ERROR_NUM) / CELL_SIZE;
	y2 = (y_pos + height_frame - ERROR_NUM) / CELL_SIZE;

	x3 = (x_pos + 1/3 * width_frame) / CELL_SIZE;
	x4 = (x_pos + 2/3 * width_frame) / CELL_SIZE;

	y3 = (y_pos + 1/3 * height_frame) / CELL_SIZE;
	y4 = (y_pos + 2/3 * height_frame) / CELL_SIZE;

	int main_top_right = main_map_.tile_map[y1][x2];
	int main_bot_right = main_map_.tile_map[y2][x2];
	int main_top_left = main_map_.tile_map[y1][x1];
	int main_bot_left = main_map_.tile_map[y2][x1];

	int main_mid_top_right = main_map_.tile_map[y3][x4];
	int main_mid_bot_right = main_map_.tile_map[y4][x4];
	int main_mid_top_left = main_map_.tile_map[y3][x3];
	int main_mid_bot_left = main_map_.tile_map[y4][x3];

	bool check_main_top_right = main_top_right == DEAD_CELL;
	bool check_main_top_left = main_top_left == DEAD_CELL;
	bool check_main_bot_right = main_bot_right == DEAD_CELL;
	bool check_main_bot_left = main_bot_left == DEAD_CELL;

	bool check_main_mid_top_right = main_mid_top_right == DEAD_CELL;
	bool check_main_mid_top_left = main_mid_top_left == DEAD_CELL;
	bool check_main_mid_bot_right = main_mid_bot_right == DEAD_CELL;
	bool check_main_mid_bot_left = main_mid_bot_left == DEAD_CELL;

	if (check_main_top_right || check_main_top_left || check_main_bot_right || check_main_bot_left ||
		check_main_mid_top_right || check_main_mid_top_left || check_main_mid_bot_right || check_main_mid_bot_left)
	{
		freeze_time = SDL_GetTicks() + FREEZE_TIMER;
			enemy_life[type]--;
			if (is_freeze == false)
			{
				Mix_PlayChannel(-1, mix_freeze, 0);
			}
		if (enemy_life[type] == 0)
		{
			is_freeze = true;
		}
		return true;
	}

	return false;
}

void Enemy::increaseEnemySpeed()
{
	if (!is_speed_up)
	{
		enemy_speed[type] += 4;
		is_speed_up = true;
	}
}



