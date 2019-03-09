#include <iostream>
#include <limits>
#include "Sprite.hpp"

std::map<const char *, Texture *> Sprite::textures;

bool Sprite::init(float width, float height, const char *textureName, vec2 texPiece)
{
    this->height = height;
    this->width = width;
    this->tint = {1.f, 1.f, 1.f};
    this->selected = false;
    this->state = 0;
    auto t = textures.find(textureName);
    if (textures.count(textureName) > 0)
    {
        texture = textures.at(textureName);
    }
    else
    {
        texture = new Texture();
        textures[textureName] = texture;
    }
    // Load shared texture
    if (!texture->is_valid())
    {
        if (!texture->load_from_file(textureName))
        {
            fprintf(stderr, "Failed to load texture!");
            return false;
        }
    }
    this->texPiece = texPiece;

    // The position corresponds to the center of the texture
    float wr = width * 0.5f;
    float hr = height * 0.5f;

    TexturedVertex vertices[4];
    vertices[0].position = {-wr, +hr, -0.02f};
    vertices[0].texcoord = {frame.x, texPiece.y};
    vertices[1].position = {+wr, +hr, -0.02f};
    vertices[1].texcoord = {texPiece.x, texPiece.y};
    vertices[2].position = {+wr, -hr, -0.02f};
    vertices[2].texcoord = {texPiece.x, frame.y};
    vertices[3].position = {-wr, -hr, -0.02f};
    vertices[3].texcoord = {frame.x, frame.y};

    // counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = {0, 3, 1, 1, 3, 2};

    // Clearing errors
    gl_flush_errors();

    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);

    // Index Buffer creation
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);

    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &mesh.vao);
    if (gl_has_errors())
        return false;

    // Loading shaders
    return effect.load_from_file(shader_path("textured.vs.glsl"), shader_path("textured.fs.glsl"));
}

void Sprite::draw(const mat3 &projection, vec2 position, float rotation, vec2 scale)
{
    // Transformation code, see Rendering and Transformation in the template specification for more info
    // Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
    transform_begin();
    transform_translate(position);
    transform_rotate(rotation);
    transform_scale(scale);
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
    GLint shift_uloc = glGetUniformLocation(effect.program, "shift");

    // Setting vertices and indices
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

    // Input data location as in the vertex buffer
    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_texcoord_loc);
    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *)0);
    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *)sizeof(vec3));

    // Enabling and binding texture to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    // Setting uniform values to the currently bound program
    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *)&transform);

    std::array<GLfloat,3> selectedTint = {0.7f, 1.f, 0.7f};
    std::array<GLfloat,3> drawTint = selected ? selectedTint : tint;

    glUniform3fv(color_uloc, 1, drawTint.data());
    glUniform2f(shift_uloc, texPiece.x * state, texPiece.y * state);
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *)&projection);

    // Drawing!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}
