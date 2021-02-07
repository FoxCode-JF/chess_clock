#include "catch2/catch.hpp"

extern "C"
{
	#include "../src/dummy/dummy.h"
}

SCENARIO("dummy")
{

	REQUIRE_FALSE(false);
}
