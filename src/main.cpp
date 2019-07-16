#include <string>
#include <sstream>
#include <functional>
#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicsManager.h"
#include "Mesh.h"

Mesh *display;

void render(double current_time, GraphicsManager *gm) {
    /** Drawing Code Goes Here! **/
    glColor4f(0.7f, 0.8f, 0.8f, 1.0f);
    glm::mat4 model(1.0f);

    model = glm::rotate(model, (float)glm::radians(180.0f), glm::vec3(1, 0, 0));

    glm::mat4 view(1.0f);

//    view = glm::rotate(view, (float)glm::radians(90.0f), glm::vec3(1, 0, 0));
    float deg = -25.0f*current_time;
    float rad = deg * acos(-1) / 180;

    std::cout<<deg<<std::endl;
    std::cout<<rad<<std::endl;
    view = glm::rotate(view, (float)glm::radians(deg), glm::vec3(0, 1, 0));
    view = glm::translate(view, glm::vec3(-1.3f*sin(-rad), 0, -1.3f*cos(-rad)));

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), gm->aspect(), 0.1f, 40.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view*model));

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));


    glEnable(GL_DEPTH_TEST);

    display->draw();
}

int main(int argc, char **argv) {
    std::string title = "OpenGL Tutorial";
    std::function<void(double, GraphicsManager*)> pass = &render;
    display = new Mesh("obj/human.obj", 1);
    display->mean();
    GraphicsManager *gm = new GraphicsManager(title, pass);

    gm->set_gl_version(2, 1); // Set OpenGL profile to 2.1
    gm->execute();

    return 0;
}