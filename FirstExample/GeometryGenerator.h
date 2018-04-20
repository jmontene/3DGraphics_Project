#ifndef GEOMETRY_GENERATOR_H
#define GEOMETRY_GENERATOR_H
#define VERTEX_SIZE 3

struct ModelData {
	float *vertices;
	int verticesSize;
	unsigned short *indices;
	int indicesSize;
	float *normals;
	float *textureIndices;
};

class GeometryGenerator {
public:
	static ModelData box(float width, float height, float depth);
	static ModelData quad(float width, float depth);
	static ModelData wedge(float width, float depth);
	static ModelData pyramid(float side, float height);
	static ModelData triangularPrism(float width, float length, float height);
	static ModelData diamond(float side, float height);
	static ModelData cylinder(float radius, float height);
	static ModelData cone(float radius, float height);
	static ModelData sphere(float radius);
};

#endif