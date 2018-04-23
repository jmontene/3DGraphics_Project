#include "GeometryGenerator.h"
#include <math.h>
#include <iostream>
#define PI 3.141592
#define PI_2 PI/2

ModelData GeometryGenerator::pyramid(float side, float height) {
    ModelData res;
    float halfSide = side / 2.f;
    
    res.vertices = new float[5 * 3];
    res.verticesSize = 5 * 3;
    
    //Top vertex
    res.vertices[0] = 0.f;
    res.vertices[1] = height;
    res.vertices[2] = 0.f;
    
    //Bottom Left Corner
    res.vertices[3] = -halfSide;
    res.vertices[4] = 0.f;
    res.vertices[5] = -halfSide;
    
    //Bottom Right Corner
    res.vertices[6] = halfSide;
    res.vertices[7] = 0.f;
    res.vertices[8] = -halfSide;
    
    //Top Left Corner
    res.vertices[9] = -halfSide;
    res.vertices[10] = 0.f;
    res.vertices[11] = halfSide;
    
    //Top Right Corner
    res.vertices[12] = halfSide;
    res.vertices[13] = 0.f;
    res.vertices[14] = halfSide;
    
    res.indices = new unsigned short[12 + 6];
    res.indicesSize = 12 + 6;
    
    //Front
    res.indices[0] = 0;
    res.indices[1] = 2;
    res.indices[2] = 1;
    
    //Right
    res.indices[3] = 0;
    res.indices[4] = 4;
    res.indices[5] = 2;
    
    //Back
    res.indices[6] = 0;
    res.indices[7] = 3;
    res.indices[8] = 4;
    
    //Left
    res.indices[9] = 0;
    res.indices[10] = 1;
    res.indices[11] = 3;
    
    //Base
    res.indices[12] = 1;
    res.indices[13] = 2;
    res.indices[14] = 4;
    res.indices[15] = 1;
    res.indices[16] = 4;
    res.indices[17] = 3;
    
    res.normals = new float[5 * 3];
    res.normalsSize = 5 * 3;
    res.normals[0] = 0.0f;
    res.normals[1] = 1.0f;
    res.normals[2] = 0.0f;
    
    int normalCount = 3;
    for (int i = 0; i < 4; ++i) {
        res.normals[normalCount] = 0.f;
        res.normals[normalCount + 1] = -1.f;
        res.normals[normalCount + 2] = 0.f;
        normalCount += 3;
    }
    
    res.textureIndices = new float[5 * 2];
    res.texturesSize = 5 * 2;
    
    //Top vertex
    res.textureIndices[0] = 0.f;
    res.textureIndices[1] = 0.f;
    
    //Bottom Left Corner
    res.textureIndices[2] = 0.25f;
    res.textureIndices[3] = 0.25f;
    
    //Bottom Right Corner
    res.textureIndices[4] = 0.5f;
    res.textureIndices[5] = 0.5f;
    
    //Top Left Corner
    res.textureIndices[6] = 1.f;
    res.textureIndices[7] = 1.f;
    
    //Top Right Corner
    res.textureIndices[8] = 0.75f;
    res.textureIndices[9] = 0.75f;
    
    return res;
}



