#version 410

in vec2 t_coords;

uniform vec3 objectColor;

out vec4 color;

void main()
{
	color = vec4(objectColor, 1.0);
}