#include <utility>

//
// Created by Dmitry on 2019-02-14.
//

#include "Tilemap.h"
#include <iostream>


#define TILE_SRC_SIZE 32


Tilemap Tilemap::LoadFromFile(std::string filepath) {
    std::ifstream infile;
    infile.open(filepath);
    if (!infile) {
        std::cerr << "Failed to load map file " << filepath << std::endl;
        exit(1);
    }
    std::string line;
    std::vector<std::vector<unsigned int>> temp;

    while (std::getline(infile, line)) {
        std::vector<unsigned int> row;
        for (char &c : line) {
            row.push_back(c - '0');
        }
        temp.push_back(row);
    }
    unsigned int w = temp[0].size();
    unsigned int h = temp.size();
    auto map = new unsigned int* [w];
    for (unsigned int x = 0; x < w; ++x) {
        map[x] = new unsigned int[h];
        for (unsigned int y = 0; y < h; ++y) {
            map[x][y] = temp[y][x]; //transpose here, since we read it row-by-row
        }
    }

    Tilemap t = Tilemap(map, w, h);
    return t;

}

void Tilemap::draw(const mat3 &projection) {
    transform_begin();
    transform_end();

    // Setting shaders
    glUseProgram(effect.program);

    // Enabling alpha channel for textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // Getting uniform locations for glUniform* calls
    GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
    GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");

    // Setting vertices and indices
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

    // Input data location as in the vertex buffer
    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_texcoord_loc);
    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*) 0);
    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*) sizeof(vec3));

    // Enabling and binding texture to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    // Setting uniform values to the currently bound program
    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*) &transform);
    float color[] = {1.f, 1.f, 1.f};
    glUniform3fv(color_uloc, 1, color);
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*) &projection);

    // Drawing!
    glDrawElements(GL_TRIANGLES, mesh.vertCount, GL_UNSIGNED_INT, nullptr);
}

Tilemap::~Tilemap() {
    for (int i = 0; i < width; ++i) {
        delete[] map[i];
    }
    delete[] map;
}


Tilemap::Tilemap(unsigned int** map, unsigned int w, unsigned int h) : map(map), width(w), height(h) {
    // Load shared texture
    if (!texture.is_valid()) {
        if (!texture.load_from_file(textures_path("tilemap1.png"))) {
            fprintf(stderr, "Failed to load map texture!");
            exit(1);
        }
    }

    // Loading shaders
    if (!effect.load_from_file(shader_path("textured.vs.glsl"), shader_path("textured.fs.glsl"))) {

        fprintf(stderr, "Failed to load map shaders!");
        exit(1);
    }   // TODO
    // The position corresponds to the center of the texture

    std::vector<TexturedVertex> vertices;
    std::vector<GLuint> indices;

    GLuint idx = 0;

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y) {
            unsigned int tilemap_n = map[x][y];

            float x0 = x * TILE_SIZE;
            float y0 = y * TILE_SIZE;
            float wr = TILE_SIZE * 0.5f;
            float hr = TILE_SIZE * 0.5f;

            float textureLeft = 0;
            float textureRight = 1;

            //grass added
            if (tilemap_n >= 2) {
                textureLeft = 0.001f;
                textureRight = 0.249f;
            }
            //sand added
            if (tilemap_n == 1) {
                textureLeft = 0.251f;
                textureRight = 0.499f;
            }
            if (tilemap_n == 0) {
                textureLeft = 0.501f;
                textureRight = 0.749f;
            }

            vertices.emplace_back(TexturedVertex{{x0 - wr,      y0 + hr, -0.02f},
                                                 {textureLeft,  1.f}});
            vertices.emplace_back(TexturedVertex{{x0 + wr,      y0 + hr, -0.02f},
                                                 {textureRight, 1.f}});
            vertices.emplace_back(TexturedVertex{{x0 + wr,      y0 - hr, -0.02f},
                                                 {textureRight, 0.f}});
            vertices.emplace_back(TexturedVertex{{x0 - wr,      y0 - hr, -0.02f},
                                                 {textureLeft,  0.f}});
            indices.insert(indices.end(), {idx, 3 + idx, 1 + idx, 1 + idx, 3 + idx, 2 + idx});
            idx += 4;

        }
    // Clearing errors
    gl_flush_errors();

    // multiplied by two to get the entire map rendered
    // does not help if water added.
    mesh.vertCount = static_cast<GLsizei>(indices.size());
    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Index Buffer creation
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &mesh.vao);
    if (gl_has_errors()) {
        printf("ERROR initializing tilemap mesh\n");
    }
}
