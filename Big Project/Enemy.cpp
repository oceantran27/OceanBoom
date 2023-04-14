#include "Enemy.h"
#include <queue>
#include <cstring>

#define LIMIT_LAG 18

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
		parent = nullptr;
	}
	~Cell()
	{
		parent = NULL;
		delete(parent);
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
	return grid[row][col] == 0;
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


Enemy::Enemy()
{
	//enemy_speed;

	x_val = 0;
	y_val = 0;

	x_pos = 0;
	y_pos = 0;

	width_frame = 0;
	height_frame = 0;

	//frame = 0;
	type = -1;

	is_freeze = false;

	status = WALK_DOWN;
}

Enemy::~Enemy()
{
	//
}

//bool Enemy::LoadClipImg(std::string path, SDL_Renderer* screen)
//{
//	bool ret = BaseObject::LoadImg(path, screen);
//	if (ret == false)
//	{
//		return false;
//	}
//
//	width_frame = rect.w / ENEMY_FRAMES;
//	height_frame = rect.h;
//
//	return true;
//}
//
//void Enemy::SetClip()
//{
//	if (width_frame > 0 && height_frame > 0)
//	{
//		for (int i = 0; i < ENEMY_FRAMES; i++)
//		{
//			frame_clip[i].x = i * width_frame;
//			frame_clip[i].y = 0;
//			frame_clip[i].w = width_frame;
//			frame_clip[i].h = height_frame;
//		}
//	}
//}
	
void Enemy::EnemyShow(SDL_Renderer* des)
{
	switch (type)
	{
	case 1:
		if (status == FREEZE)
		{
			LoadImg("Enemy/1_Freeze.png", des);
		}
		else if (status == WALK_LEFT)
		{
			LoadImg("Enemy/1_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("Enemy/1_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("Enemy/1_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("Enemy/1_Down.png", des);
		}
		else if (status == DEAD)
		{
			LoadImg("Enemy/1_Dead.png", des);
		}
		break;

	case 2:
		if (status == FREEZE)
		{
			LoadImg("Enemy/2_Freeze.png", des);
		}
		else if (status == WALK_LEFT)
		{
			LoadImg("Enemy/2_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("Enemy/2_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("Enemy/2_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("Enemy/2_Down.png", des);
		}
		else if (status == DEAD)
		{
			LoadImg("Enemy/2_Dead.png", des);
		}
		break;

	case 3:
		if (status == FREEZE)
		{
			LoadImg("Enemy/3_Freeze.png", des);
		}
		else if (status == WALK_LEFT)
		{
			LoadImg("Enemy/3_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("Enemy/3_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("Enemy/3_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("Enemy/3_Down.png", des);
		}
		else if (status == DEAD)
		{
			LoadImg("Enemy/3_Dead.png", des);
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

bool Enemy::CheckToMap(Map& main_map_)
{
	x_pos += x_val;
	y_pos += y_val;
	if (checkBombCollision(main_map_))
	{
		return checkCellCollision(main_map_);
	}
}

void Enemy::HandleMove(const float& bomber_x_pos, const float& bomber_y_pos, Map& main_map_)
{
	x_val = 0;
	y_val = 0;

	if (status == FREEZE)
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

	if (!is_freeze)
	{
		if (type == 1)
		{
			srand(SDL_GetTicks());
			if (!CheckToMap(main_map_))
			{
				status = rand() % 4 + 1;
			}
		}
		else
		{
			int enemy_x, enemy_y;

			enemy_x = x_pos / TILE_SIZE;
			enemy_y = y_pos / TILE_SIZE;

			if (status == WALK_UP)
			{
				enemy_y = (y_pos + height_frame) / TILE_SIZE;
			}

			if (status == WALK_LEFT)
			{
				enemy_x = (x_pos + width_frame) / TILE_SIZE;
			}

			int bomber_x = bomber_x_pos / TILE_SIZE;
			int bomber_y = bomber_y_pos / TILE_SIZE;
			Pair next_step = bfs(main_map_.tile_map, std::make_pair(enemy_y, enemy_x), std::make_pair(bomber_y, bomber_x));
			if (next_step.first != -1 && next_step.second != -1)
			{
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
			}
			CheckToMap(main_map_);
		}
	}
	else
	{
		status = FREEZE;
		SDL_TimerID current_timer_id = SDL_GetTicks();
		if (current_timer_id >= timer_id)
		{
			is_freeze = false;
			status = WALK_DOWN;
		}
		SDL_RemoveTimer(current_timer_id);
	}
}


bool Enemy::checkCellCollision(Map& main_map_)
{
	int old_x_pos = x_pos - x_val;
	int old_y_pos = y_pos - y_val;

	int x1, x2;
	int y1, y2;

	//Check for collision of enemies and obstacles

	x1 = (x_pos + ERROR_NUM) / TILE_SIZE;
	x2 = (x_pos + width_frame - ERROR_NUM) / TILE_SIZE;

	y1 = (y_pos + ERROR_NUM) / TILE_SIZE;
	y2 = (y_pos + height_frame - ERROR_NUM) / TILE_SIZE;

	int main_top_right = main_map_.tile_map[y1][x2];
	int main_bot_right = main_map_.tile_map[y2][x2];
	int main_top_left = main_map_.tile_map[y1][x1];
	int main_bot_left = main_map_.tile_map[y2][x1];

	bool check_main_top_right = main_top_right != BLANK_TILE;
	bool check_main_top_left = main_top_left != BLANK_TILE;
	bool check_main_bot_right = main_bot_right != BLANK_TILE;
	bool check_main_bot_left = main_bot_left != BLANK_TILE;

	//move right
	if (x_val > 0)
	{
		if (check_main_top_right || check_main_bot_right)
		{
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * TILE_SIZE;
			int head_lag_part = (y1 + 1) * TILE_SIZE - y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_right && main_map_.tile_map[y2 - 1][x1 + 1] == BLANK_TILE)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
				int y3 = y_pos / TILE_SIZE;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y1 + 1][x1 + 1] == BLANK_TILE)
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
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * TILE_SIZE;
			int head_lag_part = (y1 + 1) * TILE_SIZE - y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y2 - 1][x2 - 1] == BLANK_TILE)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_left && main_map_.tile_map[y1 + 1][x2 - 1] == BLANK_TILE)
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
			int foot_right_lag_part = x_pos + width_frame - (x1 + 1) * TILE_SIZE;
			int foot_left_lag_part = (x1 + 1) * TILE_SIZE - x_pos;
			if (foot_left_lag_part <= LIMIT_LAG && foot_left_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y1 + 1][x2] == BLANK_TILE)
			{
				x_pos += foot_left_lag_part + ERROR_NUM;
			}
			else if (foot_right_lag_part <= LIMIT_LAG && foot_right_lag_part > 0
				&& check_main_bot_right && main_map_.tile_map[y1 + 1][x1] == BLANK_TILE)
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
			int head_right_lag_part = x_pos + width_frame - (x1 + 1) * TILE_SIZE;
			int head_left_lag_part = (x1 + 1) * TILE_SIZE - x_pos;
			if (head_left_lag_part <= LIMIT_LAG && head_left_lag_part >= 0
				&& check_main_top_left && main_map_.tile_map[y2 - 1][x2] == BLANK_TILE)
			{
				x_pos += head_left_lag_part + ERROR_NUM;
			}
			else if (head_right_lag_part <= LIMIT_LAG && head_right_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y2 - 1][x1] == BLANK_TILE)
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

bool Enemy::checkBombCollision(Map& main_map_)
{
	int old_x_pos = x_pos - x_val;
	int old_y_pos = y_pos - y_val;

	int x1, x2;
	int y1, y2;

	//Check for collision of enemies and bomb

	x1 = (x_pos + 3*ERROR_NUM) / TILE_SIZE;
	x2 = (x_pos + width_frame - 3*ERROR_NUM) / TILE_SIZE;

	y1 = (y_pos + 3*ERROR_NUM) / TILE_SIZE;
	y2 = (y_pos + height_frame - 3*ERROR_NUM) / TILE_SIZE;

	int main_top_right = main_map_.tile_map[y1][x2];
	int main_bot_right = main_map_.tile_map[y2][x2];
	int main_top_left = main_map_.tile_map[y1][x1];
	int main_bot_left = main_map_.tile_map[y2][x1];

	bool check_main_top_right = main_top_right == DEAD_TILE;
	bool check_main_top_left = main_top_left == DEAD_TILE;
	bool check_main_bot_right = main_bot_right == DEAD_TILE;
	bool check_main_bot_left = main_bot_left == DEAD_TILE;

	if (check_main_top_right || check_main_top_left || check_main_bot_right || check_main_bot_left)
	{
		timer_id = SDL_GetTicks() + FREEZE_TIMER;
		is_freeze = true;
		return false;
	}

	return true;
}