ModelData GeometryGenerator::hexagon(float width, float height, float depth){
    ModelData res;
    
    res.vertices = new float[7 * 2 * 3 + 4 * 6 * 3];
    res.verticesSize = 7 * 2 * 3 + 4 * 6 * 3;
    
    //top
    //center point 0
    res.vertices[0] = 0.f;
    res.vertices[1] = height/2;
    res.vertices[2] = 0.f;
    res.vertices[3] = width/2;
    res.vertices[4] = height/2;
    res.vertices[5] = -sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[6] = -width/2;
    res.vertices[7] = height/2;
    res.vertices[8] = -sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[9] = -width;
    res.vertices[10] = height/2;
    res.vertices[11] = 0.f;
    res.vertices[12] = -width/2;
    res.vertices[13] = height/2;
    res.vertices[14] = sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[15] = width/2;
    res.vertices[16] = height/2;
    res.vertices[17] = sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[18] = width;
    res.vertices[19] = height/2;
    res.vertices[20] = 0.f;
    
    //bottom
    //bottom center point
    res.vertices[21] = 0.f;
    res.vertices[22] = -height/2;
    res.vertices[23] = 0.f;
    res.vertices[24] = width/2;
    res.vertices[25] = -height/2;
    res.vertices[26] = -sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[27] = -width/2;
    res.vertices[28] = -height/2;
    res.vertices[29] = -sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[30] = -width;
    res.vertices[31] = -height/2;
    res.vertices[32] = 0.f;
    res.vertices[33] = -width/2;
    res.vertices[34] = -height/2;
    res.vertices[35] = sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[36] = width/2;
    res.vertices[37] = -height/2;
    res.vertices[38] = sqrt(pow(width,2) - pow((width/2),2));
    res.vertices[39] = width;
    res.vertices[40] = -height/2;
    res.vertices[41] = 0.f;
    
//    //front
//    res.vertices[42] = width/2;
//    res.vertices[43] = height/2;
//    res.vertices[44] = sqrt(pow(width,2) - pow((width/2),2));
//    res.vertices[45] = -width/2;
//    res.vertices[46] = height/2;
//    res.vertices[47] = -sqrt(pow(width,2) - pow((width/2),2));
//    res.vertices[48] = -width/2;
//    res.vertices[49] = -height/2;
//    res.vertices[50] = sqrt(pow(width,2) - pow((width/2),2));
//    res.vertices[51] = width/2;
//    res.vertices[52] = -height/2;
//    res.vertices[53] = sqrt(pow(width,2) - pow((width/2),2));
    

    res.textureIndices = new float[14 * 2];// + 4 * 6];
    res.texturesSize = 14 * 2;// + 4 * 6;

    //top
//    res.textureIndices[0] = 1.f;
//    res.textureIndices[1] = 1.f;
//
//    res.textureIndices[2] = 1.f;
//    res.textureIndices[3] = 0.f;
//
//    res.textureIndices[4] = 0.f;
//    res.textureIndices[5] = 0.f;
//
//    res.textureIndices[6] = 0.f;
//    res.textureIndices[7] = 1.f;
//
//    res.textureIndices[8] = 1.f;
//    res.textureIndices[9] = 1.f;
//
//    res.textureIndices[10] = 1.f;
//    res.textureIndices[11] = 1.f;

//    res.textureIndices[12] = 0.f;
//    res.textureIndices[13] = 0.f;

//    bottom
//    res.textureIndices[14] = 1.f;
//    res.textureIndices[15] = 1.f;
//    res.textureIndices[16] = 0.f;
//    res.textureIndices[17] = 0.f;
//    res.textureIndices[18] = 0.f;
//    res.textureIndices[19] = 1.f;
//    res.textureIndices[20] = 1.f;
//    res.textureIndices[21] = 1.f;
//    res.textureIndices[22] = 1.f;
//    res.textureIndices[23] = 0.f;
//    res.textureIndices[24] = 0.f;
//    res.textureIndices[25] = 0.f;
//    res.textureIndices[26] = 0.f;
//    res.textureIndices[27] = 1.f;
//    front
//    res.textureIndices[28] = 1.f;
//    res.textureIndices[29] = 1.f;
//    res.textureIndices[30] = 1.f;
//    res.textureIndices[31] = 0.f;
//    res.textureIndices[32] = 0.f;
//    res.textureIndices[33] = 0.f;
//    res.textureIndices[34] = 0.f;
//    res.textureIndices[35] = 1.f;
    
//    res.textureIndices[36] = 1.f;
//    res.textureIndices[37] = 1.f;
//    res.textureIndices[38] = 1.f;
//    res.textureIndices[39] = 0.f;
    
    
    res.indices = new unsigned short[3 * 6 * 4];
    res.indicesSize = 3 * 6 * 4;
    //top
    res.indices[0] = 0;
    res.indices[1] = 1;
    res.indices[2] = 2;
    res.indices[3] = 0;
    res.indices[4] = 2;
    res.indices[5] = 3;
    res.indices[6] = 0;
    res.indices[7] = 3;
    res.indices[8] = 4;
    res.indices[9] = 0;
    res.indices[10] = 4;
    res.indices[11] = 5;
    res.indices[12] = 0;
    res.indices[13] = 5;
    res.indices[14] = 6;
    res.indices[15] = 0;
    res.indices[16] = 6;
    res.indices[17] = 1;
    //bottom
    res.indices[18] = 7;
    res.indices[19] = 9;
    res.indices[20] = 8;
    res.indices[21] = 7;
    res.indices[22] = 8;
    res.indices[23] = 13;
    res.indices[24] = 7;
    res.indices[25] = 13;
    res.indices[26] = 12;
    res.indices[27] = 7;
    res.indices[28] = 12;
    res.indices[29] = 11;
    res.indices[30] = 7;
    res.indices[31] = 11;
    res.indices[32] = 10;
    res.indices[33] = 7;
    res.indices[34] = 10;
    res.indices[35] = 9;
    //front
    res.indices[36] = 5;
    res.indices[37] = 4;
    res.indices[38] = 12;
    res.indices[39] = 4;
    res.indices[40] = 11;
    res.indices[41] = 12;
    //front right
    res.indices[42] = 6;
    res.indices[43] = 5;
    res.indices[44] = 13;
    res.indices[45] = 5;
    res.indices[46] = 12;
    res.indices[47] = 13;
    //back right
    res.indices[48] = 1;
    res.indices[49] = 6;
    res.indices[50] = 8;
    res.indices[51] = 6;
    res.indices[52] = 13;
    res.indices[53] = 8;
    //back
    res.indices[54] = 2;
    res.indices[55] = 1;
    res.indices[56] = 9;
    res.indices[57] = 1;
    res.indices[58] = 8;
    res.indices[59] = 9;
    //back left
    res.indices[60] = 3;
    res.indices[61] = 2;
    res.indices[62] = 10;
    res.indices[63] = 2;
    res.indices[64] = 9;
    res.indices[65] = 10;
    //front left
    res.indices[66] = 4;
    res.indices[67] = 3;
    res.indices[68] = 11;
    res.indices[69] = 3;
    res.indices[70] = 10;
    res.indices[71] = 11;

    return res;
}


