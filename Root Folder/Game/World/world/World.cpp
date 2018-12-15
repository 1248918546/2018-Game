#include "World.h"
#include "..\generator\NormalsGenerator.h"
#include "..\generator\ColorGenerator.h"
#include "..\generator\PerlinNoiseGenerator.h"

const Color World::BACK_COLOR = Color(111.0f, 80.0f, 45.0f, true);

World::World(const WorldConfigs &_configs) {
	configs = _configs;
	PerlinNoiseGenerator noise(configs.getSeed(), configs.getSmoothness(), configs.getVertexCount() - 1.0f, configs.getWaterHeight() + WorldConfigs::EDGE_ABOVE_WATER);

	//heights
	vector<vector<float>> heights(configs.getVertexCount(), vector<float>(configs.getVertexCount()));
	float maxHeight = generateHeights(heights, noise);
	configs.setMaxHeight(maxHeight);

	//normals
	vector<vector<vec3>> normals;
	NormalsGenerator::generateNormals(heights, normals);

	//terrains
	terrains.resize(CHUNK_COUNT, vector<Terrain>(CHUNK_COUNT));
	generateTerrains(heights, normals);
}

float World::generateHeights(vector<vector<float>>& heights, PerlinNoiseGenerator noise) {
	float maxHeight = 0.0f;
	for (int z = 0; z < heights.size(); z++) {
		for (int x = 0; x < heights.size(); x++) {
			heights[z][x] = noise.getPerlinNoise(x, z);
			maxHeight = fmaxf(maxHeight, heights[z][x]);
		}
	}
	return maxHeight;
}

void World::generateTerrains(const vector<vector<float>> &heights, const vector<vector<vec3>> &normals) {
	int chunkLength = (heights.size() - 1) / terrains.size() + 1;
	for (int i = 0; i < terrains.size(); i++) {
		for (int j = 0; j < terrains.size(); j++) {
			generateTerrain(i, j, chunkLength, heights, normals);
		}
	}
}

void World::generateTerrain(int gridX, int gridZ, int chunkLength, const vector<vector<float>> &heights, const vector<vector<vec3>> &normals) {
	vector<vector<float>> childHeights(chunkLength, vector<float>(chunkLength));
	vector<vector<vec3>> childNormals(chunkLength, vector<vec3>(chunkLength));
	vector<vector<Color>> childColors(chunkLength, vector<Color>(chunkLength));

	ColorGenerator colorGenerator;

	int startX = gridZ * (chunkLength - 1);
	int startZ = gridX * (chunkLength - 1);

	for (int z = 0; z < chunkLength; z++) {
		for (int x = 0; x < chunkLength; x++) {
			childHeights[z][x] = heights[startZ + z][startX + x];
			childNormals[z][x] = normals[startZ + z][startX + x];
			childColors[z][x] = colorGenerator.getColor(childHeights[z][x], configs);
		}
	}

	terrains[gridX][gridZ] = Terrain(gridZ, gridX, childHeights, childNormals, childColors);
}

Terrain World::getTerrain(int gridX, int gridZ) {
	if (gridX < 0 || gridX >= terrains.size() || gridZ < 0 || gridZ >= terrains.size()) {
		return Terrain();
	}
	return terrains[gridZ][gridX];
}

vector<vector<Terrain>> World::getTerrains() {
	return terrains;
}

WorldConfigs World::getWorldConfigs() {
	return configs;
}
