#include "util/Random.h"

#include <random>

namespace chroma
{
	Random::Random() {}

	int Random::GetInt(int minInclusive, int maxInclusive)
	{
		std::random_device _device;
		std::mt19937 rng(_device());
		std::uniform_int_distribution < std::mt19937::result_type> dist(minInclusive, maxInclusive);

		return dist(rng);
	}
}