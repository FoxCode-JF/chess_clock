#pragma once

#include "game_types.h"

#include <stdint.h>
#include <stdbool.h>

struct extra_time_after_x_moves 
{
	game_time_t time_added;
	moves_cnt_t moves;
};

struct time_config
{
	game_time_t base_time;
	game_time_t bonus_per_move;

	struct extra_time_after_x_moves extra_time;
};