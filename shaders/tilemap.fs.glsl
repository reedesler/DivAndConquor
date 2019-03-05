#version 330
// From vertex shader
in vec2 texcoord;
in float explored;
in vec4 vert_tint;

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;

// Output color
layout(location = 0) out  vec4 color;

void main()
{
    color =  vec4(explored, explored, explored, 1.0) * (vert_tint * texture(sampler0, vec2(texcoord.x, texcoord.y)));
}
