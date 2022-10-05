#pragma once

#include <random>

namespace neu {

	inline void seedRandom(int seed) { srand(seed); }

	inline int random() { return rand(); };

	inline int random(int max) { return random() % max; } // , exclussive (0 - 9 if max = 10)

	inline int random(int min, int max) { return min + random() % ((max - min) + 1); } // inclusive

	inline float randomf() { return rand() / (float)RAND_MAX; } // 0.0 - 1

	inline float randomf(float max) { return randomf() * max; } // 0.0 - max

	inline float randomf(float min, float max) { return min + randomf(max - min); }

}