ModelData GeometryGenerator::box(float width, float height, float depth){
    ModelData res;
    
    res.vertices = new float[4 * 3 * 6];
    res.verticesSize = 4 * 3 * 6;

    //top
    res.vertices[0] = -width/2;
    res.vertices[1] = height/2;
    res.vertices[2] = depth/2;
    res.vertices[3] = width/2;
    res.vertices[4] = height/2;
    res.vertices[5] = depth/2;
    res.vertices[6] = width/2;
    res.vertices[7] = height/2;
    res.vertices[8] = -depth/2;
    res.vertices[9] = -width/2;
    res.vertices[10] = height/2;
    res.vertices[11] = -depth/2;
    //front
    res.vertices[12] = -width/2;
    res.vertices[13] = -height/2;
    res.vertices[14] = depth/2;
    res.vertices[15] = width/2;
    res.vertices[16] = -height/2;
    res.vertices[17] = depth/2;
    res.vertices[18] = width/2;
    res.vertices[19] = height/2;
    res.vertices[20] = depth/2;
    res.vertices[21] = -width/2;
    res.vertices[22] = height/2;
    res.vertices[23] = depth/2;
    //left
    res.vertices[24] = -width/2;
    res.vertices[25] = -height/2;
    res.vertices[26] = -depth/2;
    res.vertices[27] = -width/2;
    res.vertices[28] = -height/2;
    res.vertices[29] = depth/2;
    res.vertices[30] = -width/2;
    res.vertices[31] = height/2;
    res.vertices[32] = depth/2;
    res.vertices[33] = -width/2;
    res.vertices[34] = height/2;
    res.vertices[35] = -depth/2;
    //bottom
    res.vertices[36] = -width/2;
    res.vertices[37] = -height/2;
    res.vertices[38] = depth/2;
    res.vertices[39] = width/2;
    res.vertices[40] = -height/2;
    res.vertices[41] = depth/2;
    res.vertices[42] = width/2;
    res.vertices[43] = -height/2;
    res.vertices[44] = -depth/2;
    res.vertices[45] = -width/2;
    res.vertices[46] = -height/2;
    res.vertices[47] = -depth/2;
    //right
    res.vertices[48] = width/2;
    res.vertices[49] = -height/2;
    res.vertices[50] = depth/2;
    res.vertices[51] = width/2;
    res.vertices[52] = -height/2;
    res.vertices[53] = -depth/2;
    res.vertices[54] = width/2;
    res.vertices[55] = height/2;
    res.vertices[56] = -depth/2;
    res.vertices[57] = width/2;
    res.vertices[58] = height/2;
    res.vertices[59] = depth/2;
    //back
    res.vertices[60] = -width/2;
    res.vertices[61] = -height/2;
    res.vertices[62] = -depth/2;
    res.vertices[63] = width/2;
    res.vertices[64] = -height/2;
    res.vertices[65] = -depth/2;
    res.vertices[66] = width/2;
    res.vertices[67] = height/2;
    res.vertices[68] = -depth/2;
    res.vertices[69] = -width/2;
    res.vertices[70] = height/2;
    res.vertices[71] = -depth/2;
    
    
    res.textureIndices = new float[4 * 2 * 6];
    res.texturesSize = 4 * 2 * 6;
    
    res.textureIndices[0] = 0.f;
    res.textureIndices[1] = 0.f;
    res.textureIndices[2] = 0.f;
    res.textureIndices[3] = 1.f;
    res.textureIndices[4] = 1.f;
    res.textureIndices[5] = 1.f;
    res.textureIndices[6] = 1.f;
    res.textureIndices[7] = 0.f;
    
    res.textureIndices[8] = 0.f;
    res.textureIndices[9] = 0.f;
    res.textureIndices[10] = 0.f;
    res.textureIndices[11] = 1.f;
    res.textureIndices[12] = 1.f;
    res.textureIndices[13] = 1.f;
    res.textureIndices[14] = 1.f;
    res.textureIndices[15] = 0.f;
    
    res.textureIndices[16] = 0.f;
    res.textureIndices[17] = 0.f;
    res.textureIndices[18] = 0.f;
    res.textureIndices[19] = 1.f;
    res.textureIndices[20] = 1.f;
    res.textureIndices[21] = 1.f;
    res.textureIndices[22] = 1.f;
    res.textureIndices[23] = 0.f;
    
    res.textureIndices[24] = 0.f;
    res.textureIndices[25] = 0.f;
    res.textureIndices[26] = 0.f;
    res.textureIndices[27] = 1.f;
    res.textureIndices[28] = 1.f;
    res.textureIndices[29] = 1.f;
    res.textureIndices[30] = 1.f;
    res.textureIndices[31] = 0.f;
    
    res.textureIndices[32] = 0.f;
    res.textureIndices[33] = 0.f;
    res.textureIndices[34] = 0.f;
    res.textureIndices[35] = 1.f;
    res.textureIndices[36] = 1.f;
    res.textureIndices[37] = 1.f;
    res.textureIndices[38] = 1.f;
    res.textureIndices[39] = 0.f;
    
    res.textureIndices[40] = 0.f;
    res.textureIndices[41] = 0.f;
    res.textureIndices[42] = 0.f;
    res.textureIndices[43] = 1.f;
    res.textureIndices[44] = 1.f;
    res.textureIndices[45] = 1.f;
    res.textureIndices[46] = 1.f;
    res.textureIndices[47] = 0.f;
    
    res.indices = new unsigned short[2 * 3 * 6];
    res.indicesSize = 2 * 3 * 6;
    //top
    res.indices[0] = 0;
    res.indices[1] = 1;
    res.indices[2] = 2;
    res.indices[3] = 0;
    res.indices[4] = 2;
    res.indices[5] = 3;
    //front
    res.indices[6] = 4;
    res.indices[7] = 5;
    res.indices[8] = 6;
    res.indices[9] = 4;
    res.indices[10] = 6;
    res.indices[11] = 7;
    //left
    res.indices[12] = 8;
    res.indices[13] = 9;
    res.indices[14] = 10;
    res.indices[15] = 8;
    res.indices[16] = 10;
    res.indices[17] = 11;
    //bottom
    res.indices[18] = 15;
    res.indices[19] = 14;
    res.indices[20] = 13;
    res.indices[21] = 15;
    res.indices[22] = 13;
    res.indices[23] = 12;
    //right
    res.indices[24] = 16;
    res.indices[25] = 17;
    res.indices[26] = 18;
    res.indices[27] = 16;
    res.indices[28] = 18;
    res.indices[29] = 19;
    //back
    res.indices[30] = 21;
    res.indices[31] = 20;
    res.indices[32] = 23;
    res.indices[33] = 21;
    res.indices[34] = 23;
    res.indices[35] = 22;
    
    return res;
}



