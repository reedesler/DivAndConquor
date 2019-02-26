#version 330 
// Input attributes
// Input attributes
in vec3 in_position;
in vec2 in_texcoord;


// Passed to fragment shader
out vec2 texcoord;

// Application data
uniform vec2 shift;
uniform mat3 transform;
uniform mat3 projection;

void main()
{
//mat3 mat = {{0.5, 0.0,0.0},
//            {0.0, 0.5, 0.0},
//            {0.0, 0.0, 1.0}};
//vec2 a = {0.0, 0.25};



	texcoord = in_texcoord + shift;


	vec3 pos = projection  * transform * vec3(in_position.xy, 1.0);
	gl_Position = vec4(pos.xy, in_position.z, 1.0);
}