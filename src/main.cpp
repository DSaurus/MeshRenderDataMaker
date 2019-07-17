#include <string>
#include <sstream>
#include <functional>
#include <iostream>

#include <GL/glew.h>
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
double x_pos, y_pos;
double last_x_pos, last_y_pos;
int pressing = 0;
glm::vec3 view_pos_x = glm::vec3(1, 0, 0);
glm::vec3 view_pos_y = glm::vec3(0, 1, 0);
glm::vec3 view_pos_z = glm::vec3(0, 0, 1);
float view_r = 2.0f;

void mouse_scroll(GLFWwindow* window, double xoffset, double yoffset){
    if(yoffset > 0){
        view_r *= 0.9;
    } else if(yoffset < 0){
        view_r /= 0.9;
    }
}

void render(double current_time, GraphicsManager *gm) {
    /** Drawing Code Goes Here! **/
    glColor4f(0.7f, 0.8f, 0.8f, 1.0f);
    glm::mat4 model(1.0f);

    glm::mat4 view(1.0f);

//    float deg = -25.0f*current_time;
//    float rad = deg * acos(-1) / 180;
//
//    view = glm::rotate(view, (float)glm::radians(deg), glm::vec3(0, 1, 0));
//    view = glm::translate(view, glm::vec3(-2.0f*sin(-rad), 0, -2.0f*cos(-rad)));

    int mouse_state = glfwGetMouseButton(gm->window, GLFW_MOUSE_BUTTON_RIGHT);
    if(mouse_state == GLFW_PRESS){
        glfwGetCursorPos(gm->window, &x_pos, &y_pos);
        if(pressing == 0){
            pressing = 1;
            last_x_pos = x_pos;
            last_y_pos = y_pos;
        }

        double vx = x_pos - last_x_pos;
        double vy = y_pos - last_y_pos;
        last_x_pos = x_pos;
        last_y_pos = y_pos;

        glm::mat4 rotate_x(1.0f), rotate_y(1.0f);
        rotate_x = glm::rotate(rotate_x, (float)glm::radians(-vx), view_pos_y);
        view_pos_x = glm::vec3(rotate_x* glm::vec4(view_pos_x, 1));
        view_pos_z = glm::vec3(rotate_x* glm::vec4(view_pos_z, 1));

        rotate_y = glm::rotate(rotate_y, (float)glm::radians(vy), view_pos_z);
        view_pos_x = glm::vec3(rotate_y* glm::vec4(view_pos_x, 1));
        view_pos_y = glm::vec3(rotate_y* glm::vec4(view_pos_y, 1));
    }
    if(mouse_state == GLFW_RELEASE) pressing = 0;

    glfwSetScrollCallback(gm->window, mouse_scroll);

    view = glm::lookAt(view_pos_x*view_r, glm::vec3(0, 0, 0), view_pos_y);

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), gm->aspect(), 0.1f, 40.0f);

    display->ourShader.setMat4("model", model);
    display->ourShader.setMat4("view", view);
    display->ourShader.setMat4("projection", projection);

//    glMatrixMode(GL_MODELVIEW);
//    glLoadMatrixf(glm::value_ptr(view*model));
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadMatrixf(glm::value_ptr(projection));


    glEnable(GL_DEPTH_TEST);

    display->draw();
}

int main(int argc, char **argv) {

    std::string title = "Mesh Render";
    std::function<void(double, GraphicsManager*)> pass = &render;
    GraphicsManager *gm = new GraphicsManager(title, pass);
    gm->init();

    display = new Mesh("obj/human.obj", 1);
    display->readSkeleton();
    display->mean();
    display->bindShader();

    gm->set_gl_version(2, 1); // Set OpenGL profile to 2.1
    gm->execute();

    return 0;
}