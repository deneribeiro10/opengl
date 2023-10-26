#include <object.h>

class face : public object
{
public:
    face(GLfloat vertices[][3], int n);

};

face::face(GLfloat vertices[][3], int n) {
    indexed = true;

    v_number = n;
    glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v_number * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    i_number = 3*(n-2);
    GLushort *index = new GLushort[i_number];
    for(int i=1, p=0; i<v_number-1; ++i) {
        index[p++] = 0;
        index[p++] = i;
        index[p++] = i+1;
    }

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_number * sizeof(GLushort), index, GL_STATIC_DRAW);
}