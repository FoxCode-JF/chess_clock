#pragma once

#include "game_types.h"

#include <stdint.h>
#include <stdbool.h>

enum player_id
{
	PLAYER_NONE,
	PLAYER_ONE,
	PLAYER_TWO
};

struct time_config;

void game_init(struct time_config *time);

void game_move_done(void);

void game_start(void);
void game_pause(void);

void game_referee_intervention(game_time_t time_p1, moves_cnt_t moves_p1, game_time_t time_p2, moves_cnt_t moves_p2);

void player_second_elapsed(enum player_id player);
/*how to count seconds on hardware timers*/
/*how the interface will need info if the player made a move*/