#include <catch2/catch.hpp>

#include <UWUEngine/Helper.h>

#include <UWUTest/Helper/TestFloat.hpp>

#include <glm/gtc/constants.hpp>

using namespace UWUTest;

TEST_CASE("Vector derived from angle", "[Angle θ :=> <x, y>]")
{
  SECTION("Angle θ = π/2")
	{
		uwu_const t_float theta = glm::pi<float>() / 2.f;
		glm::vec4 v = VectorFromAngle((float)theta);

		REQUIRE(t_float(0.f).almost_equal(v.x));
		REQUIRE(t_float(1.f).almost_equal(v.y));

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = -π/3")
	{
		uwu_const t_float theta = -glm::pi<float>() / 3.f;
		glm::vec4 v = VectorFromAngle((float)theta);

		REQUIRE(t_float(1.f / 2).almost_equal(v.x));
		REQUIRE(t_float(-std::sqrtf(3.f) / 2).almost_equal(v.y));

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = 0")
	{
		uwu_const t_float theta = 0;
		glm::vec4 v = VectorFromAngle((float)theta);

		REQUIRE(v.x == 1);
		REQUIRE(v.y == 0);

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}

	SECTION("Angle θ = 5π/4")
	{
		uwu_const t_float theta = 5.f * glm::pi<float>() / 4.f;
		glm::vec4 v = VectorFromAngle((float)theta);

		REQUIRE(t_float(-std::sqrtf(2.f) / 2).almost_equal(v.x));
		REQUIRE(t_float(-std::sqrtf(2.f) / 2).almost_equal(v.y));

		REQUIRE(v.z == 0);
		REQUIRE(v.w == 0);
	}
}
