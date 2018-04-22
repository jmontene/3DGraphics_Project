//***********************************************************************************************
// GeometryGenerator.cpp by Jamie Ching-chun Huang,101088322 (C) 2018 All Rights Reserved.
//
// Final Project.
//
// Description:
//
//
//***********************************************************************************************

#include <type_ptr.hpp>
#include "stdlib.h"
#include <iostream>
#include <glew.h>
#include "time.h"
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <GLUT/GLUT.h>
#include <LoadShaders.h>
#include <SOIL.h>
#include <stdio.h>
#include "GeometryGenerator.h"


float cameraSpeed = 0.1f;
float cameraX = 0.f;
float cameraY = 1.4f;
float cameraZ = 4.f;

ModelData coneData;
GLuint cone_vao;
GLuint cone_tex;

ModelData sphereData;
GLuint sphere_vao;
GLuint sphere_tex;

ModelData quadData;
GLuint quad_vao;
GLuint quad_tex;

ModelData boxData;
GLuint box_vao;
GLuint box_tex;

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

float lightX = 0.5f;
float lightY = 3.f;
float lightZ = 0.2f;
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
    glUseProgram(program);    //My Pipeline is set up
    
    //Geometries
    coneData = GeometryGenerator::cone(0.5f, 1.f);
    sphereData = GeometryGenerator::sphere(1.0f);
    quadData = GeometryGenerator::quad(1.0f, 5.0f);
    boxData = GeometryGenerator::box(1.0f, 1.0f, 1.0f);
    
    //vbos, ibos------------------------------------------
    
    //Cone
    GLuint cone_vbo = 0, cone_ibo = 0, coneTexture_vbo = 0 ;
    glGenBuffers(1, &cone_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cone_vbo);
    glBufferData(GL_ARRAY_BUFFER, coneData.verticesSize * sizeof(float), coneData.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &cone_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, coneData.indicesSize * sizeof(unsigned short), coneData.indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &coneTexture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, coneTexture_vbo);
    glBufferData(GL_ARRAY_BUFFER, coneData.texturesSize * sizeof(float), coneData.textureIndices, GL_STATIC_DRAW);
    
    
    //Quad
    GLuint quad_vbo = 0, quad_ibo = 0, quadTexture_vbo = 0 ;
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, quadData.verticesSize * sizeof(float), quadData.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &quad_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, quadData.indicesSize * sizeof(unsigned short), quadData.indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &quadTexture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadTexture_vbo);
    glBufferData(GL_ARRAY_BUFFER, quadData.texturesSize * sizeof(float), quadData.textureIndices, GL_STATIC_DRAW);
    
    //Box
    GLuint box_vbo = 0, box_ibo = 0, boxTexture_vbo = 0 ;
    glGenBuffers(1, &box_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, box_vbo);
    glBufferData(GL_ARRAY_BUFFER, boxData.verticesSize * sizeof(float), boxData.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &box_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxData.indicesSize * sizeof(unsigned short), boxData.indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &boxTexture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, boxTexture_vbo);
    glBufferData(GL_ARRAY_BUFFER, boxData.texturesSize * sizeof(float), boxData.textureIndices, GL_STATIC_DRAW);
    
    //vao--------------------------------------------------
    //Cone
    glGenVertexArrays(1, &cone_vao);
    glBindVertexArray(cone_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cone_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, coneTexture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_ibo);
    
    //Quad
    glGenVertexArrays(1, &quad_vao);
    glBindVertexArray(quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadTexture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);
    
    //Box
    glGenVertexArrays(1, &box_vao);
    glBindVertexArray(box_vao);
    glBindBuffer(GL_ARRAY_BUFFER, box_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, boxTexture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box_ibo);
    
    //Uniforms
    model = glGetUniformLocation(program, "Model");
    view = glGetUniformLocation(program, "View");
    projection = glGetUniformLocation(program, "Projection");
    lightPos = glGetUniformLocation(program, "LightPosition");
    lightColor = glGetUniformLocation(program, "LightColor");
    ambientStrength = glGetUniformLocation(program, "Ambient");
    camPos = glGetUniformLocation(program, "ViewPos");
    
    //Textures
    GLint Width, Height;
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/castle_red.png", &Width, &Height, 0, SOIL_LOAD_RGB);
    cone_tex = 0;
    glGenTextures(1, &cone_tex);
    glBindTexture(GL_TEXTURE_2D, cone_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_grass = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/grass_s.png",&Width, &Height, 0, SOIL_LOAD_RGB);
    quad_tex = 0;
    glGenTextures(1, &quad_tex);
    glBindTexture(GL_TEXTURE_2D, quad_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_grass);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_rock = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/rock.jpg",&Width, &Height, 0, SOIL_LOAD_RGB);
    box_tex = 0;
    glGenTextures(1, &box_tex);
    glBindTexture(GL_TEXTURE_2D, box_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_rock);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    //Lighting
    LightColor = glm::vec3(0.8f, 0.8f, 0.8f);
    glUniform3fv(lightColor, 1, glm::value_ptr(LightColor));
    glUniform1f(ambientStrength, 0.15f);
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
void display(void){
    
    glClearColor(0.349, 0.396, 0.466, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniform3fv(lightPos, 1, glm::value_ptr(glm::vec3(lightX, lightY, lightZ)));
    glUniform3fv(camPos, 1, glm::value_ptr(glm::vec3(cameraZ, cameraY, cameraZ)));
    
    glBindVertexArray(cone_vao);
    glBindTexture(GL_TEXTURE_2D, cone_tex);
    drawModel(coneData, glm::vec3(-0.6f,0.f,0.5f), 0.f, glm::vec3(0.3f,0.4f,0.3f));
    
    glBindVertexArray(quad_vao);
    glBindTexture(GL_TEXTURE_2D, quad_tex);
    drawModel(quadData, glm::vec3(0.f,-1.0f,0.f), 0.f, glm::vec3(2.0f,0.f,1.5f));
    
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, box_tex);
    drawModel(boxData, glm::vec3(0.f,-0.75f,0.f), 0.f, glm::vec3(1.5f,0.5f,1.0f));

    glutSwapBuffers();

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


void Timer(int id){
    glutPostRedisplay();
    glutTimerFunc(15, Timer, 0);
}

//---------------------------------------------------------------------
//
// main
//
int main(int argc, char** argv){
    
    srand(time(NULL));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_DEPTH);
    //I think the glutInitDisplayMode has something different with windows version
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Huang, Jamie Ching-chun, 101088322");
    
    glewExperimental = true;
    glewInit();    //Initializes the glew and prepares the drawing pipeline.
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
    
    init();
    
    glutTimerFunc(15, Timer, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    
    glutMainLoop();
}


