#include <iostream>

#include "TextRenderer.hpp"

void _check_gl_error(const char *file, int line);

int TextRenderer::init(const char *fontFileName)
{
    /* Initialize the FreeType2 library */
    if (FT_Init_FreeType(&ft))
    {
        fprintf(stderr, "Could not init freetype library\n");
        return -1;
    }

    /* Load a font */
    if (FT_New_Face(ft, fontFileName, 0, &face))
    {
        fprintf(stderr, "Could not open font %s\n", fontFileName);
        return -1;
    }

    if (!shader.load_from_file(shader_path("label.vs.glsl"), shader_path("label.fs.glsl")))
    {
        fprintf(stderr, "cannot load shaders\n");
        return -1;
    }
    attribute_coord = glGetAttribLocation(shader.program, "coord");
    uniform_tex = glGetUniformLocation(shader.program, "tex");
    uniform_color = glGetUniformLocation(shader.program, "color");

    if (attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
    {
        fprintf(stderr, "shader error: uloc %d %d %d\n", attribute_coord, uniform_tex, uniform_color);
        return -1;
    }

    // Create the vertex buffer object
    glGenBuffers(1, &vbo);

    return 0;
}

void TextRenderer::config(unsigned int fontSize, glm::vec4 color)
{
    glUseProgram(shader.program);
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glUniform4fv(uniform_color, 1, glm::value_ptr(color));
}

void TextRenderer::draw(const char *text, float x, float y, float sx, float sy)
{
    const char *p;
    FT_GlyphSlot g = face->glyph;

    /* Create a texture that will be used to hold one "glyph" */
    GLuint tex;

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_2D, tex);

    glUniform1i(uniform_tex, 0);

    /* We require 1 byte alignment when uploading texture data */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* Clamping to edges is important to prevent artifacts when scaling */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* Linear filtering usually looks best for text */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Set up the VBO for our vertex data */
    glEnableVertexAttribArray(attribute_coord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

    /* Loop through all characters */
    for (p = text; *p; p++)
    {
        /* Try to load and render the character */
        if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
            continue;

        _check_gl_error(__FILE__, __LINE__);

        /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        printf("glTexImage2D %d %d\n", g->bitmap.width, g->bitmap.rows);

        _check_gl_error(__FILE__, __LINE__);

        /* Calculate the vertex and texture coordinates */
        float x2 = x + g->bitmap_left * sx;
        float y2 = -y - g->bitmap_top * sy;
        float w = g->bitmap.width * sx;
        float h = g->bitmap.rows * sy;

        glm::mat4 box({x2, -y2, 0, 0},
                      {x2 + w, -y2, 1, 0},
                      {x2, -y2 - h, 0, 1},
                      {x2 + w, -y2 - h, 1, 1});

        _check_gl_error(__FILE__, __LINE__);

        /* Draw the character on the screen */
        glBufferData(GL_ARRAY_BUFFER, sizeof box, glm::value_ptr(box), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        /* Advance the cursor to the start of the next character */
        x += (g->advance.x >> 6) * sx;
        y += (g->advance.y >> 6) * sy;
    }

    glDisableVertexAttribArray(attribute_coord);
    glDeleteTextures(1, &tex);
}
