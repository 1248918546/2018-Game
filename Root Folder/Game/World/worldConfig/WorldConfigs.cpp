#include "WorldConfigs.h"
#include "..\..\Render Engine\toolbox\maths\maths_func.h"

float WorldConfigs::EDGE_ABOVE_WATER = 0.5f;

WorldConfigs::WorldConfigs(int seed, float smoothness, int vertexCount, float waterHeight) {
	this->seed = seed;
	this->smoothness = smoothness;
	this->vertexCount = vertexCount;
	this->waterHeight = waterHeight;
}

WorldConfigs::WorldConfigs() {
	this->seed = Maths::randomInt(1000000);
	this->smoothness = 1.0f;
	this->vertexCount = 136;
	this->waterHeight = -2.0f;
}

int WorldConfigs::getSeed() {
	return seed;
}

int WorldConfigs::getVertexCount() {
	return vertexCount;
}

float WorldConfigs::getSmoothness() {
	return smoothness;
}

float WorldConfigs::getWaterHeight() {
	return waterHeight;
}

float WorldConfigs::getMaxHeight() {
	return maxHeight;
}

void WorldConfigs::setMaxHeight(float height) {
	maxHeight = height;
}
