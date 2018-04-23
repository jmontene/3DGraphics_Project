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
float cameraY = 0.4f;
float cameraZ = 4.f;
float cameraTheta = 3.14f;
float cameraPhi = 0.f;
float mouseSpeed = 0.0005f;

glm::vec3 cameraPos(0.f,0.f, 3.f);
glm::vec3 cameraDirection(0.f,0.f,0.f);
glm::vec3 cameraUp(0.f,1.f,0.f);
glm::vec3 right(1.f, 0.f, 0.f);

ModelData coneData;
GLuint cone_vao;

ModelData sphereData;
GLuint sphere_vao;

ModelData quadData;
GLuint quad_vao;

ModelData boxData;
GLuint box_vao;

ModelData hexagonData;
GLuint hexagon_vao;

ModelData cylinderData;
GLuint cylinder_vao;

ModelData pyramidData;
GLuint pyramid_vao;


//Textures vao
GLuint redRock_tex;
GLuint grass_tex;
GLuint rock_tex;
GLuint brick_tex;
GLuint blueWall_tex;
GLuint colorWall_tex;
GLuint door_tex;
GLuint wood_tex;
GLuint waffle_tex;

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

float lightX = 2.0f;
float lightY = 5.f;
float lightZ = 1.0f;
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
    quadData = GeometryGenerator::quad(1.0f, 1.0f);
    boxData = GeometryGenerator::box(1.0f, 1.0f, 1.0f);
    hexagonData = GeometryGenerator::hexagon(1.f, 0.5f, 1.f);
    cylinderData = GeometryGenerator::cylinder(1.5f, 1.f);
    pyramidData = GeometryGenerator::pyramid(1.f, 1.f);
    
    //vbos, ibos------------------------------------------
    
    //Sphere
    GLuint sphere_vbo = 0, sphere_ibo = 0, sphereTexture_vbo = 0 ;
    glGenBuffers(1, &sphere_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
    glBufferData(GL_ARRAY_BUFFER, sphereData.verticesSize * sizeof(float), sphereData.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &sphere_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereData.indicesSize * sizeof(unsigned short), sphereData.indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &sphereTexture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, sphereTexture_vbo);
    glBufferData(GL_ARRAY_BUFFER, sphereData.texturesSize * sizeof(float), sphereData.textureIndices, GL_STATIC_DRAW);
    
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
    
    //Hexagon
    GLuint hexagon_vbo = 0, hexagon_ibo = 0, hexagonTexture_vbo = 0 ;
    glGenBuffers(1, &hexagon_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, hexagon_vbo);
    glBufferData(GL_ARRAY_BUFFER, hexagonData.verticesSize * sizeof(float), hexagonData.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &hexagon_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexagon_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, hexagonData.indicesSize * sizeof(unsigned short), hexagonData.indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &hexagonTexture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, hexagonTexture_vbo);
    glBufferData(GL_ARRAY_BUFFER, hexagonData.texturesSize * sizeof(float), hexagonData.textureIndices, GL_STATIC_DRAW);
    
    //Cylinder
    GLuint cylinder_vbo = 0, cylinder_ibo = 0, cylinderTexture_vbo = 0 ;
    glGenBuffers(1, &cylinder_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo);
    glBufferData(GL_ARRAY_BUFFER, cylinderData.verticesSize * sizeof(float), cylinderData.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &cylinder_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinderData.indicesSize * sizeof(unsigned short), cylinderData.indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &cylinderTexture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cylinderTexture_vbo);
    glBufferData(GL_ARRAY_BUFFER, cylinderData.texturesSize * sizeof(float), cylinderData.textureIndices, GL_STATIC_DRAW);
    
    //Pyramid
    GLuint pyramid_vbo = 0, pyramid_ibo = 0, pyramidTexture_vbo = 0 ;
    glGenBuffers(1, &pyramid_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, pyramid_vbo);
    glBufferData(GL_ARRAY_BUFFER, pyramidData.verticesSize * sizeof(float), pyramidData.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &pyramid_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramid_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pyramidData.indicesSize * sizeof(unsigned short), pyramidData.indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &pyramidTexture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidTexture_vbo);
    glBufferData(GL_ARRAY_BUFFER, pyramidData.texturesSize * sizeof(float), cylinderData.textureIndices, GL_STATIC_DRAW);
    
    
    //vao--------------------------------------------------
    //Sphere
    glGenVertexArrays(1, &sphere_vao);
    glBindVertexArray(sphere_vao);
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, sphereTexture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ibo);
    
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
    
    //Hexagon
    glGenVertexArrays(1, &hexagon_vao);
    glBindVertexArray(hexagon_vao);
    glBindBuffer(GL_ARRAY_BUFFER, hexagon_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, hexagonTexture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexagon_ibo);
    
    //Cylinder
    glGenVertexArrays(1, &cylinder_vao);
    glBindVertexArray(cylinder_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, cylinderTexture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_ibo);
    
    //Pyramid
    glGenVertexArrays(1, &pyramid_vao);
    glBindVertexArray(pyramid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, pyramid_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidTexture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramid_ibo);
    
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
    redRock_tex = 0;
    glGenTextures(1, &redRock_tex);
    glBindTexture(GL_TEXTURE_2D, redRock_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_grass = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/grass_s.png",&Width, &Height, 0, SOIL_LOAD_RGB);
    grass_tex = 0;
    glGenTextures(1, &grass_tex);
    glBindTexture(GL_TEXTURE_2D, grass_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_grass);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_rock = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/rock.jpg",&Width, &Height, 0, SOIL_LOAD_RGB);
    rock_tex = 0;
    glGenTextures(1, &rock_tex);
    glBindTexture(GL_TEXTURE_2D, rock_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_rock);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_brick = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/brick.jpg",&Width, &Height, 0, SOIL_LOAD_RGB);
    brick_tex = 0;
    glGenTextures(1, &brick_tex);
    glBindTexture(GL_TEXTURE_2D, brick_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_brick);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_blue = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/blue.jpg",&Width, &Height, 0, SOIL_LOAD_RGB);
    blueWall_tex = 0;
    glGenTextures(1, &blueWall_tex);
    glBindTexture(GL_TEXTURE_2D, blueWall_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_blue);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_colorWall = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/Pastellfarben.jpg",&Width, &Height, 0, SOIL_LOAD_RGB);
    colorWall_tex = 0;
    glGenTextures(1, &colorWall_tex);
    glBindTexture(GL_TEXTURE_2D, colorWall_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_colorWall);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_door = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/esconrusticadouble3.png",&Width, &Height, 0, SOIL_LOAD_RGB);
    door_tex = 0;
    glGenTextures(1, &door_tex);
    glBindTexture(GL_TEXTURE_2D, door_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_door);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_wood = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/wood.png",&Width, &Height, 0, SOIL_LOAD_RGB);
    wood_tex = 0;
    glGenTextures(1, &wood_tex);
    glBindTexture(GL_TEXTURE_2D, wood_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_wood);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image_waffle = SOIL_load_image("/Users/jamie/Documents/2018Winter/GAME2012_3DGraphicsProgramming/02_assignments/Project/waffle.png",&Width, &Height, 0, SOIL_LOAD_RGB);
    waffle_tex = 0;
    glGenTextures(1, &waffle_tex);
    glBindTexture(GL_TEXTURE_2D, waffle_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_waffle);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    
    //Lighting
    LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
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
    View = glm::lookAt(cameraPos, cameraPos+cameraDirection, cameraUp);
//    View = glm::lookAt(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
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
    
//    glClearColor(0.349, 0.396, 0.466, 1.0);
    glClearColor(0.086, 0.247, 0.392, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniform3fv(lightPos, 1, glm::value_ptr(glm::vec3(lightX, lightY, lightZ)));
    glUniform3fv(camPos, 1, glm::value_ptr(glm::vec3(cameraZ, cameraY, cameraZ)));
    
    //grass ground
    glBindVertexArray(quad_vao);
    glBindTexture(GL_TEXTURE_2D, grass_tex);
    drawModel(quadData, glm::vec3(0.f,-0.95f,0.2f), 0.f, glm::vec3(2.0f,0.f,2.5f));
    
    //door road
    glBindVertexArray(quad_vao);
    glBindTexture(GL_TEXTURE_2D, redRock_tex);
    drawModel(quadData, glm::vec3(0.f,-0.94f,1.0f), 0.f, glm::vec3(0.35f,0.f,0.95f));

    //ice cream cone
    glBindVertexArray(cone_vao);
    glBindTexture(GL_TEXTURE_2D, waffle_tex);
    drawModel(coneData, glm::vec3(-0.6f,-0.55f,1.3f), 180.f, glm::vec3(0.18f,0.45f,0.18f));
    //ice cream
    glBindVertexArray(sphere_vao);
    glBindTexture(GL_TEXTURE_2D, blueWall_tex);
    drawModel(sphereData, glm::vec3(-0.6f,-0.5f,1.3f), 90.f, glm::vec3(0.1f));

    //base
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, rock_tex);
    drawModel(boxData, glm::vec3(0.f,-0.75f,0.f), 0.f, glm::vec3(1.5f,0.7f,1.0f));
    //second base
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, brick_tex);
    drawModel(boxData, glm::vec3(0.f,-0.1f,0.f), 0.f, glm::vec3(0.8f,0.6f,0.7f));
    //top base
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, brick_tex);
    drawModel(hexagonData, glm::vec3(0.f,0.4f,0.f), 0.f, glm::vec3(0.4f,0.8f,0.3f));
    //bocony
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, colorWall_tex);
    drawModel(hexagonData, glm::vec3(0.f,0.5f,0.f), 0.f, glm::vec3(0.5f, 0.15f, 0.5f));
    //roof
    glBindVertexArray(cone_vao);
    glBindTexture(GL_TEXTURE_2D, colorWall_tex);
    drawModel(coneData, glm::vec3(0.f,0.8f,0.f), 0.f, glm::vec3(0.55f,0.5f,0.55f));


    //outer column
    //front right
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, wood_tex);
    drawModel(hexagonData, glm::vec3(0.70f,-0.6f,0.5f), 0.f, glm::vec3(0.1f, 2.f, 0.1f));
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, waffle_tex);
    drawModel(hexagonData, glm::vec3(0.70f,-0.02f,0.5f), 0.f, glm::vec3(0.15f, 0.33f, 0.15f));
    glBindVertexArray(pyramid_vao);
    glBindTexture(GL_TEXTURE_2D, blueWall_tex);
    drawModel(pyramidData, glm::vec3(0.70f,0.06f,0.5f), 0.f, glm::vec3(0.2f));
    //back right
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, wood_tex);
    drawModel(hexagonData, glm::vec3(0.70f,-0.6f,-0.5f), 0.f, glm::vec3(0.1f, 2.f, 0.1f));
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, waffle_tex);
    drawModel(hexagonData, glm::vec3(0.70f,-0.02f,-0.5f), 0.f, glm::vec3(0.15f, 0.33f, 0.15f));
    glBindVertexArray(pyramid_vao);
    glBindTexture(GL_TEXTURE_2D, blueWall_tex);
    drawModel(pyramidData, glm::vec3(0.70f,0.06f,-0.5f), 0.f, glm::vec3(0.2f));
    //back left
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, wood_tex);
    drawModel(hexagonData, glm::vec3(-0.70f,-0.6f,-0.5f), 0.f, glm::vec3(0.1f, 2.f, 0.1f));
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, waffle_tex);
    drawModel(hexagonData, glm::vec3(-0.70f,-0.02f,-0.5f), 0.f, glm::vec3(0.15f, 0.33f, 0.15f));
    glBindVertexArray(pyramid_vao);
    glBindTexture(GL_TEXTURE_2D, blueWall_tex);
    drawModel(pyramidData, glm::vec3(-0.70f,0.06f,-0.5f), 0.f, glm::vec3(0.2f));
    //back right
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, wood_tex);
    drawModel(hexagonData, glm::vec3(-0.70f,-0.6f,0.5f), 0.f, glm::vec3(0.1f, 2.f, 0.1f));
    glBindVertexArray(hexagon_vao);
    glBindTexture(GL_TEXTURE_2D, waffle_tex);
    drawModel(hexagonData, glm::vec3(-0.70f,-0.02f,0.5f), 0.f, glm::vec3(0.15f, 0.33f, 0.15f));
    glBindVertexArray(pyramid_vao);
    glBindTexture(GL_TEXTURE_2D, blueWall_tex);
    drawModel(pyramidData, glm::vec3(-0.70f,0.06f,0.5f), 0.f, glm::vec3(0.2f));

    //inner column
    //front left
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, brick_tex);
    drawModel(hexagonData, glm::vec3(-0.45f,-0.1f,0.35f), 0.f, glm::vec3(0.15f,0.9f,0.15f));
    glBindVertexArray(cone_vao);
    glBindTexture(GL_TEXTURE_2D, colorWall_tex);
    drawModel(coneData, glm::vec3(-0.45f,0.35f,0.35f), 0.f, glm::vec3(0.25f,0.2f,0.25f));
    //front right
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, brick_tex);
    drawModel(hexagonData, glm::vec3(0.45f,-0.1f,0.35f), 0.f, glm::vec3(0.15f,0.9f,0.15f));
    glBindVertexArray(cone_vao);
    glBindTexture(GL_TEXTURE_2D, colorWall_tex);
    drawModel(coneData, glm::vec3(0.45f,0.35f,0.35f), 0.f, glm::vec3(0.25f,0.2f,0.25f));
    //back right
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, brick_tex);
    drawModel(hexagonData, glm::vec3(0.35f,0.1f,-0.35f), 0.f, glm::vec3(0.15f,0.9f,0.15f));
    glBindVertexArray(cone_vao);
    glBindTexture(GL_TEXTURE_2D, colorWall_tex);
    drawModel(coneData, glm::vec3(0.35f,0.5f,-0.35f), 0.f, glm::vec3(0.25f,0.25f,0.25f));
    //back left
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, brick_tex);
    drawModel(hexagonData, glm::vec3(-0.35f,0.16f,-0.35f), 0.f, glm::vec3(0.15f,1.3f,0.15f));
    glBindVertexArray(cone_vao);
    glBindTexture(GL_TEXTURE_2D, colorWall_tex);
    drawModel(coneData, glm::vec3(-0.35f,0.8f,-0.35f), 0.f, glm::vec3(0.25f,0.25f,0.25f));
   
    //upper wall
    //front
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, rock_tex);
    drawModel(hexagonData, glm::vec3(0.f,-0.3f,0.48f), 0.f, glm::vec3(1.3f,0.3f,0.03f));
    //back
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, rock_tex);
    drawModel(hexagonData, glm::vec3(0.f,-0.3f,-0.48f), 0.f, glm::vec3(1.3f,0.3f,0.03f));
    //right
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, rock_tex);
    drawModel(hexagonData, glm::vec3(0.72f,-0.3f,0.f), 0.f, glm::vec3(0.02f,0.3f,0.96f));
    //left
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, rock_tex);
    drawModel(hexagonData, glm::vec3(-0.72f,-0.3f,0.f), 0.f, glm::vec3(0.02f,0.3f,0.96f));

    //door
    glBindVertexArray(quad_vao);
    glBindTexture(GL_TEXTURE_2D, door_tex);
    drawModel(quadData, glm::vec3(0.f,-0.75f,0.51f), 90.f, glm::vec3(0.4f));
    
    //lower wall
    //front right
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, redRock_tex);
    drawModel(hexagonData, glm::vec3(0.55f,-0.8f,1.f), 0.f, glm::vec3(0.6f,0.3f,0.03f));
    //front left
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, redRock_tex);
    drawModel(hexagonData, glm::vec3(-0.55f,-0.8f,1.f), 0.f, glm::vec3(0.6f,0.3f,0.03f));
    //back
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, redRock_tex);
    drawModel(hexagonData, glm::vec3(0.0f,-0.8f,-0.8f), 0.f, glm::vec3(1.7f,0.3f,0.03f));
    //right
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, redRock_tex);
    drawModel(hexagonData, glm::vec3(0.85f,-0.8f,0.1f), 0.f, glm::vec3(0.02f,0.3f,1.8f));
    //left
    glBindVertexArray(box_vao);
    glBindTexture(GL_TEXTURE_2D, redRock_tex);
    drawModel(hexagonData, glm::vec3(-0.85f,-0.8f,0.1f), 0.f, glm::vec3(0.02f,0.3f,1.8f));
    
    
