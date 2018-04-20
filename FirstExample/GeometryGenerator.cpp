#include "GeometryGenerator.h"
#include <math.h>
#include <iostream>
#define PI 3.141592
#define PI_2 PI/2

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

	res.textureIndices = new float[(bottomVertices + 2) * 2];
	res.texturesSize = (bottomVertices + 2) * 2;
	res.textureIndices[0] = 0.5f;
	res.textureIndices[1] = 0.f;

	res.textureIndices[2] = 1.f;
	res.textureIndices[3] = 0.5f;

	float t = 0.f;
	int count = 6;
	int indexCount = 0;
	int textureCount = 4;
	for (int i = 2; i < bottomVertices+2; ++i) {
		res.vertices[count] = radius * cos(t);
		res.vertices[count + 1] = 0.f;
		res.vertices[count + 2] = radius * sin(t);

		res.indices[indexCount] = 0;
		res.indices[indexCount + 1] = (i == bottomVertices+1 ? 1 : i + 1);
		res.indices[indexCount + 2] = i;

		res.indices[bottomVertices * 3 + indexCount] = 1;
		res.indices[bottomVertices * 3 + indexCount + 1] = i;
		res.indices[bottomVertices * 3 + indexCount + 2] = (i == bottomVertices + 1 ? 1 : i + 1);

		res.textureIndices[textureCount] = (radius * cos(t) + radius) / (2*radius);
		res.textureIndices[textureCount + 1] = (radius * sin(t) + radius) / (2 * radius);

		count += 3;
		indexCount += 3;
		textureCount += 2;
		t += delta;
	}

	return res;
}

ModelData GeometryGenerator::sphere(float radius) {
	ModelData res;

	int rings = 10;
	int sectors = 10;

	float R = 1.0f / (rings - 1);
	float S = 1.0f / (sectors - 1);

	res.vertices = new float[rings * sectors * 3];
	res.verticesSize = rings * sectors * 3;
	res.normals = new float[rings * sectors * 3];
	res.normalsSize = rings * sectors * 3;
	res.textureIndices = new float[rings * sectors * 2];
	res.texturesSize = rings * sectors * 2;

	int count = 0;
	int textureCount = 0;

	for (int i = 0; i < rings; ++i) {
		for (int j = 0; j < sectors; ++j) {
			float x = cos(2 * PI*j*S) * sin(PI * i * R);
			float y = sin(-PI_2 + PI * i * R);
			float z = sin(2 * PI*j*S) * sin(PI * i * R);

			res.vertices[count] = x*radius;
			res.vertices[count + 1] = y*radius;
			res.vertices[count + 2] = z*radius;

			res.normals[count] = x;
			res.normals[count + 1] = y;
			res.normals[count + 2] = z;

			res.textureIndices[textureCount] = j*S;
			res.textureIndices[textureCount + 1] = i*R;

			count += 3;
			textureCount += 2;
		}
	}

	res.indices = new unsigned short[rings * sectors * 4];
	res.indicesSize = rings * sectors * 4;
	count = 0;
	for (int i = 0; i < rings; ++i) {
		for (int j = 0; j < sectors; ++j) {
			res.indices[count] = i * sectors + j;
			res.indices[count + 1] = i * sectors + (j + 1);
			res.indices[count + 2] = (i + 1) * sectors + (j + 1);
			res.indices[count + 3] = (i + 1) * sectors + j;
		}
	}
	return res;
}
