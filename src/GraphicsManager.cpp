#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(
        std::string title,
        std::function<void(double, GraphicsManager*)> render_fn) : title(title), render_fn(render_fn) {

}

bool GraphicsManager::init(){

    if(!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor_version);

    window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
}

bool GraphicsManager::execute() {

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.3f, 1.f);
        glLoadIdentity();

        render_fn(glfwGetTime(), this);

        glFlush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return true;
}