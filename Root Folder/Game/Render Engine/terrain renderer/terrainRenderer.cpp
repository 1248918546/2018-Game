#include "terrainRenderer.h"
#include "..\..\World\world\world.h"
#include "..\basics\window.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

TerrainRenderer::TerrainRenderer(const char *vertexGlsl, const char *fragmentGlsl) {
	shader = new TerrainShader(vertexGlsl, fragmentGlsl);
}

void TerrainRenderer::render(Terrain terrain) {
	terrain.bindVAO();
	glDrawElements(GL_TRIANGLES, terrain.getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);
	terrain.unbindVAO();
}
