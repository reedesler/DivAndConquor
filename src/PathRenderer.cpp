#include "PathRenderer.hpp"

bool PathRenderer::init(Path path)
{

    // Loading shaders
    if (!effect.load_from_file(shader_path("path.vs.glsl"), shader_path("path.fs.glsl")))
    {
        fprintf(stderr, "Failed to load map shaders!");
        exit(1);
    }

    std::vector<Vertex> vertices;
    bool add = false;
    for (auto i : path.path)
    {
        if (add)
        {
            vertices.emplace_back(Vertex{{(float)i.x * TILE_SIZE, (float)i.y * TILE_SIZE}, {1, 1, 0}});
        }
        else
        {
            add = true;
        }
        vertices.emplace_back(Vertex{{(float)i.x * TILE_SIZE, (float)i.y * TILE_SIZE}, {1, 1, 0}});
    }

    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    mesh.vertCount = vertices.size();
}

void PathRenderer::draw(const mat3 &projection)
{
    // Setting shaders
    glUseProgram(effect.program);

    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
    GLint in_color_loc = glGetAttribLocation(effect.program, "in_color");
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_color_loc);
    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(in_color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(vec3));

    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *)&projection);
    glDrawArrays(GL_LINES, 0, mesh.vertCount);
}
