#pragma once
#include "terrainShader.h"
#include "..\..\World\terrain\terrain.h"

class TerrainRenderer {
public:
	TerrainShader *shader;

public:
	
	TerrainRenderer(const char *vertexGlsl, const char *fragmentGlsl);
	void render(Terrain terrain);
};