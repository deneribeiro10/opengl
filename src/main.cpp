#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "scene.h"
using namespace std;

#define LINES   4
#define COLS    4

bool colors[COLS][LINES] = {false};

GLint width = 800, height=800;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int blockWidth = width/COLS;
        int blockHeight = height/LINES;
        int x = xpos/blockWidth;
        int y = ypos/blockHeight;
        colors[x][LINES - y - 1] ^= 1;
    }
}
 
int main(void)
{
    GLFWwindow* window; 
    
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
 
    window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwSetKeyCallback(window, key_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
 
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
  
    
    scene my_scene;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        for(int i=0; i<LINES; ++i) {
            for(int j=0; j<COLS; ++j) {
                int blockWidth = width/COLS;
                int blockHeight = height/LINES;
                glViewport(j*blockWidth, i*blockHeight, blockWidth, blockHeight);
                
                if(colors[j][i]) my_scene.set_color(1.0, 0.0, 0.0);
                else my_scene.set_color(1.0, 1.0, 0.0);
                
                my_scene.ortho2D(-2, 2, -2.2, 1.8);
                my_scene.render();
                my_scene.ortho2D(-2, 2, 1.8, -2.2);
                my_scene.render();
            }
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}