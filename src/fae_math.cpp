#include "fae_pch.hpp"
#include "fae_math.hpp"
#include <random>

namespace fae
{
	std::random_device random_device;
	std::mt19937 generator(random_device());

	float random_range(float min, float max)
	{
		std::uniform_real_distribution<> distribution(static_cast<double>(min), static_cast<double>(max));
		return static_cast<float>(distribution(generator));
	}
}