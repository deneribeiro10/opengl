#ifndef SCENE_H__
#define SCENE_H__

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "utils.h"
using namespace std;

class scene
{
public:
    scene();
    void render();
    void set_color(float r, float g, float b);
    void Ortho2D(float WL, float WR, float WB, float WT);
    void modelView(glm::mat4 mv);
private:
    GLuint VBO;
    GLuint EBO;
    GLuint ShaderProgram;
    float color[3];
    glm::mat4 ortho2DMatrix;
    glm::mat4 modelViewMatrix;
};

scene::scene()
{
    const char *pVSFileName = "../src/shader.vs";
    const char *pFSFileName = "../src/shader.fs";
    ShaderProgram = CompileShaders(pVSFileName, pFSFileName);
    CreateVertexBufferCircle(VBO, EBO);
    color[0] = 1.0;
    color[1] = color[2] = 0.0;
    ortho2DMatrix = glm::mat4(1.0);
    modelViewMatrix = glm::mat4(1.0);
}

void scene::render()
{
    glUseProgram(ShaderProgram);
    GLint color_u = glGetUniformLocation(ShaderProgram, "Color");
    glUniform3fv(color_u, 1, color);
    GLint ortho2d_u = glGetUniformLocation(ShaderProgram, "Ortho2D");
    glUniformMatrix4fv(ortho2d_u, 1, GL_FALSE, glm::value_ptr(ortho2DMatrix));
    GLint modelview_u = glGetUniformLocation(ShaderProgram, "ModelView");
    glUniformMatrix4fv(modelview_u, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    GLint atributo = glGetAttribLocation(ShaderProgram, "Position");
    glEnableVertexAttribArray(atributo);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(atributo, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);
}

void scene::set_color(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    return;
}

void scene::Ortho2D(float WL, float WR, float WB, float WT) {
    ortho2DMatrix = glm::ortho(WL, WR, WB, WT);
}

void scene::modelView(glm::mat4 mv) {
    modelViewMatrix = mv;
}

#endif