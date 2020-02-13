#include <catch2/catch.hpp>

#include <UWUEngine/Helper.h>

#include <UWUTest/Helper/TestFloat.hpp>

#include <glm/gtc/constants.hpp>
#include <iostream>

using namespace UWUTest;

TEST_CASE("Vector derived from angle", "[Angle θ :=> <x, y>]")
{
  SECTION("Angle θ = π/2")
	{
		constexpr t_float theta = glm::pi<float>() / 2.f;
		glm::vec4 v = VectorFromAngle(float(theta));

		std::cout << (0.f == t_float(v.x)) << std::endl;

		REQUIRE((0.f == t_float(v.x)));
		REQUIRE((1.f == t_float(v.y)));

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = -π/3")
	{
		constexpr t_float theta = -glm::pi<float>() / 3.f;
		glm::vec4 v = VectorFromAngle(float(theta));

		std::cout << (t_float(v.x) == 1.f / 2) << std::endl;

		REQUIRE((t_float(v.x) == 1.f / 2));
		REQUIRE((t_float(v.y) == -std::sqrtf(3.f) / 2));

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = 0")
	{
		constexpr t_float theta = 0;
		glm::vec4 v = VectorFromAngle(float(theta));

		REQUIRE(v.x == 1);
		REQUIRE(v.y == 0);

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = 5π/4")
	{
		constexpr t_float theta = 5.f * glm::pi<float>() / 4.f;
		glm::vec4 v = VectorFromAngle(float(theta));

		REQUIRE((-std::sqrtf(2.f) / 2 == t_float(v.x)));
		REQUIRE((-std::sqrtf(2.f) / 2 == t_float(v.y)));

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}
}
