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

	WHEN("Game is initialized")
	{
		struct time_config config;
		game_init(&config);

		THEN("Game is not started")
		{
			REQUIRE(false == game_is_started());
		}
	}
}
