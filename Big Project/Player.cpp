#include "Player.h"

Player::Player()
{
	frame = 0;
	frame_effect = 1;

	width_frame = 0;
	height_frame = 0;

	is_coll_explosion = false;
	is_coll_enemy = false;
	limit_coll = false;

	time_protect = 0;

	life = 3;
	bomb_limit = 1;
	bomb_power = 1;
	player_speed = 4;

	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;

	status = WALK_NONE;
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;

}

Player::~Player()
{
	pbomb_list.clear();
	SDL_RemoveTimer(time_protect);
}

void Player::handleInputAction(SDL_Event& event, SDL_Renderer* screen, Map& main_map_)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.up = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			status = WALK_RIGHT;
			input_type.left = 0;
			input_type.right = 1;
			input_type.up = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_UP:
		{
			status = WALK_UP;
			input_type.left = 0;
			input_type.right = 0;
			input_type.up = 1;
			input_type.down = 0;
		}
		break;

		case SDLK_DOWN:
		{
			status = WALK_DOWN;
			input_type.left = 0;
			input_type.right = 0;
			input_type.up = 0;
			input_type.down = 1;

		}
		break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			input_type.left = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			input_type.right = 0;
		}
		break;

		case SDLK_UP:
		{
			input_type.up = 0;
		}
		break;

		case SDLK_DOWN:
		{
			input_type.down = 0;
		}
		break;

		case SDLK_SPACE:
		{
			if (pbomb_list.size() < bomb_limit)
			{
				int x, y;
				if (status == WALK_LEFT)
				{
					x = ((x_pos + width_frame - ERROR_NUM) / CELL_SIZE);
				}
				else
				{
					x = ((x_pos + ERROR_NUM) / CELL_SIZE);
				}
				y = ((y_pos + 0.7 * height_frame - ERROR_NUM) / CELL_SIZE);

				if (main_map_.tile_map[y][x] == BLANK_CELL)
				{
					Bomb* pbomb = new Bomb();
					pbomb->setScreen(screen);
					pbomb->plantBomb(x, y);
					pbomb_list.push_back(pbomb);
					main_map_.tile_map[y][x] = BOMB_PLANTED;
				}
			}
		}
		break;
		}
	}
}

void Player::handleMove(Map& main_map_, Map& item_map_)
{
	x_val = 0;
	y_val = 0;
	if (input_type.left == 1)
	{
		x_val -= player_speed;
	}
	else if (input_type.right == 1)
	{
		x_val += player_speed;
	}
	else if (input_type.up == 1)
	{
		y_val -= player_speed;
	}
	else if (input_type.down == 1)
	{
		y_val += player_speed;
	}
	checkToMap(main_map_, item_map_);
}

void Player::explodeBomb(SDL_Renderer* des, Bomb* bomb_,
	Map& main_map_, Map& item_map_)
{
	int x = bomb_->getX();
	int y = bomb_->getY();

	if (bomb_->getLim())
	{
		for (int i = -1; i >= -bomb_power; i--)
		{
			int x1 = x + i;

			if (main_map_.tile_map[y][x1] <= 10 && main_map_.tile_map[y][x1] > 0)
			{
				break;
			}

			bomb_->setLeft(i);

			if (item_map_.tile_map[y][x1] != BLANK_ITEM && main_map_.tile_map[y][x1] == BLANK_CELL)
			{
				item_map_.tile_map[y][x1] = BLANK_ITEM;
			}

			if (main_map_.tile_map[y][x1] != BOMB_PLANTED)
			{
				main_map_.tile_map[y][x1] = DEAD_CELL;
				break;
			}
		}

		for (int i = 1; i <= bomb_power; i++)
		{
			int x1 = x + i;

			if (main_map_.tile_map[y][x1] <= NUMBER_OF_LIMIT_CELL && main_map_.tile_map[y][x1] > 0)
			{
				break;
			}

			bomb_->setRight(i);

			if (item_map_.tile_map[y][x1] != BLANK_ITEM && main_map_.tile_map[y][x1] == BLANK_CELL)
			{
				item_map_.tile_map[y][x1] = BLANK_ITEM;
			}

			if (main_map_.tile_map[y][x1] != BOMB_PLANTED)
			{
				main_map_.tile_map[y][x1] = DEAD_CELL;
				break;
			}
		}

		for (int i = -1; i >= -bomb_power; i--)
		{
			int y1 = y + i;

			if (main_map_.tile_map[y1][x] <= 10 && main_map_.tile_map[y1][x] > 0)
			{
				break;
			}

			bomb_->setTop(i);

			if (item_map_.tile_map[y1][x] != BLANK_ITEM && main_map_.tile_map[y1][x] == BLANK_CELL)
			{
				item_map_.tile_map[y1][x] = BLANK_ITEM;
			}

			if (main_map_.tile_map[y1][x] != BOMB_PLANTED)
			{
				main_map_.tile_map[y1][x] = DEAD_CELL;
				break;
			}

		}

		for (int i = 1; i <= bomb_power; i++)
		{
			int y1 = y + i;

			if (main_map_.tile_map[y1][x] <= 10 && main_map_.tile_map[y1][x] > 0)
			{
				break;
			}

			bomb_->setBot(i);

			if (item_map_.tile_map[y1][x] != BLANK_ITEM && main_map_.tile_map[y1][x] == BLANK_CELL)
			{
				item_map_.tile_map[y1][x] = BLANK_ITEM;
			}

			if (main_map_.tile_map[y1][x] != BOMB_PLANTED)
			{
				main_map_.tile_map[y1][x] = DEAD_CELL;
				break;
			}
		}

		main_map_.tile_map[y][x] = DEAD_CELL;
		bomb_->setLim(false);
	}
	bomb_->displayExplosion(des);
}


