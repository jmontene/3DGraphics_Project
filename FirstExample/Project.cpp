
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
#include "GeometryGenerator.h"

float cameraSpeed = 0.1f;
float cameraX = 0.f;
float cameraY = 1.4f;
float cameraZ = 3.f;

ModelData coneData;
GLuint cone_vbo;
GLuint cone_ibo;
GLuint coneTexture_vbo;
GLuint cone_vao;

ModelData sphereData;
GLuint sphere_vbo;
GLuint sphere_ibo;
GLuint sphereTexture_vbo;
GLuint sphere_vao;

GLint model;
GLint view;
GLint projection;

GLint lightPos;
GLint lightColor;
GLint ambientStrength;
GLint camPos;

int width = 720;
int height = 720;

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

	//Geometries
	coneData = GeometryGenerator::cone(0.5f, 1.f);
	sphereData = GeometryGenerator::sphere(1.0f);

	//vbos, ibos

	//Cone
	glGenBuffers(1, &cone_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cone_vbo);
	glBufferData(GL_ARRAY_BUFFER, coneData.verticesSize * sizeof(float), coneData.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &cone_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, coneData.indicesSize * sizeof(unsigned short), coneData.indices, GL_STATIC_DRAW);

	glGenBuffers(1, &coneTexture_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coneTexture_vbo);
	glBufferData(GL_ARRAY_BUFFER, coneData.texturesSize * sizeof(float), coneData.textureIndices, GL_STATIC_DRAW);

	//

	//vao
	glGenVertexArrays(1, &cone_vao);
	glBindVertexArray(cone_vao);
	glBindBuffer(GL_ARRAY_BUFFER, cone_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, coneTexture_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_ibo);

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
	unsigned char* image = SOIL_load_image("castle_red.png", &width, &height, 0, SOIL_LOAD_RGB);

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

void drawModel(ModelData &data, glm::vec3 translation, float angle, glm::vec3 scale) {
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

	glDrawElements(GL_TRIANGLES, data.indicesSize, GL_UNSIGNED_SHORT, 0);
}


//---------------------------------------------------------------------
//
// display
//

void
display(void){
	glBindVertexArray(cone_vao);

	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform3fv(lightPos, 1, glm::value_ptr(glm::vec3(lightX, lightY, lightZ)));
	glUniform3fv(camPos, 1, glm::value_ptr(glm::vec3(cameraZ, cameraY, cameraZ)));
	drawModel(coneData, glm::vec3(0.f), 0.f, glm::vec3(1.f));
	
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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 720);
	glutCreateWindow("Final Project");

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
