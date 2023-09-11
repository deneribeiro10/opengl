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
    void ortho2D(float wl, float wr, float wb, float wt);
private:
    GLuint VBO;
    GLuint ShaderProgram;
    float color[3];
    float ortho[4];
};

scene::scene()
{
    const char *pVSFileName = "../src/shader.vs";
    const char *pFSFileName = "../src/shader.fs";
    ShaderProgram = CompileShaders(pVSFileName, pFSFileName);
    CreateVertexBufferTriangle(VBO);
    color[0] = 1.0;
    color[1] = color[2] = 0.0;
    ortho2D(-1, 1, -1, 1);
}

void scene::render()
{
    glUseProgram(ShaderProgram);
    GLint color_u = glGetUniformLocation(ShaderProgram, "Color");
    glUniform3fv(color_u, 1, color);
    GLint orthoShader = glGetUniformLocation(ShaderProgram, "Ortho");
    glUniform4fv(orthoShader, 1, ortho);
    GLint atributo = glGetAttribLocation(ShaderProgram, "Position");
    glEnableVertexAttribArray(atributo);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(atributo, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void scene::set_color(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    return;
}

/*
    Define window limits
    @param wl: window left
    @param wr: window right
    @param wb: window bottom
    @param wt: window top
*/
void scene::ortho2D(float wl, float wr, float wb, float wt)
{
    ortho[0] = wl;
    ortho[1] = wr;
    ortho[2] = wb;
    ortho[3] = wt;
}

#endif