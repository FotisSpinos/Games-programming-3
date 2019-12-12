#version 410

layout(location = 0) in vec3 pos;
uniform mat4 MVP;

out vec2 t_coords;

void main()
{
	gl_Position = MVP * vec4(pos, 1.0);
}