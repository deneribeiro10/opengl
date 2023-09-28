#ifndef UTILS_H__
#define UTILS_H__


#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;


GLchar *readTextFile(const char * name){
     FILE *fp;
     GLchar * content = NULL;
     int cont = 0;
     if(name == NULL)
        return NULL;
     fp = fopen(name,"rt");
     if(fp == NULL)
        return NULL;
     fseek(fp,0,SEEK_END);
     cont = ftell(fp);
     rewind(fp);
     if(cont> 0){
       content = (GLchar *) malloc(sizeof(char) * (cont +1));
       if(content != NULL){
          cont = fread(content,sizeof(char),cont,fp);
          content[cont] = '\0';

       }

     }

     fclose(fp);
     return content;

}

static void CreateVertexBufferTriangle(GLuint &VBO)
{
    GLfloat Vertices[6][3]= {
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.0f, 0.75f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
    };
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateVertexBufferCircle(GLuint &VBO, GLuint &EBO)
{
    const float pi = acos(-1);

    GLfloat Vertices[8][3];
    for(int i=0; i<8; ++i) {
        Vertices[i][0] = cos(i*pi/4);
        Vertices[i][1] = sin(i*pi/4);
        Vertices[i][2] = 0.0f;
    }
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    GLuint Indexes[18];
    for(int i=0, j=0; j<18; ++i) {
        Indexes[j++] = 0;
        Indexes[j++] = i+1;
        Indexes[j++] = i+2;
    }
 	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indexes), Indexes, GL_STATIC_DRAW);
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    //cout << pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static GLuint CompileShaders(const char* pVSFileName, const char* pFSFileName)
{
    GLuint ShaderProgram = glCreateProgram();
    
    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    char * shv, * shf;
    shv = readTextFile(pVSFileName);
    
    if (shv == NULL) {
        fprintf(stderr, "Error load shader file!\n");
        exit(1);
    };

    shf = readTextFile(pFSFileName);

    if (shf == NULL) {
        fprintf(stderr, "Error load shader file!\n");
        exit(1);
    };

    
    AddShader(ShaderProgram, shv ,GL_VERTEX_SHADER);

    AddShader(ShaderProgram, shf, GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);



    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}
    
    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    return ShaderProgram;

}

#endif