#pragma once
#include <vector>
#include "..\..\Render Engine\toolbox\maths\vec3.h"
#include "..\..\Render Engine\toolbox\color\Color.h"
#include "..\..\Render Engine\buffers\vertexarray.h"
#include "..\..\Render Engine\buffers\indexbuffer.h"

using namespace std;

//地形 一个CHUNK大小
class Terrain {
public:
	static const int GRID_COUNT;
	static const int VERTEX_COUNT;
	static const int SIZE;
	static const int GRID_SQUARE_SIZE;

	VertexArray *vao;
	IndexBuffer *ibo;
	vector<vec3u> indices;

	vector<vec3> positions;
	vector<vec3> normals;
	vector<vec3> colors;

public:
	Terrain();
	Terrain(int gridX, int gridZ, const vector<vector<float>> &_heights, const vector<vector<vec3>> &_normals, const vector<vector<Color>> &_colors);
	vector<vec3> generatePositionsVector(int gridX, int gridZ, const vector<vector<float>> &_heights);
	vector<vec3> generateNormalsVector(int gridX, int gridZ, const vector<vector<vec3>> &_normals);
	vector<vec3> generateColorsVector(int gridX, int gridZ, const vector<vector<Color>> &_colors);

	VertexArray* getVAO();
	IndexBuffer* getIBO();

	void bindVAO();
	void unbindVAO();
};