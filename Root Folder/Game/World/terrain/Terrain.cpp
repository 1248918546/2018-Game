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
	m_positions = generatePositionsVector(gridX, gridZ, _heights);
	m_normals = generateNormalsVector(gridX, gridZ, _normals);
	m_colors = generateColorsVector(gridX, gridZ, _colors);
	m_indices = GridGenerator::generateGridIndexBuffer(VERTEX_COUNT, (gridX + gridZ) % 2 == 0);

	m_vao = new VertexArray();
	m_ibo = new IndexBuffer(&m_indices[0].x, m_indices.size() * 3);
	m_vao->addBuffer(new Buffer(&m_positions[0].x, m_positions.size() * 3, 3), 0);  //position
	m_vao->addBuffer(new Buffer(&m_normals[0].x, m_normals.size() * 3, 3), 1);      //normal
	m_vao->addBuffer(new Buffer(&m_colors[0].x, m_colors.size() * 3, 3), 2);        //color
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
	return m_vao;
}

IndexBuffer* Terrain::getIBO() {
	return m_ibo;
}


void Terrain::bindVAO() {
	m_vao->bind();
	m_ibo->bind();
}

void Terrain::unbindVAO() {
	m_ibo->unbind();
	m_vao->unbind();
}
