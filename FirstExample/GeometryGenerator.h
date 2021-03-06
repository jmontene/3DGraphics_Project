#ifndef GeometryGenerator_h
#define GeometryGenerator_h

struct ModelData {
    float *vertices;
    int verticesSize;
    
    unsigned short *indices;
    int indicesSize;
    
    float *normals;
    int normalsSize;
    
    float *textureIndices;
    int texturesSize;
    
    float *colorIndices;
    int colorSize;
};

class GeometryGenerator {
public:
    static ModelData hexagon(float width, float height, float depth);
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

#endif /* GeometryGenerator_h */
