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

void game_current_player_moved(void);

void game_start(void);
void game_pause(void);
bool game_is_started();

void game_referee_intervention(game_time_t time_p1, moves_cnt_t moves_p1, game_time_t time_p2, moves_cnt_t moves_p2);

void current_player_second_elapsed(void);
/*how to count seconds on hardware timers*/
/*how the interface will need info if the player made a move*/

game_time_t player_get_time_left(enum player_id player);

enum player_id get_current_player(void);