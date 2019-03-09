#ifndef DIVCONQ_TEXT_RENDERER_HPP
#define DIVCONQ_TEXT_RENDERER_HPP

#include <glm/ext.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Common.hpp"

class TextRenderer
{

private:
  GLint attribute_coord;
  GLint uniform_tex;
  GLint uniform_color;
  GLuint vbo;

  FT_Library ft;
  FT_Face face;
  Effect shader;

public:
  int init(const char *fontFileName);

  void config(unsigned int fontSize, glm::vec4 color);

  /**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
  void draw(const char *text, float x, float y, float sx, float sy);
};

#endif //DIVCONQ_TEXT_RENDERER_HPP