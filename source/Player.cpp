#include "Player.h"

Player::Player()
{
	limit_move_sound = 0;

	frame = 0;
	frame_effect = 1;

	width_frame = 0;
	height_frame = 0;

	is_coll_explosion = false;
	is_coll_enemy = false;
	limit_coll = false;

	time_protect = 0;

	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;

	star = 0;
	mark = 0;
	life = 3;
	num_bomb = 1;
	bomb_power = 1;
	player_speed = 4;

	status = WALK_NONE;
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;

	mix_move = Mix_LoadWAV("Sound/move.wav");
	mix_plant = Mix_LoadWAV("Sound/plant.wav");
	mix_damage = Mix_LoadWAV("Sound/damage.wav");
	mix_die = Mix_LoadWAV("Sound/die.wav");
	mix_item = Mix_LoadWAV("Sound/item.wav");
	mix_explosion = Mix_LoadWAV("Sound/boom_bang.wav");

}

Player::~Player()
{
	pbomb_list.clear();
	Mix_FreeChunk(mix_move);
	mix_move = NULL;
	Mix_FreeChunk(mix_plant);
	mix_plant = NULL;
	Mix_FreeChunk(mix_damage);
	mix_damage = NULL;
	Mix_FreeChunk(mix_die);
	mix_die = NULL;
	Mix_FreeChunk(mix_item);
	mix_item = NULL;
	Mix_FreeChunk(mix_explosion);
	mix_explosion = NULL;


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

		if (limit_move_sound == 4) 
		{ 
			Mix_PlayChannel(-1, mix_move, 0); 
			limit_move_sound = 0;
		}
		else { limit_move_sound++; }
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			input_type.left = 0;
			Mix_PlayChannel(-1, mix_move, 0);
		}
		break;

		case SDLK_RIGHT:
		{
			input_type.right = 0;
			Mix_PlayChannel(-1, mix_move, 0);

		}
		break;

		case SDLK_UP:
		{
			input_type.up = 0;
			Mix_PlayChannel(-1, mix_move, 0);

		}
		break;

		case SDLK_DOWN:
		{
			input_type.down = 0;
			Mix_PlayChannel(-1, mix_move, 0);

		}
		break;

		case SDLK_SPACE:
		{
			if (pbomb_list.size() < num_bomb)
			{
				int x, y;
				x = ((x_pos + 0.5 * width_frame - ERROR_NUM) / CELL_SIZE);
				y = ((y_pos + 0.75 * height_frame - ERROR_NUM) / CELL_SIZE);

				if (main_map_.tile_map[y][x] == BLANK_CELL)
				{
					Bomb* pbomb = new Bomb();
					pbomb->setScreen(screen);
					pbomb->plantBomb(x, y);
					pbomb_list.push_back(pbomb);
					main_map_.tile_map[y][x] = BOMB_PLANTED;

					Mix_PlayChannel(-1, mix_plant, 0);
				}
			}
		}
		break;
		}
	}

	if (status == WALK_NONE)
	{
		input_type.left = 0;
		input_type.right = 0;
		input_type.up = 0;
		input_type.down = 0;
	}
}

