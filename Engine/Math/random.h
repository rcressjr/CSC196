#pragma once
#include <stdlib.h>

namespace rj {
	void SeedRandom(unsigned int seed);

	float Random();
	float RandomRange(float min, float max);
	float RandomEnemy(float min, float max);

	int RandomInt();
	int RandomRangeInt(int min, int max);
}