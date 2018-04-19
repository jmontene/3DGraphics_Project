
//*******************************************************************************
// MJ-101085465-Assignment4.cpp by Jose Montenegro (C) 2018 All Rights Reserved.
// 
// Assignment 4 submission
//
// Description:
//     Click run to see the results
//*******************************************************************************

using namespace std;

#include "stdlib.h"
#include <iostream>
#include "time.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "SOIL\SOIL.h"

int divisions = 60;
float plane_size = 1.f;

float cameraSpeed = 0.1f;
float cameraX = 0.f;
float cameraY = 1.4f;
float cameraZ = 3.f;

GLuint plane_ibo;
GLuint plane_vbo;
GLuint plane_vao;
GLuint texture_vbo;

GLint model;
GLint view;
GLint projection;

GLint lightPos;
GLint lightColor;
GLint ambientStrength;
GLint camPos;

int width = 720;
int height = 720;

unsigned short* indices;
float* vertices;
float* colors;
float* textureIndices;
float* normals;

float yAngle = 0.0f;
float rotationSpeed = 20.0f;

float lightX = 0.f;
float lightY = 1.f;
float lightZ = 0.f;
float lightSpeed = 0.1f;

glm::vec3 LightColor;

void init(void)
{

	//Specifying the name of vertex and fragment shaders.
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "camera.vert" },
		{ GL_FRAGMENT_SHADER, "camera.frag" },
		{ GL_NONE, NULL }
	};

	//Loading and compiling shaders
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up

	float division_size = plane_size / divisions;
	int num_sub_planes = divisions * divisions;

	//Vertices and Normals
	vertices = new float[12 * num_sub_planes];
	normals = new float[12 * num_sub_planes];
	for (int i = 0; i < divisions; ++i) {
		for (int j = 0; j < divisions; ++j) {
			vertices[i*divisions*12 + j * 12] = j*division_size + (-division_size / 2);
			vertices[i*divisions*12 + j * 12 + 1] = 0.f;
			vertices[i*divisions*12 + j * 12 + 2] = -i*division_size + (division_size / 2);

			vertices[i*divisions*12 + j * 12 + 3] = j*division_size + (division_size / 2);
			vertices[i*divisions*12 + j * 12 + 4] = 0.f;
			vertices[i*divisions*12 + j * 12 + 5] = -i*division_size + (division_size / 2);

			vertices[i*divisions*12 + j * 12 + 6] = j*division_size + (-division_size / 2);
			vertices[i*divisions*12 + j * 12 + 7] = 0.f;
			vertices[i*divisions*12 + j * 12 + 8] = -i*division_size + (-division_size / 2);

			vertices[i*divisions*12 + j * 12 + 9] = j*division_size + (division_size / 2);
			vertices[i*divisions*12 + j * 12 + 10] = 0.f;
			vertices[i*divisions*12 + j * 12 + 11] = -i*division_size + (-division_size / 2);
		}
	}
	
	//Indices
	indices = new unsigned short[6 * num_sub_planes];
	for (int i = 0; i < divisions; ++i) {
		for (int j = 0; j < divisions; ++j) {
			indices[i*divisions*6 + j * 6] = divisions * 4 * i + 4 * j;
			indices[i*divisions*6 + j * 6 + 1] = divisions * 4 * i + 4 * j + 1;
			indices[i*divisions*6 + j * 6 + 2] = divisions * 4 * i + 4 * j + 3;
			indices[i*divisions*6 + j * 6 + 3] = divisions * 4 * i + 4 * j;
			indices[i*divisions*6 + j * 6 + 4] = divisions * 4 * i + 4 * j + 3;
			indices[i*divisions*6 + j * 6 + 5] = divisions * 4 * i + 4 * j + 2;
		}
		cout << endl;
	}

	//UV's
	float end = 1.0f / divisions;
	textureIndices = new float[8 * num_sub_planes];
	for (int i = 0; i < divisions; ++i) {
		for (int j = 0; j < divisions; ++j) {
			textureIndices[i*divisions*8 + j * 8] = j*end;
			textureIndices[i*divisions*8 + j * 8 + 1] = 1.0f - i*end;

			textureIndices[i*divisions*8 + j * 8 + 2] = j*end + end;
			textureIndices[i*divisions*8 + j * 8 + 3] = 1.0f - i*end;

			textureIndices[i*divisions*8 + j * 8 + 4] = j*end;
			textureIndices[i*divisions*8 + j * 8 + 5] = 1.0f - i*end - end;

			textureIndices[i*divisions*8 + j * 8 + 6] = j*end + end;
			textureIndices[i*divisions*8 + j * 8 + 7] = 1.0f - i*end - end;
		}
	}

	//vbos, ibos
	glGenBuffers(1, &plane_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * num_sub_planes * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &plane_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * num_sub_planes * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &texture_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * num_sub_planes * sizeof(float), textureIndices, GL_STATIC_DRAW);

	//vao
	glGenVertexArrays(1, &plane_vao);
	glBindVertexArray(plane_vao);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane_ibo);

	//Uniforms
	model = glGetUniformLocation(program, "Model");
	view = glGetUniformLocation(program, "View");
	projection = glGetUniformLocation(program, "Projection");
	lightPos = glGetUniformLocation(program, "LightPosition");
	lightColor = glGetUniformLocation(program, "LightColor");
	ambientStrength = glGetUniformLocation(program, "Ambient");
	camPos = glGetUniformLocation(program, "ViewPos");

	//Textures
	GLint width, height;
	unsigned char* image = SOIL_load_image("rubiksTexture.png", &width, &height, 0, SOIL_LOAD_RGB);

	GLuint cube_tex = 0;
	glGenTextures(1, &cube_tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);


	//Lighting
	LightColor = glm::vec3(0.8f, 0.8f, 0.8f);
	glUniform3fv(lightColor, 1, glm::value_ptr(LightColor));
	glUniform1f(ambientStrength, 0.1f);
}

