#version 330
// From vertex shader
in vec2 texcoord;
in float explored;

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;

// Output color
layout(location = 0) out  vec4 color;

void main()
{
    if (explored > 0) {
	    color = vec4(fcolor, 1.0) * texture(sampler0, vec2(texcoord.x, texcoord.y));
    } else {
	    color = vec4(0, 0, 0, 1.0);
    }
}
