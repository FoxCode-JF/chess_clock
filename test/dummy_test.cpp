#include "catch2/catch.hpp"

extern "C"
{
	#include "../src/dummy/dummy.h"
	#include "../src/dummy/time_config.h"

}

SCENARIO("Game initialization")
{
	GIVEN("Time configuration")
	{
		game_time_t p1_time_expected = 5 * 60;
		struct time_config config;
			
		WHEN("Game is initialized")
		{
			game_init(&config);

			THEN("Players time left configured")
			{
				game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);
				REQUIRE(p1_time_left == p1_time_expected);
			}
		}
	}
}
