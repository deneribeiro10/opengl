#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>

#include "scene.h"
#include "face.h"

using namespace std;
 
bool color[4][4] = {0};
GLint width = 800,height = 800; 
bool ortho_per = false;
 
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if(key == GLFW_KEY_P && action == GLFW_PRESS) 
        ortho_per = true;
    if(key == GLFW_KEY_O && action == GLFW_PRESS) 
        ortho_per = false;
}
 
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        color[(int)(xpos/(width/4))][3 - (int)(ypos/(height/4))] = !(color[(int)(xpos/(width/4))][3 - (int)(ypos/(height/4))]);

    }
        
}

face* make_front_face() {
    GLfloat v[4][3] = {
        {0.5f, -0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f},
        {-0.5f, -0.5f, 0.5f}
    };
    return new face(v, 4);
}

face* make_back_face() {
    GLfloat v[4][3] = {
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, 0.5f, -0.5f},
        {0.5f, 0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f}
    };
    return new face(v, 4);
}

face* make_top_face() {
    GLfloat v[4][3] = {
        {-0.5f, 0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},
        {0.5f, 0.5f, -0.5f},
        {-0.5f, 0.5f, -0.5f}
    };
    return new face(v, 4);
}

face* make_bottom_face() {
    GLfloat v[4][3] = {
        {-0.5f, -0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f},
        {0.5f, -0.5f, 0.5f},
        {-0.5f, -0.5f, 0.5f}
    };
    return new face(v, 4);
}

face* make_left_face() {
    GLfloat v[4][3] = {
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f, -0.5f}
    };
    return new face(v, 4);
}

face* make_right_face() {
    GLfloat v[4][3] = {
        {0.5f, 0.5f, -0.5f},
        {0.5f, 0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f},
        {0.5f, -0.5f, -0.5f}
    };
    return new face(v, 4);
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
  
    glEnable(GL_DEPTH_TEST);
    
    scene my_scene;

    // create faces
    face *front = make_front_face();
    face *back = make_back_face();
    face *top = make_top_face();
    face *bottom = make_bottom_face();
    face *left = make_left_face();
    face *right = make_right_face();
    
    // add to scene
    my_scene.push_back_object(front);
    my_scene.push_back_object(back);
    my_scene.push_back_object(top);
    my_scene.push_back_object(bottom);
    my_scene.push_back_object(left);
    my_scene.push_back_object(right);

    // set colors
    front->set_color(0.0f, 0.0f, 1.0f);
    back->set_color(0.0f, 1.0f, 0.0f);
    top->set_color(0.0f, 1.0f, 1.0f);
    bottom->set_color(1.0f, 0.0f, 0.0f);
    left->set_color(1.0f, 0.0f, 1.0f);
    right->set_color(1.0f, 1.0f, 0.0f);

    my_scene.LookAt(1.75, 1.3, 1.75, 0, 0, 0, 0, 1, 0);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glViewport(0, 0, width , height);
  
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(ortho_per) my_scene.perspective(0.75, 1.0, 0.1, 10.0);
        else my_scene.Ortho3D(-1, 1, -1, 1, 0, 10);
        my_scene.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}