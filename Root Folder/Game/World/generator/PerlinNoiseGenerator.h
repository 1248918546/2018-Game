#pragma once
#include "..\..\Render Engine\toolbox\maths\vec3.h"
#include "..\..\Render Engine\toolbox\maths\maths_func.h"

class PerlinNoiseGenerator {
private:
	const float ROUGHNESS = 0.43f;
	const float OCATAVES = 5;
	const float AMPLITUDE = 15;

	float m_smoothness;
	float m_maxSize;

	float m_edgeHeight = -1.0f;

	int m_seed;

private:
	float getNoise(int x, int y);
	float getSmoothNoise(int x, int y);
	float cosinInterpolate(float a, float b, float blend);
	float getInterpolateNoise(float x, float y);

	float getEdgeFactor(float x, float y);

public:
	PerlinNoiseGenerator(int seed, float smoothness, float size, float edgeHeight);
	PerlinNoiseGenerator(float smoothness, float size, float edgeHeight);
	float getPerlinNoise(float x, float y);

};