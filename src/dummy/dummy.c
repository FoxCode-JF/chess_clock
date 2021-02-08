#include "dummy.h"
#include "game_types.h"
#include "time_config.h"
#include <stdbool.h>

struct player {
	game_time_t time_left;
	moves_cnt_t moves_cnt;
};

enum game_state
{
	GAME_STATE_START,
	GAME_STATE_PLAYER1,
	GAME_STATE_PLAYER2,
	GAME_STATE_PAUSE,
	GAME_STATE_REFEREE_INTERVENTION,
	GAME_STATE_END
};

struct game
{
	struct player player1;
	// enum player_id current_player;
	// enum player_id first_player_timed_out;
	// enum game_state game;
};

static struct game game_state;

void game_init(struct time_config *time)
{
	game_state.player1.time_left = time->base_time;
}

void game_move_done(void)
{

}

void game_start(void)
{

}
void game_pause(void)
{

}

bool game_is_started(void) 
{
	return false;
}
void game_referee_intervention(game_time_t time_p1, moves_cnt_t moves_p1, game_time_t time_p2, moves_cnt_t moves_p2)
{

}

void player_second_elapsed(enum player_id player)
{

}
/*how to count seconds on hardware timers*/
/*how the interface will need info if the player made a move*/

game_time_t player_get_time_left(enum player_id player)
{
	return game_state.player1.time_left;	
}
