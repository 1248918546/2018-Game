#include "terrain.h"
#include "..\world\world.h"
#include "..\..\Render Engine\buffers\buffer.h"
#include "..\generator\gridGenerator.h"

const int Terrain::GRID_COUNT = (World::DESIRED_VERTEX_COUNT - 1) / World::CHUNK_COUNT;
const int Terrain::VERTEX_COUNT = GRID_COUNT + 1;
const int Terrain::SIZE = World::SIZE / World::CHUNK_COUNT;
const int Terrain::GRID_SQUARE_SIZE = SIZE / (VERTEX_COUNT - 1);

Terrain::Terrain() {}

Terrain::Terrain(int gridX, int gridZ, const vector<vector<float>> &_heights, const vector<vector<vec3>> &_normals, const vector<vector<Color>> &_colors) {
	positions = generatePositionsVector(gridX, gridZ, _heights);
	normals = generateNormalsVector(gridX, gridZ, _normals);
	colors = generateColorsVector(gridX, gridZ, _colors);
	indices = GridGenerator::generateGridIndexBuffer(VERTEX_COUNT, (gridX + gridZ) % 2 == 0);

	vao = new VertexArray();
	ibo = new IndexBuffer(&indices[0].x, indices.size() * 3);
	vao->addBuffer(new Buffer(&positions[0].x, positions.size() * 3, 3), 0);  //position
	vao->addBuffer(new Buffer(&normals[0].x, normals.size() * 3, 3), 1);      //normal
	vao->addBuffer(new Buffer(&colors[0].x, colors.size() * 3, 3), 2);        //color
}

vector<vec3> Terrain::generatePositionsVector(int gridX, int gridZ, const vector<vector<float>> &_heights) {
	vector<vec3> positions(_heights.size() * _heights.size());

	float squareSize = (float)SIZE / (float)(VERTEX_COUNT - 1);
	int startX = gridX * SIZE;
	int startZ = gridZ * SIZE;
	int pointer = 0;
	for (int z = 0; z < _heights.size(); z++) {
		for (int x = 0; x < _heights.size(); x++) {
			positions[pointer].x = startX + x * squareSize;
			positions[pointer].y = _heights[z][x];
			positions[pointer].z = startZ + z * squareSize;
			pointer++;
		}
	}

	return positions;
}

vector<vec3> Terrain::generateNormalsVector(int gridX, int gridZ, const vector<vector<vec3>> &_normals) {
	vector<vec3> normals(_normals.size() * _normals.size());
	int pointer = 0;
	for (int z = 0; z < _normals.size(); z++) {
		for (int x = 0; x < _normals.size(); x++) {
			vec3 normal = _normals[z][x];
			normals[pointer].x = normal.x;
			normals[pointer].y = normal.y;
			normals[pointer].z = normal.z;
			pointer++;
		}
	}
	return normals;
}

vector<vec3> Terrain::generateColorsVector(int gridX, int gridZ, const vector<vector<Color>> &_colors) {
	vector<vec3> colors(_colors.size() * _colors.size());
	int pointer = 0;
	for (int z = 0; z < _colors.size(); z++) {
		for (int x = 0; x < _colors.size(); x++) {
			Color color = _colors[z][x];
			colors[pointer].x = color.getR();
			colors[pointer].y = color.getG();
			colors[pointer].z = color.getB();
			pointer++;
		}
	}
	return colors;
}

VertexArray* Terrain::getVAO() {
	return vao;
}

IndexBuffer* Terrain::getIBO() {
	return ibo;
}


void Terrain::bindVAO() {
	vao->bind();
	ibo->bind();
}

void Terrain::unbindVAO() {
	ibo->unbind();
	vao->unbind();
}