void drawPlane(glm::vec3 translation, float angle, glm::vec3 scale) {
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::scale(Model, scale);
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Model));

	glm::mat4 View;
	View = glm::lookAt(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
	glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(View));

	glm::mat4 Projection;
	Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.01f, 1000.f);
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(Projection));

	glDrawElements(GL_TRIANGLES, 6 * divisions * divisions, GL_UNSIGNED_SHORT, 0);
}


//---------------------------------------------------------------------
//
// display
//

void
display(void){
	glBindVertexArray(plane_vao);

	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform3fv(lightPos, 1, glm::value_ptr(glm::vec3(lightX, lightY, lightZ)));
	glUniform3fv(camPos, 1, glm::value_ptr(glm::vec3(cameraZ, cameraY, cameraZ)));
	drawPlane(glm::vec3(0.f), 0.f, glm::vec3(1.f));
	
	glutSwapBuffers();
}

void timer(int id) {
	glutPostRedisplay();
	glutTimerFunc(33, timer, 0);
}

void keyDown(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			cameraZ -= cameraSpeed;
			break;
		case 's':
			cameraZ += cameraSpeed;
			break;
		case 'a':
			cameraX -= cameraSpeed;
			break;
		case 'd':
			cameraX += cameraSpeed;
			break;
		case 'r':
			cameraY += cameraSpeed;
			break;
		case 'f':
			cameraY -= cameraSpeed;
			break;
		case 'j':
			lightX -= lightSpeed;
			break;
		case 'l':
			lightX += lightSpeed;
			break;
		case 'i':
			lightY += lightSpeed;
			break;
		case 'k':
			lightY -= lightSpeed;
			break;
	}
}

void idle(){
}

//---------------------------------------------------------------------
//
// main
//

int
main(int argc, char** argv){
	srand(time(NULL));

	//Ask for input
	cout << "Please enter the number of divisions: ";
	cin >> divisions;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 720);
	glutCreateWindow("Montenegro, Jose, 101085465");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//Lighting Configuration
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glewInit();	//Initializes the glew and prepares the drawing pipeline.

	init();

	glutDisplayFunc(display);

	glutIdleFunc(idle);
	glutKeyboardFunc(keyDown);
	glutTimerFunc(33, timer, 0);

	glutMainLoop();

}
