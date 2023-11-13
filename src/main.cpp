#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>

#include "loadobject.h"
#include "object.h"
#include "scene.h"

using namespace std;

bool ortho_per = true;
GLint width = 800, height = 800;

int worldx = 0, worldy = 0, worldz = 0;
float camerax = 0.0, cameray = 0.0, cameraz = 5.0;

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        ortho_per = true;
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
        ortho_per = false;

    if(action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_Q:
                if (mods == GLFW_MOD_SHIFT) {
                    worldx = (worldx + 5) % 360;
                } else {
                    worldx = (worldx - 5) % 360;
                }
                break;
            case GLFW_KEY_W:
                if (mods == GLFW_MOD_SHIFT) {
                    worldy = (worldy + 5) % 360;
                } else {
                    worldy = (worldy - 5) % 360;
                }
                break;
            case GLFW_KEY_E:
                if (mods == GLFW_MOD_SHIFT) {
                    worldz = (worldz + 5) % 360;
                } else {
                    worldz = (worldz - 5) % 360;
                }
                break;
            case GLFW_KEY_A:
                if (mods == GLFW_MOD_SHIFT) {
                    cameraz = cameraz + 0.1;
                } else {
                    cameraz = cameraz - 0.1;
                }
                break;

            default:
                break;
        }
    }
}
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        // color[(int)(xpos/(width/4))][3 - (int)(ypos/(height/4))] = !(color[(int)(xpos/(width/4))][3 - (int)(ypos/(height/4))]);
    }
}

int main(void) {
    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    scene my_scene;
    vector<object *> braco;
    braco.push_back(read_obj_file("../models/esfera_smooth.obj"));
    // braco[0]->set_wireframe(true);
    my_scene.push_back_object(braco[0]);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (ortho_per) {
            my_scene.perspective(0.75, 1.0, 0.1, 200.0);
        } else {
            my_scene.Ortho3D(-2.0, 2.0, -2.0, 2.0, 0.0, 200.0);
        }

        my_scene.LookAt(camerax, cameray, cameraz, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

        glm::mat4 matrix_now = glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0), glm::radians((float)worldx), glm::vec3(1.0, 0.0, 0.0)), glm::radians((float)worldy), glm::vec3(0.0, 1.0, 0.0)), glm::radians((float)worldz), glm::vec3(0.0, 0.0, 1.0));
        braco[0]->Model(matrix_now);
        my_scene.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}