void Player::handleMove(Map& main_map_, Map& item_map_)
{
	x_val = 0;
	y_val = 0;

	if (status != DEAD && status != WALK_NONE)
	{
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
}

void Player::explodeBomb(SDL_Renderer* des, Bomb* bomb_,
	Map& main_map_, Map& item_map_)
{
	int x = bomb_->getX();
	int y = bomb_->getY();

	if (bomb_->getLim())
	{
		Mix_PlayChannel(-1, mix_explosion, 0);

		for (int i = 0; i >= -bomb_power; i--)
		{
			int x1 = x + i;

			if (main_map_.tile_map[y][x1] <= NUMBER_OF_LIMIT_CELL && main_map_.tile_map[y][x1] > BLANK_CELL)
			{
				break;
			}

			if (item_map_.tile_map[y][x1] != BLANK_ITEM && main_map_.tile_map[y][x1] == BLANK_CELL)
			{
				item_map_.tile_map[y][x1] = BLANK_ITEM;
			}

			if (main_map_.tile_map[y][x1] != BLANK_CELL && main_map_.tile_map[y][x1] != BLOCK_CELL && main_map_.tile_map[y][x1] != DEAD_CELL)
			{
				main_map_.tile_map[y][x1] = BLANK_CELL;
				break;
			}
			main_map_.tile_map[y][x1] = DEAD_CELL;
			bomb_->setLeft(i);
		}

		for (int i = 0; i <= bomb_power; i++)
		{
			int x1 = x + i;

			if (main_map_.tile_map[y][x1] <= NUMBER_OF_LIMIT_CELL && main_map_.tile_map[y][x1] > BLANK_CELL)
			{
				break;
			}

			if (item_map_.tile_map[y][x1] != BLANK_ITEM && main_map_.tile_map[y][x1] == BLANK_CELL)
			{
				item_map_.tile_map[y][x1] = BLANK_ITEM;
			}

			if (main_map_.tile_map[y][x1] != BLANK_CELL && main_map_.tile_map[y][x1] != BLOCK_CELL && main_map_.tile_map[y][x1] != DEAD_CELL)
			{
				main_map_.tile_map[y][x1] = BLANK_CELL;
				break;
			}
			main_map_.tile_map[y][x1] = DEAD_CELL;
			bomb_->setRight(i);

		}

		for (int i = 0; i >= -bomb_power; i--)
		{
			int y1 = y + i;

			if (main_map_.tile_map[y1][x] <= NUMBER_OF_LIMIT_CELL && main_map_.tile_map[y1][x] > BLANK_CELL)
			{
				break;
			}

			if (item_map_.tile_map[y1][x] != BLANK_ITEM && main_map_.tile_map[y1][x] == BLANK_CELL)
			{
				item_map_.tile_map[y1][x] = BLANK_ITEM;
			}


			if (main_map_.tile_map[y1][x] != BLANK_CELL && main_map_.tile_map[y1][x] != BLOCK_CELL && main_map_.tile_map[y1][x] != DEAD_CELL)
			{
				main_map_.tile_map[y1][x] = BLANK_CELL;
				break;
			}

			main_map_.tile_map[y1][x] = DEAD_CELL;
			bomb_->setTop(i);
		}

		for (int i = 0; i <= bomb_power; i++)
		{
			int y1 = y + i;

			if (main_map_.tile_map[y1][x] <= NUMBER_OF_LIMIT_CELL && main_map_.tile_map[y1][x] > BLANK_CELL)
			{
				break;
			}

			if (item_map_.tile_map[y1][x] != BLANK_ITEM && main_map_.tile_map[y1][x] == BLANK_CELL)
			{
				item_map_.tile_map[y1][x] = BLANK_ITEM;
			}

			if (main_map_.tile_map[y1][x] != BLANK_CELL && main_map_.tile_map[y1][x] != BLOCK_CELL && main_map_.tile_map[y1][x] != DEAD_CELL)
			{
				main_map_.tile_map[y1][x] = BLANK_CELL;
				break;
			}

			main_map_.tile_map[y1][x] = DEAD_CELL;
			bomb_->setBot(i);
		}
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

	Uint32 current_time = SDL_GetTicks();

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
}

void Player::showBomb(SDL_Renderer* des, Map& main_map_, Map& item_map_)
{
	for (int i = 0; i < pbomb_list.size(); i++)
	{
		Uint32 current_timer_id = SDL_GetTicks();
		int bomb_x = pbomb_list[i]->getX();
		int bomb_y = pbomb_list[i]->getY();
		if (current_timer_id >= pbomb_list[i]->getExplosionTimer())
		{
			main_map_.tile_map[bomb_y][bomb_x] = BLANK_CELL;
			pbomb_list[i]->clearBomb(main_map_, item_map_);
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
	x_val = 0;
	y_val = 0;
}


void Player::checkCollideExplosion(const int& angle_1, const int& angle_2, const int& angle_3, const int& angle_4)
{
	is_coll_explosion = angle_1 == DEAD_CELL || angle_2 == DEAD_CELL || angle_3 == DEAD_CELL || angle_4 == DEAD_CELL;
	decreaseLife();
}

void Player::checkCollideEnemy(const SDL_Rect& rect_)
{
	float x1_pos_player = x_pos + ERROR_NUM;
	float x2_pos_player = x_pos + width_frame - ERROR_NUM;
	float y1_pos_player = y_pos + 0.35 * height_frame + ERROR_NUM;
	float y2_pos_player = y_pos + height_frame - ERROR_NUM;

	float x1_pos_enemy = rect_.x + ERROR_NUM;
	float x2_pos_enemy = rect_.x + rect_.w - ERROR_NUM;
	float y1_pos_enemy = rect_.y + 0.35 * rect_.h + ERROR_NUM;
	float y2_pos_enemy = rect_.y + rect_.h - ERROR_NUM;

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
	real_y_pos = y_pos + 0.4 * height_frame;

	int x1, x2;
	int y1, y2;

	//Check for collision of player and obstacles

	x1 = (x_pos + 5*ERROR_NUM) / CELL_SIZE;
	x2 = (x_pos + width_frame - 5*ERROR_NUM) / CELL_SIZE;

	y1 = (real_y_pos + ERROR_NUM) / CELL_SIZE;
	y2 = (y_pos + height_frame - 5*ERROR_NUM) / CELL_SIZE;

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
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_right && main_map_.tile_map[y2 - 1][x1 + 1] == BLANK_CELL)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
				int y3 = y_pos / CELL_SIZE;
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
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y2 - 1][x2 - 1] == BLANK_CELL)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
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

	int x_center = (x_pos + 0.5 * width_frame) / CELL_SIZE;
	int y_center = (y_pos + 0.5 * height_frame) / CELL_SIZE;
	int item_center = item_map_.tile_map[y_center][x_center];


	if (item_center == BOMB_UP)
	{
		increaseNumBomb();
	}
	if (item_center == POWER_UP)
	{
		increaseBombPower();
	}
	if (item_center == SPEED_UP)
	{
		increasePlayerSpeed();
	}

	if (item_center != BLANK_ITEM)
	{
		Mix_PlayChannel(-1, mix_item, 0);
		item_map_.tile_map[y_center][x_center] = BLANK_ITEM;
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
				(real_y_pos > bomb_y_pos + CELL_SIZE) ||
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

				if (life > 0) { Mix_PlayChannel(-1, mix_damage, 0); }
				else { Mix_PlayChannel(-1, mix_die, 0); }

				SDL_Delay(150);

				limit_coll = true;
			}
		}
		else
		{
			limit_coll = false;
		}
	}

}

void Player::showLife(SDL_Renderer* des)
{
	for (int i = 1; i <= life; i++)
	{
		setRect(i * CELL_SIZE, 0.2 * CELL_SIZE);
		loadImg("Player/life.png", des);
		Render(des);
	}
}
