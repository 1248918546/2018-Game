#include <iostream>

#include "Render Engine/basics/window.h"
#include "Render Engine/toolbox/maths/maths_func.h"
#include "Render Engine/shaders/dragonshader.h"
#include "Render Engine/buffers/buffer.h"
#include "Render Engine/buffers/indexbuffer.h"
#include "Render Engine/buffers/vertexarray.h"
#include "Source/entity/models.h"
#include "Source/main/camera.h"
#include "World/world/world.h"
#include "Render Engine/terrain renderer/terrainRenderer.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main() {
	Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	/**
	Model dragon("Resource/dragon.obj");
	
	DragonShader shader("source/shaders/dragon.vert", "source/shaders/dragon.frag");
	shader.enable();
	
	shader.projection_matrix->load(mat4::perspective(45, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 300));
	shader.light_position->load( vec3(0.0,10.0,5.0));
	
	**/

	World world = World(WorldConfigs());
	TerrainRenderer terrainRender("source/shaders/terrain.vert", "source/shaders/terrain.frag");
	terrainRender.shader->enable();

	terrainRender.shader->projectionMatrix->load(mat4::perspective(45, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 300));
	terrainRender.shader->lightDirection->load(vec3(0.0f, 10.0f, 5.0f));
	terrainRender.shader->lightColor->load(vec3(1.0f, 1.0f, 1.0f));


	Camera camera(&window);

	glEnable(GL_DEPTH_TEST);
	while (!window.closed()) {
		window.clear();

		/**
		dragon.render();

		camera.move();
		shader.view_matrix->load(camera.CreateViewMatrix());
		**/

		camera.move();
		terrainRender.shader->viewMatrix->load(camera.CreateViewMatrix());
		for (int z = 0; z < World::CHUNK_COUNT; z++) {
			for (int x = 0; x < World::CHUNK_COUNT; x++) {
				Terrain terrain = world.getTerrain(x, z);
				terrainRender.render(terrain);
			}
		}

		window.update();
	}

	return 0;
}