void Player::showPlayer(SDL_Renderer* des)
{
	if (status == WALK_NONE)
	{
		loadClipImg("Player/down.png", des);
	}
	else if (status == WALK_LEFT)
	{
		loadClipImg("Player/left.png", des);
	}
	else if (status == WALK_RIGHT)
	{
		loadClipImg("Player/right.png", des);
	}
	else if (status == WALK_UP)
	{
		loadClipImg("Player/up.png", des);
	}
	else if (status == WALK_DOWN)
	{
		loadClipImg("Player/down.png", des);
	}
	else if (status == DEAD)
	{
		loadImg("Player/dead.png", des);
	}

	setClip();

	if (input_type.left == 1 ||
		input_type.right == 1 ||
		input_type.up == 1 ||
		input_type.down == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}

	if (frame >= PLAYER_FRAMES)
		frame = 0;

	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);

	SDL_TimerID current_time = SDL_GetTicks();

	if (current_time <= time_protect)
	{
		char tmp = frame_effect + '0';
		std::string name_ = "Player/";
		name_ += tmp;
		name_ += ".png";
		loadImg(name_.c_str(), des);
		SDL_RenderCopy(des, pObject, current_clip, &renderQuad);

		if (frame_effect > 8) { frame_effect = 1; }
		else { frame_effect++; }
	}

	SDL_RemoveTimer(current_time);
}

void Player::showBomb(SDL_Renderer* des, Map& main_map_, Map& item_map_)
{
	for (int i = 0; i < pbomb_list.size(); i++)
	{
		SDL_TimerID current_timer_id = SDL_GetTicks();
		int bomb_x = pbomb_list[i]->getX();
		int bomb_y = pbomb_list[i]->getY();
		if (current_timer_id >= pbomb_list[i]->getExplosionTimer())
		{
			//main_map_.tile_map[bomb_y][bomb_x] = DEAD_CELL;
			pbomb_list[i]->clearBomb(main_map_);
			pbomb_list[i]->Free();
			pbomb_list[i] = NULL;
			delete pbomb_list[i];
			pbomb_list.erase(pbomb_list.begin() + i);
		}
		else if (current_timer_id >= pbomb_list[i]->getBombTimer())
		{
			main_map_.tile_map[bomb_y][bomb_x] = DEAD_CELL;
			explodeBomb(des, pbomb_list[i], main_map_, item_map_);
		}
		else
		{
			pbomb_list[i]->displayBomb(des);
		}
		SDL_RemoveTimer(current_timer_id);
	}
}


bool Player::loadClipImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::loadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	width_frame = rect.w / PLAYER_FRAMES;
	height_frame = rect.h;

	return true;
}

