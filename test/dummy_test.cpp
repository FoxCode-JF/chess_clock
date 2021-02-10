#include "catch2/catch.hpp"

extern "C"
{
	#include "../src/dummy/dummy.h"
	#include "../src/dummy/time_config.h"

}

#define SEC_PER_MIN			60
#define MIN_TO_SEC(min)		((min) * SEC_PER_MIN)

SCENARIO("Game initialization")
{
	GIVEN("Time configured to 5 minutes")
	{
		game_time_t time_expected = MIN_TO_SEC(5);
		struct time_config config;

		config.base_time = time_expected;
			
		WHEN("Game is initialized")
		{
			game_init(&config);

			THEN("Player one with 5 minutes left")
			{
				game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);
				REQUIRE(p1_time_left == time_expected);
			}

			THEN("Player two with 5 minutes left")
			{
				game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);
				REQUIRE(p2_time_left == time_expected);
			}
		}
	}

	GIVEN("Time configured to 15 minutes")
	{
		game_time_t time_expected = MIN_TO_SEC(15);
		struct time_config config;

		config.base_time = time_expected;
			
		WHEN("Game is initialized")
		{
			game_init(&config);

			THEN("Player one with 15 minutes left")
			{
				game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);
				REQUIRE(p1_time_left == time_expected);
			}
			THEN("Player two with 15 minutes left")
			{
				game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);
				REQUIRE(p2_time_left == time_expected);
			}
		}
	}
}

SCENARIO("Game starting")
{
	WHEN("Game is initialized")
	{
		struct time_config config;
		game_init(&config);

		THEN("Game is not started")
		{
			REQUIRE(false == game_is_started());
		}

		WHEN("Game started")
		{
			game_start();

			THEN("Game is started")
			{
				REQUIRE(true == game_is_started());
			}

			WHEN("Game is paused")
			{
				game_pause();

				THEN("Game is not started")
				{
					REQUIRE(false == game_is_started());
				}
				WHEN("Game started again")
				{
					game_start();

					THEN("Game is started")
					{
						REQUIRE(true == game_is_started());
					}	
				}
			}
		}
	}
}

SCENARIO("Switching player turn")
{
	WHEN("Game is not started")
	{
		struct time_config config;

		game_init(&config);

		THEN("No player to move")
		{
			REQUIRE(PLAYER_NONE == get_current_player());
		}

		WHEN("Game started")
		{
			game_start();

			THEN("Player one turn")
			{
				REQUIRE(PLAYER_ONE == get_current_player());
			}

			WHEN("Player one moved")
			{
				game_current_player_moved();

				THEN("Player two turn")
				{
					REQUIRE(PLAYER_TWO == get_current_player());		
				}

				WHEN("Player two moved")
				{
					game_current_player_moved();
				
					THEN("Player one turn")
					{
						REQUIRE(PLAYER_ONE == get_current_player());		
					}
				}

				WHEN("Game paused")
				{
					game_pause();

					WHEN("Game is resumed")
					{
						game_start();

						THEN("Player two turn")
						{
							REQUIRE(PLAYER_TWO == get_current_player());
						}
					}
				}
			}
		}
	}
}


SCENARIO("Second elapsed")
{
	GIVEN("After init - game not started")
	{
		game_time_t time_expected = MIN_TO_SEC(5);
		struct time_config config;

		config.base_time = time_expected;
		game_init(&config);

		WHEN("Current player's second elapsed")
		{
			current_player_second_elapsed();

			THEN("Player one's time not decreased")
			{
				game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

				REQUIRE(time_expected == p1_time_left);
			}

			THEN("Player two's time not decreased")
			{
				game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);

				REQUIRE(time_expected == p2_time_left);		
			}
		}

		WHEN("Game started")
		{
			game_start();

			WHEN("Current player's second elapsed")
			{
				current_player_second_elapsed();

				THEN("Player one's time decreased")
				{
					game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

					REQUIRE(time_expected - 1 == p1_time_left);	
				}


				THEN("Player two's time not decreased")
				{
					game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);

					REQUIRE(time_expected == p2_time_left);		
				}
			}

			WHEN("Game paused")
			{
				game_pause();
				WHEN("Current player's second elapsed")
				{
					current_player_second_elapsed();
					
					THEN("Player one's time not decreased")
					{
						game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

						REQUIRE(time_expected == p1_time_left);
					}

					// THEN("Player two's time not decreased")
					// {
					// 	game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);

					// 	REQUIRE(time_expected == p2_time_left);		
					// }
				}
			}
			WHEN("Player moved")
			{
				game_current_player_moved();

				WHEN("Current player's second elapsed")
				{
					current_player_second_elapsed();

					THEN("Player one's time not decreased")
					{
						game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

						REQUIRE(time_expected == p1_time_left);	
					}


					THEN("Player two's time decreased")
					{
						game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);

						REQUIRE(time_expected - 1 == p2_time_left);		
					}
				}
			}
		}
	}
	// when game is not started then player time is not decreased
	// given game is started
		// when player one is currently moving:
			// then player one time is decreased
			//  then player two time is not decreased
	 	// when player two is currently moving:
			// then player one time is not decreased
			// then player two time is decreased
}