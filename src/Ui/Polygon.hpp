//
// Created by DMa on 2019-03-15.
//

#ifndef DIVCONQ_POLYGON_H
#define DIVCONQ_POLYGON_H

#include "Common.hpp"
#include "Polygon.hpp"
#include "Ui/UiElement.h"

class Polygon : public UiElement
{
  private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    void init(GLfloat *vertices, GLuint *elements, const char *vs_path, const char *fs_path)
    {
        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create a Vertex Buffer Object and copy the vertex data to it
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Create an element array
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        // Create and compile the vertex shader
        Effect shader;
        shader.load_from_file(vs_path, fs_path);

        glBindFragDataLocation(shader.program, 0, "outColor");

        // Specify the layout of the vertex data
        GLint posAttrib = glGetAttribLocation(shader.program, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

        GLint colAttrib = glGetAttribLocation(shader.program, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
    }

    void render()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};

#endif //DIVCONQ_POLYGON_H
