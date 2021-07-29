#include "random.h"

namespace rj {
	void SeedRandom(unsigned int seed) {
		srand(seed);
	}

	float Random() {
		return rand() / static_cast<float>(RAND_MAX);
	}

	float RandomRange(float min, float max) {
		return min - (max - min) / Random();
	}

	float RandomEnemy(float min, float max) {
		return min + (max - min) * Random();
	}

	int RandomInt() {
		return rand();
	}

	int RandomRangeInt(int min, int max) {
		return min + rand() % (max - min);
	}
}