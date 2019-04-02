//
// Created by DMa on 2019-03-15.
//

#ifndef DIVCONQ_POLYGON_H
#define DIVCONQ_POLYGON_H

#include "Common.hpp"
#include "Polygon.hpp"
#include "Ui/UiElement.h"

class Polygon
{
  private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLfloat *vertices;
    int verticesSize;
    int elementsSize;
    GLuint *elements;

    float sign(vec2 p1, vec2 p2, vec2 p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }

    bool inTriangle(vec2 pt, vec2 v1, vec2 v2, vec2 v3)
    {
        float d1, d2, d3;
        bool has_neg, has_pos;

        d1 = sign(pt, v1, v2);
        d2 = sign(pt, v2, v3);
        d3 = sign(pt, v3, v1);

        has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }

  public:
    void init(GLfloat *verticesList, int vSize, GLuint *elementsList, int eSize, const char *vs_path, const char *fs_path)
    {
        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create a Vertex Buffer Object and copy the vertex data to it
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vSize, verticesList, GL_STATIC_DRAW);
        verticesSize = vSize;
        elementsSize = eSize;
        vertices = verticesList;
        elements = elementsList;

        // Create an element array
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, eSize, elementsList, GL_STATIC_DRAW);

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
        glUseProgram(shader.program);
    }

    void render()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    bool InBounds(vec2 point)
    {
        for (int i = 0; i < elementsSize / 3; i += 1)
        {
            int idx1 = elements[i * 3];
            int idx2 = elements[i * 3 + 1];
            int idx3 = elements[i * 3 + 2];

            vec2 v1{vertices[5 * idx1], vertices[5 * idx1 + 1]};
            vec2 v2{vertices[5 * idx2], vertices[5 * idx2 + 1]};
            vec2 v3{vertices[5 * idx3], vertices[5 * idx3 + 1]};

            if (inTriangle(point, v1, v2, v3))
            {
                return true;
            }
        }
        return false;
    }
};

#endif //DIVCONQ_POLYGON_H
