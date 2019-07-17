#include "Mesh.h"

#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"


Mesh::Mesh(std::vector<glm::vec3> verts, std::vector<int> tris) : verts(verts), tris(tris) {}

/** Mesh::Mesh(string local_path)
  * Loads a mesh from a file in .obj file format.  Only basic obj
  * constructs are supported -- do not export with UVs, normals,
  * or materials/material groups.
  *
  * local_path: path to the obj (local to executable)
  */
Mesh::Mesh(std::string local_path, int _obj) {
    obj_type = _obj;
    std::ifstream infile(local_path);

    std::string line;
    while (std::getline(infile, line))
    {
        if(line.find("v ") == 0) {
            line = line.substr(2, std::string::npos);
            std::istringstream iss(line);
            double x, y, z;
            if(iss >> x >> y >> z) {
                glm::vec3 v(x, y, z);
                verts.push_back(v);
            }
            if(obj_type == 1){
                iss>>x>>y>>z;
                glm::vec3 c(x, y, z);
                colors.push_back(c);
            }
        } else if(line.find("f ") == 0) {
            line = line.substr(2, std::string::npos);
            std::replace(line.begin(), line.end(), '/', ' ');
            std::istringstream iss(line);
            int v1, v2, v3;
            if(obj_type == 1){
                int n1, n2, n3;
                iss>>v1>>n1>>v2>>n2>>v3>>n3;
                tris.push_back(v1);
                tris.push_back(v2);
                tris.push_back(v3);
                trisn.push_back(n1);
                trisn.push_back(n2);
                trisn.push_back(n3);
            }
            // only support triangles
            else if(iss >> v1 >> v2 >> v3) {
                tris.push_back(v1);
                tris.push_back(v2);
                tris.push_back(v3);
            }
        } else if(line.find("vn ") == 0){
            line = line.substr(3, std::string::npos);
            std::istringstream iss(line);
            double x, y, z;
            if(iss>>x>>y>>z){
                glm::vec3 n(x, y, z);
                normals.push_back(n);
            }
        }
    }

    infile.close();
}

void Mesh::mean(){
    double mx = 0, my = 0, mz = 0;
    for(auto v : verts){
        mx += v.x;
        my += v.y;
        mz += v.z;
    }
    mx /= verts.size();
    my /= verts.size();
    mz /= verts.size();
    for(auto &v : verts){
        v.x -= mx;
        v.y -= my;
        v.z -= mz;
    }
    for(auto &v : skeletons){
        v.x -= mx;
        v.y -= my;
        v.z -= mz;
    }
}

void Mesh::readSkeleton() {
    std::string filename = "obj/joints_coord.txt";
    std::ifstream fin(filename);
    std::string header;

    //header
    fin>>header;
    std::cout<<header<<std::endl;
    skeletons.resize(26);
    for(int i = 0; i < 26; i++){
        double x; fin>>x;
        skeletons[i].x = x;
    }
    for(int i = 0; i < 26; i++){
        double x; fin>>x;
        skeletons[i].y = x;
    }
    for(int i = 0; i < 26; i++){
        double x; fin>>x;
        skeletons[i].z = x;
    }

    return;

    fin>>header>>header;
    std::cout<<header<<std::endl;

    for(int i = 0; i < 21; i++){
        double x, y, z;

        fin>>x>>y>>z;
        glm::vec3 v(x, y, z);
        std::cout<<x<<" "<<y<<" "<<z<<std::endl;
        skeletons.push_back(v);
    }
    exit(0);

}


void Mesh::bindShader() {

    float *vertex;
    vertex = new float[tris.size()*6];
    int sz = sizeof(float)*tris.size()*6;
    int ind = 0;
    if(obj_type == 1){
        for(int i = 0; i < tris.size(); i += 3){
            for(int j = 0; j < 3; j++){
                int i1 = tris[i+j], j1 = trisn[i+j];
                auto v1 = verts[i1-1];
                auto c1 = colors[i1-1];
                vertex[ind++] = v1.x; vertex[ind++] = v1.y; vertex[ind++] = v1.z;
                vertex[ind++] = c1.x; vertex[ind++] = c1.y; vertex[ind++] = c1.z;
            }
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sz, vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1);

    ourShader = Shader("shader/human.vs", "shader/human.fs");
}

void Mesh::draw() {

    ourShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, tris.size()*3);

    return;

    glBegin(GL_TRIANGLES);
    if(obj_type == 0) {
        auto i = tris.begin();
        while (i != tris.end()) {
            int i1 = *i;
            ++i;
            int i2 = *i;
            ++i;
            int i3 = *i;
            ++i;
            glm::vec3 v1 = verts[i1 - 1];
            glm::vec3 v2 = verts[i2 - 1];
            glm::vec3 v3 = verts[i3 - 1];

            glm::vec3 n = glm::cross(v3 - v1, v2 - v1);

            glNormal3f(n.x, n.y, n.z);
            glVertex3f(v1.x, v1.y, v1.z);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(v2.x, v2.y, v2.z);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(v3.x, v3.y, v3.z);

        }
    } else {
        for(int i = 0; i < tris.size(); i+=3){
            int i1 = tris[i], i2 = tris[i+1], i3 = tris[i+2];
            int j1 = trisn[i], j2 = trisn[i+1], j3 = trisn[i+2];
            glm::vec3 v1 = verts[i1-1];
            glm::vec3 v2 = verts[i2-1];
            glm::vec3 v3 = verts[i3-1];
            glm::vec3 c1 = colors[i1-1];
            glm::vec3 c2 = colors[i2-1];
            glm::vec3 c3 = colors[i3-1];
            glm::vec3 n1 = normals[j1-1];
            glm::vec3 n2 = normals[j2-1];
            glm::vec3 n3 = normals[j3-1];

            float alpha = 0.5;

            glColor4f(c1.x, c1.y, c1.z, alpha);
            glNormal3f(n1.x, n1.y, n1.z);
            glVertex3f(v1.x, v1.y, v1.z);

            glColor4f(c2.x, c2.y, c2.z, alpha);
            glNormal3f(n2.x, n2.y, n2.z);
            glVertex3f(v2.x, v2.y, v2.z);

            glColor4f(c3.x, c3.y, c3.z, alpha);
            glNormal3f(n3.x, n3.y, n3.z);
            glVertex3f(v3.x, v3.y, v3.z);
        }
    }
    glEnd();

//    glPointSize(5);
//    glBegin(GL_POINTS);
//    for(int i = 0; i < skeletons.size(); i++){
//        glm::vec3 v = skeletons[i];
//        glColor4f(1.0, 0, 0, 1.0);
//        glVertex3f(v.x, v.y, v.z);
//    }
//    glEnd();

}