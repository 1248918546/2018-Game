#pragma once
#define _USE_MATH_DEFINES

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include <math.h>
#include <time.h>

class Maths {
public:
	static float getDistanceBetweenPoints(float x1, float y1, float x2, float y2) {
		float dx = x2 - x1;
		float dy = y2 - y1;
		return sqrt(dx * dx + dy * dy);
	}

	static int randomInt(int nextInt) {
		srand((int)time(0));
		return rand() % nextInt;
	}

	static float randomFloat(int seed) {
		srand(seed);
		float m1 = (float)(rand() / float(RAND_MAX));
		return m1;
	}

	static float clamp(float x, float lower, float upper) {
		return fmaxf(lower, fminf(x, upper));
	}
};