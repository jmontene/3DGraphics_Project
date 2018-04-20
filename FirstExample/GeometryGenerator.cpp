#include "GeometryGenerator.h"
#include <math.h>
#include <iostream>
#define PI 3.141592

ModelData GeometryGenerator::cone(float radius, float height){
	ModelData res;
	float delta = 0.01f;
	int bottomVertices = ((2 * PI) / delta) + 2;

	res.vertices = new float[(bottomVertices + 2) * 3];
	res.vertices[0] = 0.f;
	res.vertices[1] = height;
	res.vertices[2] = 0.f;

	res.vertices[3] = 0.f;
	res.vertices[4] = 0.f;
	res.vertices[5] = 0.f;

	res.verticesSize = (bottomVertices + 2) * 3;

	res.indices = new unsigned short[2 * bottomVertices * 3];
	res.indicesSize = 2 * bottomVertices * 3;

	float t = 0.f;
	int count = 6;
	int indexCount = 0;
	for (int i = 2; i < bottomVertices+2; ++i) {
		res.vertices[count] = radius * cos(t);
		res.vertices[count + 1] = 0.f;
		res.vertices[count + 2] = (radius * sin(t));

		res.indices[indexCount] = 0;
		res.indices[indexCount + 1] = (i == bottomVertices+1 ? 1 : i + 1);
		res.indices[indexCount + 2] = i;

		res.indices[bottomVertices * 3 + indexCount] = 1;
		res.indices[bottomVertices * 3 + indexCount + 1] = i;
		res.indices[bottomVertices * 3 + indexCount + 2] = (i == bottomVertices + 1 ? 1 : i + 1);

		count += 3;
		indexCount += 3;
		t += delta;
	}

	return res;
}
