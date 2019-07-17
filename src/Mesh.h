#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "Color.h"
#include "Shader.h"

class Mesh {
public:
    Mesh(std::string local_path, int obj_type);
    Mesh(std::vector<glm::vec3> verts, std::vector<int> tris);

    int obj_type = 0;
    void draw();
    void mean();
    void bindShader();
    void readSkeleton();
    Shader ourShader;
private:
    std::vector<glm::vec3> verts;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> skeletons;
    std::vector<int> tris;
    std::vector<int> trisn;
    unsigned int VBO, VAO;
};