void Player::setClip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < PLAYER_FRAMES; i++)
		{
			frame_clip[i].x = i*width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void Player::setSpawn(const float& x_, const float& y_)
{
	x_pos = x_ * CELL_SIZE; 
	y_pos = y_ * CELL_SIZE;

	time_protect = SDL_GetTicks() + PROTECT_TIMER;
	status = WALK_NONE;
}


void Player::checkCollideExplosion(const int& angle_1, const int& angle_2, const int& angle_3, const int& angle_4)
{
	is_coll_explosion = angle_1 == DEAD_CELL || angle_2 == DEAD_CELL || angle_3 == DEAD_CELL || angle_4 == DEAD_CELL;
	decreaseLife();
}

void Player::checkCollideEnemy(const SDL_Rect& rect_)
{
	int x1_pos_player = rect.x + ERROR_NUM;
	int x2_pos_player = rect.x + width_frame - ERROR_NUM;
	int y1_pos_player = rect.y + ERROR_NUM;
	int y2_pos_player = rect.y + height_frame - ERROR_NUM;

	int x1_pos_enemy = rect_.x + ERROR_NUM;
	int x2_pos_enemy = rect_.x + rect_.w - ERROR_NUM;
	int y1_pos_enemy = rect_.y + ERROR_NUM;
	int y2_pos_enemy = rect_.y + rect_.h - ERROR_NUM;

	if ((x1_pos_player >= x1_pos_enemy && x1_pos_player <= x2_pos_enemy && y1_pos_player >= y1_pos_enemy && y1_pos_player <= y2_pos_enemy) ||
		(x1_pos_player >= x1_pos_enemy && x1_pos_player <= x2_pos_enemy && y2_pos_player >= y1_pos_enemy && y2_pos_player <= y2_pos_enemy) ||
		(x2_pos_player >= x1_pos_enemy && x2_pos_player <= x2_pos_enemy && y1_pos_player >= y1_pos_enemy && y1_pos_player <= y2_pos_enemy) ||
		(x2_pos_player >= x1_pos_enemy && x2_pos_player <= x2_pos_enemy && y2_pos_player >= y1_pos_enemy && y2_pos_player <= y2_pos_enemy))
	{
		is_coll_enemy = true;
		decreaseLife();
	}
	else
	{
		is_coll_enemy = false;
	}
}

void Player::checkToMap(Map& main_map_, Map& item_map_)
{
	int old_x_pos = x_pos;
	int old_y_pos = y_pos;

	x_pos += x_val;
	y_pos += y_val;

	int x1, x2;
	int y1, y2;

	//Check for collision of player and obstacles

	x1 = (x_pos + ERROR_NUM) / CELL_SIZE;
	x2 = (x_pos + width_frame - ERROR_NUM) / CELL_SIZE;

	y1 = (y_pos + ERROR_NUM) / CELL_SIZE;
	y2 = (y_pos + height_frame - ERROR_NUM) / CELL_SIZE;

	int main_top_right = main_map_.tile_map[y1][x2];
	int main_bot_right = main_map_.tile_map[y2][x2];
	int main_top_left = main_map_.tile_map[y1][x1];
	int main_bot_left = main_map_.tile_map[y2][x1];

	checkCollideExplosion(main_top_right, main_bot_right, main_top_left, main_bot_left);
	
	bool check_main_top_right = main_top_right != BLANK_CELL && main_top_right != BOMB_PLANTED;
	bool check_main_top_left = main_top_left != BLANK_CELL && main_top_left != BOMB_PLANTED;
	bool check_main_bot_right = main_bot_right != BLANK_CELL && main_bot_right != BOMB_PLANTED;
	bool check_main_bot_left = main_bot_left != BLANK_CELL && main_bot_left != BOMB_PLANTED;

	//move right
	if (x_val > 0)
	{
		if (check_main_top_right || check_main_bot_right)
		{
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * CELL_SIZE;
			int head_lag_part = (y1 + 1) * CELL_SIZE - y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_right && main_map_.tile_map[y2 - 1][x1 + 1] == BLANK_CELL)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
				int y3 = y_pos / CELL_SIZE;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y1 + 1][x1 + 1] == BLANK_CELL)
			{
				y_pos += head_lag_part + ERROR_NUM;
			}
			else
			{
				x_pos = old_x_pos;
				x_val = 0;
			}
		}

	}
	//move left
	else if (x_val < 0)
	{
		if (check_main_top_left || check_main_bot_left)
		{
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * CELL_SIZE;
			int head_lag_part = (y1 + 1) * CELL_SIZE - y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y2 - 1][x2 - 1] == BLANK_CELL)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_left && main_map_.tile_map[y1 + 1][x2 - 1] == BLANK_CELL)
			{
				y_pos += head_lag_part + ERROR_NUM;
			}
			else
			{
				x_pos = old_x_pos;
				x_val = 0;
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
				&& check_main_bot_left && main_map_.tile_map[y1 + 1][x2] == BLANK_CELL)
			{
				x_pos += foot_left_lag_part + ERROR_NUM;
			}
			else if (foot_right_lag_part <= LIMIT_LAG && foot_right_lag_part > 0
				&& check_main_bot_right && main_map_.tile_map[y1 + 1][x1] == BLANK_CELL)
			{
				x_pos -= foot_right_lag_part + ERROR_NUM;
			}
			else
			{
				y_pos = old_y_pos;
				y_val = 0;
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
				&& check_main_top_left && main_map_.tile_map[y2 - 1][x2] == BLANK_CELL)
			{
				x_pos += head_left_lag_part + ERROR_NUM;
			}
			else if (head_right_lag_part <= LIMIT_LAG && head_right_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y2 - 1][x1] == BLANK_CELL)
			{
				x_pos -= head_right_lag_part + ERROR_NUM;
			}
			else
			{
				y_pos = old_y_pos;
				y_val = 0;
			}
		}
	}


	//Check for collision of player and items
	x1 = (x_pos + 3*ERROR_NUM) / CELL_SIZE;
	x2 = (x_pos + width_frame - 3*ERROR_NUM) / CELL_SIZE;

	y1 = (y_pos + 3*ERROR_NUM) / CELL_SIZE;
	y2 = (y_pos + height_frame - 3*ERROR_NUM) / CELL_SIZE;

	int item_top_right = item_map_.tile_map[y1][x2];
	int item_bot_right = item_map_.tile_map[y2][x2];
	int item_top_left = item_map_.tile_map[y1][x1];
	int item_bot_left = item_map_.tile_map[y2][x1];

	if (item_top_left == BOMB_UP || item_bot_left == BOMB_UP || item_top_right == BOMB_UP || item_bot_right == BOMB_UP)
	{
		increaseBombLimit();
	}
	if (item_top_left == POWER_UP || item_bot_left == POWER_UP || item_top_right == POWER_UP || item_bot_right == POWER_UP)
	{
		increaseBombPower();
	}
	if (item_top_left == SPEED_UP || item_bot_left == SPEED_UP || item_top_right == SPEED_UP || item_bot_right == SPEED_UP)
	{
		increasePlayerSpeed();
	}

	if (item_top_left != BLANK_ITEM)
	{
		item_map_.tile_map[y1][x1] = BLANK_ITEM;
	}
	if (item_bot_left != BLANK_ITEM)
	{
		item_map_.tile_map[y2][x1] = BLANK_ITEM;
	}
	if (item_top_right != BLANK_ITEM)
	{
		item_map_.tile_map[y1][x2] = BLANK_ITEM;
	}
	if (item_bot_right != BLANK_ITEM)
	{
		item_map_.tile_map[y2][x2] = BLANK_ITEM;
	}

	//Check for collision of player and bombs 
	if (pbomb_list.size() != 0)
	{
		for (auto bomb : pbomb_list)
		{
			int bomb_x = bomb->getX();
			int bomb_y = bomb->getY();
			int bomb_x_pos = bomb_x * CELL_SIZE;
			int bomb_y_pos = bomb_y * CELL_SIZE;

			if ((y_pos + height_frame < bomb_y_pos) ||
				(y_pos > bomb_y_pos + CELL_SIZE) ||
				(x_pos + width_frame < bomb_x_pos) ||
				(x_pos > bomb_x_pos + CELL_SIZE))
			{
				main_map_.tile_map[bomb_y][bomb_x] = BLOCK_CELL;
			}
		}
	}
}


void Player::decreaseLife()
{
	if (is_coll_enemy || is_coll_explosion)
	{
		if (limit_coll == false)
		{
			SDL_TimerID current_time = SDL_GetTicks();
			if (current_time > time_protect)
			{
				life--;
				setSpawn(x_pos / CELL_SIZE, y_pos / CELL_SIZE);
				status = DEAD;
				std::cout << life << "\n";
			}
			limit_coll = true;
		}
	}
	else
	{
		limit_coll = false;
	}
}