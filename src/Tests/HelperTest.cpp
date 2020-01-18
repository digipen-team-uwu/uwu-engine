#include <catch2/catch.hpp>

#include <UWUEngine/Helper.h>

#include <glm/gtc/constants.hpp>

TEST_CASE("Vector derived from angle", "[Angle θ :=> <x, y>]")
{
  SECTION("Angle θ = π/2")
	{
		float theta = glm::pi<float>() / 2.f;
		glm::vec4 v = VectorFromAngle(theta);

		REQUIRE(v.x == 0);
		REQUIRE(v.y == 1);

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = -π/3")
	{
		float theta = -glm::pi<float>() / 3.f;
		glm::vec4 v = VectorFromAngle(theta);

		REQUIRE(v.x == std::sqrtf(3.f) / 2);
		REQUIRE(v.y == -1.f / 2);

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = 0")
	{
		float theta = 0;
		glm::vec4 v = VectorFromAngle(theta);

		REQUIRE(v.x == 1);
		REQUIRE(v.y == 0);

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = 5π/4")
	{
		float theta = 5.f * glm::pi<float>() / 4.f;
		glm::vec4 v = VectorFromAngle(theta);

		REQUIRE(v.x == -std::sqrtf(2.f) / 2);
		REQUIRE(v.y == -std::sqrtf(2.f) / 2);

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}
}
