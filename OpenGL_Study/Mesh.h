#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp\types.h>
#include "Shader.h"

using namespace glm;
using namespace std;

struct Vertex
{
	vec3 Position;
    vec3 Normal;
	vec2 TexCoords;

    vec3 Tangent;
    vec3 Bitangent;
};

struct Texture 
{
	unsigned int id;
	string type;
    aiString path;  // 我们储存纹理的路径用于与其它纹理进行比较
};

class Mesh
{
public:
    /*  网格数据  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    /*  函数  */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader shader);
private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /*  函数  */
    void setupMesh();
};

