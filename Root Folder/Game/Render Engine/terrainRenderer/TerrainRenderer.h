#pragma once
#include "TerrainShader.h"
#include "..\..\World\terrain\Terrain.h"

class TerrainRenderer {
public:
	TerrainShader *shader;

public:
	
	TerrainRenderer(const char *vertexGlsl, const char *fragmentGlsl);
	void render(Terrain terrain);
};