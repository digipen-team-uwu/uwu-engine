/******************************************************************************/
	/*!
	\par        Project Umbra
	\file       Random.cpp
	\author     Brayan Lopez
	\date       2019/09/06
	\brief      Random module implementation

	Copyright � 2019 DigiPen, All rights reserved.
	*/
	/******************************************************************************/
#include <UWUEngine/Random.h>


std::mt19937_64 Random::rng = std::mt19937_64(std::random_device{}());
static std::normal_distribution<float> normalF;  //Normal distribution RNG for floats
static std::normal_distribution<double> normalD; //Normal distribution RNG for doubles

//initialize Random module, with a given seed
Random::Random(unsigned long long int seed)
{
	if (seed)
		rng.seed(seed);
#ifdef NORMAL_IMPLEMENTED
	normalF(rng);
	normalD(rng);
#endif
}

//generates int between min and max INCLUSIVE
int Random::Range(int min, int max, RNG distro)
{
	if (min > max)
	{
		auto temp = max;
		max = min;
		min = temp;
	}

	switch (distro)
	{
		case Uniform:
			std::uniform_int_distribution dist(min, max);
			return dist(rng);

#ifdef NORMAL_IMPLEMENTED
		case Normal:

			normalF.param(normalF.min);
			normalF.max = max;
			normalF.mean = .5f * (max + min) ;
			normalF.stddev = max - normalF.mean;
			return int(normalF(rng));
#endif

	}
	return 0;
}

//generates float between min and max INCLUSIVE
float Random::Range(float min, float max, RNG distro)
{
	if (min > max)
	{
		auto temp = max;
		max = min;
		min = temp;
	}
	switch (distro)
	{
		case Uniform:
			std::uniform_real_distribution dist(min, std::nextafter(max, FLT_MAX));
			return dist(rng);

#ifdef NORMAL_IMPLEMENTED
		case Normal:

			normalF.min = min;
			normalF.max = max;
			normalF.mean = (max + min) * .5f;
			normalF.stddev = max - normalF.mean;
			return normalF(rng);
#endif
	}

}

//generates double between min and max INCLUSIVE.
double Random::Range(double min, double max, RNG distro)
{
	if (min > max)
	{
		auto temp = max;
		max = min;
		min = temp;
	}

	switch (distro)
	{
		case Uniform:
			std::uniform_real_distribution<double> dist(min, std::nextafter(max, DBL_MAX));
			return dist(rng);

#ifdef NORMAL_IMPLEMENTED
		case Normal:

			normalD.min = min;
			normalD.max = max;
			normalD.stddev = max - normalD.mean;
			normalD.mean = (max + min) * .5;
			return normalD(rng);
#endif
	}
}

glm::vec4 Random::Range(glm::vec4 min, glm::vec4 max, RNG distro)
{
	FixRange(min, max);
	switch (distro)
	{
		case Uniform:
		{
			std::uniform_real_distribution distx(min.x, std::nextafter(max.x, FLT_MAX));
			std::uniform_real_distribution disty(min.y, std::nextafter(max.y, FLT_MAX));
			std::uniform_real_distribution distz(min.z, std::nextafter(max.z, FLT_MAX));
			std::uniform_real_distribution distw(min.w, std::nextafter(max.w, FLT_MAX));
			return { distx(rng), disty(rng), distz(rng), distw(rng) };
		}

#ifdef NORMAL_IMPLEMENTED
		case Normal:
		{

			auto meanX = .5f * (min.x + max.x);
			auto meanY = .5f * (min.y + max.y);
			auto meanZ = .5f * (min.z + max.z);
			auto meanW = .5f * (min.w + max.w);

			std::normal_distribution distx(meanX, max.x - meanX);
			distx.min = min.x;
			distx.max = max.x;

			std::normal_distribution disty(meanY, max.y - meanY);
			disty.min = min.y;
			disty.max = max.y;

			std::normal_distribution distz(meanZ, max.z - meanZ);
			distz.min = min.z;
			distz.max = max.z;

			std::normal_distribution distw(meanW, max.w - meanW);
			distw.min = min.w;
			distw.max = max.w;

			return { distx(rng), disty(rng), distz(rng), distw(rng) };
		}
#endif
	}
	return { 0,0,0,0 };
}

glm::vec3 Random::Range(glm::vec3 min, glm::vec3 max, RNG distro)
{
	FixRange(min, max);
	switch (distro)
	{
		case Uniform:
		{
			std::uniform_real_distribution distx(min.x, std::nextafter(max.x, FLT_MAX));
			std::uniform_real_distribution disty(min.y, std::nextafter(max.y, FLT_MAX));
			std::uniform_real_distribution distz(min.z, std::nextafter(max.z, FLT_MAX));
			return { distx(rng), disty(rng), distz(rng) };
		}

#ifdef NORMAL_IMPLEMENTED
		case Normal:
		{

			auto meanX = .5f * (min.x + max.x);
			auto meanY = .5f * (min.y + max.y);
			auto meanZ = .5f * (min.z + max.z);

			std::normal_distribution distx(meanX, max.x - meanX);
			distx.min = min.x;
			distx.max = max.x;

			std::normal_distribution disty(meanY, max.y - meanY);
			disty.min = min.y;
			disty.max = max.y;

			std::normal_distribution distz(meanZ, max.z - meanZ);
			distz.min = min.z;
			distz.max = max.z;
			return { distx(rng), disty(rng), distz(rng) };
		}
#endif
	}
	return { 0,0,0 };
}

glm::vec2 Random::Range(glm::vec2 min, glm::vec2 max, RNG distro)
{
	FixRange(min, max);

	switch (distro)
	{
		case Uniform:
		{
			std::uniform_real_distribution distx(min.x, std::nextafter(max.x, FLT_MAX));
			std::uniform_real_distribution disty(min.y, std::nextafter(max.y, FLT_MAX));
			return { distx(rng), disty(rng) };
		}

#ifdef NORMAL_IMPLEMENTED
		case Normal:
		{

			auto meanX = .5f * (min.x + max.x);
			auto meanY = .5f * (min.y + max.y);

			std::normal_distribution distx(meanX, max.x - meanX);
			distx.min = min.x;
			distx.max = max.x;

			std::normal_distribution disty(meanY, max.y - meanY);
			disty.min = min.y;
			disty.max = max.y;

			return { distx(rng), disty(rng) };
		}
#endif
	}
	return { 0,0 };
}