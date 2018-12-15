#pragma once

class WorldConfigs {
private:
	int seed;
	int vertexCount;
	float smoothness;
	float waterHeight;
	float maxHeight;

public:
	static float EDGE_ABOVE_WATER;

	WorldConfigs();
	WorldConfigs(int seed, float smoothness, int vertexCount, float waterHeight);

	int getSeed();
	int getVertexCount();
	float getSmoothness();
	float getWaterHeight();
	float getMaxHeight();

	void setMaxHeight(float height);
};