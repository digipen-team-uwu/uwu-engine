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
#include <UWUEngine/Helper.h>
#define NORMAL_IMPLEMENTED
template<>
int RegisterSystemHelper<Random>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Random>(SystemInitOrder::FIRST, SystemUpdateOrder::FIRST);

std::mt19937_64 Random::rng = std::mt19937_64(std::random_device{}());

//initialize Random module, with a given seed
Random::Random(unsigned long long int seed)
{
	if (seed)
		rng.seed(seed);
}

//generates int between min and max INCLUSIVE
int Random::Range(int min, int max, RNG distro)
{
	if (min > max)
	{
		int temp = max;
		max = min;
		min = temp;
	}

	switch (distro)
	{
		case Uniform:
		{
			std::uniform_int_distribution dist(min, max);
			return dist(rng);
		}

#ifdef NORMAL_IMPLEMENTED
		case Normal:
		{
			float mean = .5f * (max + min);
			std::normal_distribution<float>normal(mean, max - mean);
			return SCAST(normal(rng),int);
		}
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
		{
			std::uniform_real_distribution dist(min, std::nextafter(max, FLT_MAX));
			return dist(rng);
		}

#ifdef NORMAL_IMPLEMENTED
		case Normal:
		{
			float mean = .5f * (max + min);
			std::normal_distribution<float>normal(mean, max - mean);
			return normal(rng);
		}
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
		{
			std::uniform_real_distribution<double> dist(min, std::nextafter(max, DBL_MAX));
			return dist(rng);
		}

#ifdef NORMAL_IMPLEMENTED
		case Normal:
		{
			double mean = .5 * (max + min);
			std::normal_distribution<double>normal(mean, max - mean);
			return normal(rng);
		}

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
			std::normal_distribution disty(meanY, max.y - meanY);
			std::normal_distribution distz(meanZ, max.z - meanZ);
			std::normal_distribution distw(meanW, max.w - meanW);
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
			std::normal_distribution disty(meanY, max.y - meanY);
			std::normal_distribution distz(meanZ, max.z - meanZ);
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
			std::normal_distribution disty(meanY, max.y - meanY);
			return { distx(rng), disty(rng) };
		}
#endif
	}
	return { 0,0 };
}