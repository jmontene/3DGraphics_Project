#ifndef GEOMETRY_GENERATOR_H
#define GEOMETRY_GENERATOR_H
#define VERTEX_SIZE 3

class GeometryGenerator {
public:
	struct ModelData {
		float *vertices;
		unsigned short *indices;
		float *normals;
		float *textureIndices;
	};

	ModelData box(float width, float height, float depth);
	ModelData quad(float width, float depth);
	ModelData wedge(float width, float depth);
	ModelData pyramid(float side, float height);
	ModelData triangularPrism(float width, float length, float height);
	ModelData diamond(float side, float height);
	ModelData cylinder(float radius, float height);
	ModelData cone(float radius, float height);
	ModelData sphere(float radius);
};

#endif