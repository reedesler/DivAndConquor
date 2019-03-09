#version 330 
// Input attributes
in vec3 in_position;
in vec2 in_texcoord;
in float in_explored;
in int in_tran_state;
in float in_tran_start_time;
in int in_tileid;

// Passed to fragment shader
out vec2 texcoord;
out float explored;
out vec4 vert_tint;

// Application data
uniform mat3 transform;
uniform float time;
uniform mat3 projection;

void main()
{
    texcoord = in_texcoord;
    if (in_tran_state == 0){ // NONE
        explored = in_explored;
        }
    else if (in_tran_state == 1){ // FADEIN
	    explored = 5+min(1,(time - in_tran_start_time)/500);
	    }
    else if (in_tran_state > 2) { // FADEOUT
	    explored = 1+max(0,(500+time - in_tran_start_time)/500);
	    }
    vec2 seedcord = in_position.xy*500;
	float rand_x = (sin(seedcord.y) + cos(seedcord.x))/10 + fract(sin(dot(vec2(cos(seedcord.x), sin(seedcord.y)) ,vec2(12.9898,78.233))) * 43758.5453);
	float rand_y = (cos(seedcord.y)  + sin(seedcord.x))/10 + fract(sin(dot(vec2(cos(seedcord.y), sin(seedcord.x)) ,vec2(12.9898,78.233))) * 43758.5453);
	vec2 rand_str = vec2(0.03,0.03);

	vec2 light_dir = vec2(1,1);
	vec2 rand = vec2(rand_x, rand_y)* rand_str;
	float dp = sin(dot(rand,light_dir));
	 vert_tint = 0.9+ vec4(vec3(
        2*dp
    ), 1.0);
    if(in_tileid > 1067483647) {
	vert_tint = 1+ vec4(vec3(5*dp), 1.0);
	}



	vec3 pos = projection * transform * vec3((1000*rand) +in_position.xy, 1.0);
	gl_Position = vec4(pos.xy , in_position.z, 1.0);
}