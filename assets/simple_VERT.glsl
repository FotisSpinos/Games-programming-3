#version 410

layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 textureCoords;
uniform mat4 MVP;

out vec2 t_coords;

void main()
{
	t_coords = textureCoords;
	gl_Position = MVP * vec4(pos, 1.0);
}