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
	GAME_STATE_PAUSED,
	GAME_STATE_STARTED

	// GAME_STATE_START,
	// GAME_STATE_PLAYER1,
	// GAME_STATE_PLAYER2,
	// GAME_STATE_PAUSE,
	// GAME_STATE_REFEREE_INTERVENTION,
	// GAME_STATE_END
};

struct game
{
	struct player player_one;
	struct player player_two;

	enum game_state state;
	enum player_id  current_player;
	// enum player_id current_player;
	// enum player_id first_player_timed_out;
	// enum game_state game;
};

static struct game game_state;

void game_init(struct time_config *time)
{
	game_state.state = GAME_STATE_PAUSED;
	game_state.player_one.time_left = time->base_time;
	game_state.player_two.time_left = time->base_time;
	game_state.current_player = PLAYER_NONE;
}

void game_current_player_moved(void)
{
	switch (game_state.current_player) 
	{
		case PLAYER_NONE:
			// game_state.current_player = PLAYER_ONE;
			break;
		case PLAYER_ONE:
			game_state.current_player = PLAYER_TWO;
			break;
		case PLAYER_TWO:
			game_state.current_player = PLAYER_ONE;
			break;
		default:
			break;
	}
}

void game_start(void)
{
	game_state.state = GAME_STATE_STARTED;

	if (PLAYER_NONE == game_state.current_player)
	{
		game_state.current_player = PLAYER_ONE;	
	}
}

void game_pause(void)
{
	game_state.state = GAME_STATE_PAUSED;
}

bool game_is_started(void) 
{
	return GAME_STATE_STARTED == game_state.state;
}

void game_referee_intervention(game_time_t time_p1, moves_cnt_t moves_p1, game_time_t time_p2, moves_cnt_t moves_p2)
{

}

void current_player_second_elapsed(void)
{
	if (true == game_is_started())
	{
		switch (game_state.current_player) 
		{
			case PLAYER_NONE:
				// game_state.current_player = PLAYER_ONE;
				break;
			case PLAYER_ONE:
				game_state.player_one.time_left--;
				break;
			case PLAYER_TWO:
				game_state.player_two.time_left--;
				break;
			default:
				break;
		}
	}
}
/*how to count seconds on hardware timers*/
/*how the interface will need info if the player made a move*/

game_time_t player_get_time_left(enum player_id player)
{
	switch (player) 
	{
		case PLAYER_NONE:
			// illegal case
			break;
		case PLAYER_ONE:
			return game_state.player_one.time_left;
		case PLAYER_TWO:
			return game_state.player_two.time_left;	
		default:
			// illegal case
			return -1;
	}
}

enum player_id get_current_player(void)
{
	return game_state.current_player;
}