ModelData GeometryGenerator::quad(float width, float depth){
    ModelData res;
    
    res.vertices = new float[4 * 3];
    res.verticesSize = 4 * 3;
    res.indices = new unsigned short[3 * 2];
    res.indicesSize = 3 * 2;
    res.textureIndices = new float[4 * 2];
    res.texturesSize = 4 * 2;

    res.vertices[0] = -width/2;
    res.vertices[1] = 0.f;
    res.vertices[2] = depth/2;
    res.vertices[3] = width/2;
    res.vertices[4] = 0.f;
    res.vertices[5] = depth/2;
    res.vertices[6] = width/2;
    res.vertices[7] = 0.f;
    res.vertices[8] = -depth/2;
    res.vertices[9] = -width/2;
    res.vertices[10] = 0.f;
    res.vertices[11] = -depth/2;

    res.textureIndices[0] = 0.f;
    res.textureIndices[1] = 1.f;
    res.textureIndices[2] = 1.f;
    res.textureIndices[3] = 1.f;
    res.textureIndices[4] = 1.f;
    res.textureIndices[5] = 0.f;
    res.textureIndices[6] = 0.f;
    res.textureIndices[7] = 0.f;
 
    res.indices[0] = 0;
    res.indices[1] = 1;
    res.indices[2] = 2;
    res.indices[3] = 0;
    res.indices[4] = 2;
    res.indices[5] = 3;

    return res;
}

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
    
    int rings = 20;
    int sectors = 20;
    
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
    
    res.indices = new unsigned short[rings * sectors * 6];
    res.indicesSize = rings * sectors * 6;
    count = 0;
    for (int i = 0; i < rings; ++i) {
        for (int j = 0; j < sectors; ++j) {
            res.indices[count] = i * sectors + j;
            res.indices[count + 1] = (i + 1) * sectors + (j + 1);
            res.indices[count + 2] = i * sectors + (j + 1);
            res.indices[count + 3] = i * sectors + j;
            res.indices[count + 4] = (i + 1) * sectors + j;
            res.indices[count + 5] = (i + 1) * sectors + (j + 1);
            
            count += 6;
        }
    }
    
    return res;
}