//    glBindVertexArray(pyramid_vao);
//    glBindTexture(GL_TEXTURE_2D, redRock_tex);
//    drawModel(pyramidData, glm::vec3(0.f,-0.4f,0.54f), 75.f, glm::vec3(1.1f,0.5f,0.03f));
    
    
    glutSwapBuffers();

}


void keyDown(unsigned char key, int x, int y) {
    switch (key) {
        
//        case 'w':
//        cameraZ -= cameraSpeed;
//        break;
//        case 's':
//        cameraZ += cameraSpeed;
//        break;
//        case 'a':
//        cameraX -= cameraSpeed;
//        break;
//        case 'd':
//        cameraX += cameraSpeed;
//        break;
//        case 'r':
//        cameraY += cameraSpeed;
//        break;
//        case 'f':
//        cameraY -= cameraSpeed;
//        break;
        
        case 'w':
            cameraPos += cameraDirection * cameraSpeed;

            break;
        case 's':
            cameraPos -= cameraDirection * cameraSpeed;
            break;
        case 'a':
            cameraPos -= right * cameraSpeed;
            break;
        case 'd':
            cameraPos += right * cameraSpeed;
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

void cameraViewUpdate(int x, int y) {

    glutWarpPointer(width / 2, height / 2);
    
    cameraTheta += mouseSpeed * float(width / 2 - x);
    cameraPhi += mouseSpeed * float(height / 2 - y);
    
    cameraDirection = glm::vec3(cos(cameraPhi) * sin(cameraTheta), sin(cameraPhi), cos(cameraPhi) * cos (cameraTheta));
    right = glm::vec3(sin(cameraTheta - 3.14 / 2.0f), 0.0f, cos(cameraTheta - 3.14 / 2.0f));
    cameraUp = glm::cross(right, cameraDirection);
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
    glutPassiveMotionFunc(cameraViewUpdate);
    
    glutMainLoop();
}