ModelData GeometryGenerator::cylinder(float radius, float height) {
    ModelData res;
    float delta = 0.01f;
    int circleVertices = ((2 * PI) / delta);
    float halfHeight = height / 2.f;
    
    res.vertices = new float[(circleVertices * 2 + 2) * 3];
    res.verticesSize = (circleVertices * 2 + 2) * 3;
    res.vertices[0] = 0.0f;
    res.vertices[1] = halfHeight;
    res.vertices[2] = 0.0f;
    
    res.vertices[3] = 0.0f;
    res.vertices[4] = -halfHeight;
    res.vertices[5] = 0.0f;
    
    res.indices = new unsigned short[circleVertices * 6 + (circleVertices * 6)];
    res.indicesSize = (circleVertices * 6) + (circleVertices * 6);
    
    res.normals = new float[(circleVertices + 2) * 3];
    res.normalsSize = (circleVertices + 2) * 3;
    res.normals[0] = 0.f;
    res.normals[1] = 1.f;
    res.normals[2] = 0.f;
    res.normals[3] = 0.f;
    res.normals[4] = -1.f;
    res.normals[5] = 0.f;
    
    res.textureIndices = new float[(circleVertices * 2 + 2) * 2];
    res.texturesSize = (circleVertices * 2 + 2) * 2;
    res.textureIndices[0] = 0.5f;
    res.textureIndices[1] = 1.0f;
    res.textureIndices[2] = 0.5f;
    res.textureIndices[3] = 0.0f;
    
    float t = 0.f;
    int count = 6;
    int indexCount = 0;
    int textureCount = 4;
    for (int i = 2; i < circleVertices+2; ++i) {
        res.vertices[count] = radius * cos(t);
        res.vertices[count + 1] = halfHeight;
        res.vertices[count + 2] = radius * sin(t);
        
        res.vertices[(circleVertices * 3) + count] = radius * cos(t);
        res.vertices[(circleVertices * 3) + count + 1] = -halfHeight;
        res.vertices[(circleVertices * 3) + count + 2] = radius * sin(t);
        
        res.indices[indexCount] = circleVertices + i + 1;
        res.indices[indexCount + 1] = circleVertices + i;
        res.indices[indexCount + 2] = i;
        res.indices[indexCount + 3] = circleVertices + i + 1;
        res.indices[indexCount + 4] = i;
        res.indices[indexCount + 5] = i + 1;
        
        res.indices[circleVertices * 6 + indexCount] = i + 1;
        res.indices[circleVertices * 6 + indexCount+1] = i;
        res.indices[circleVertices * 6 + indexCount+2] = 0;
        
        res.indices[circleVertices * 6 + indexCount+3] = circleVertices + i + 1;
        res.indices[circleVertices * 6 + indexCount+4] = circleVertices + i;
        res.indices[circleVertices * 6 + indexCount+5] = 1;
        
        res.normals[count] = cos(t);
        res.normals[count + 1] = 0.f;
        res.normals[count + 2] = sin(t);
        
        res.textureIndices[textureCount] = (radius * cos(t) + radius) / (2 * radius);
        res.textureIndices[textureCount + 1] = 1.0f;
        res.textureIndices[circleVertices + textureCount] = (radius * cos(t) + radius) / (2 * radius);
        res.textureIndices[circleVertices + textureCount + 1] = 0.0f;
        
        count += 3;
        indexCount += 6;
        textureCount += 2;
        t += delta;
    }
    
    return res;
}
