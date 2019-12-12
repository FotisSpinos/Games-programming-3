#version 410

in vec2 t_coords;

uniform sampler2D usingTexture;
uniform vec3 objectColor;

out vec4 color;

void main()
{
	vec4 texColor = texture2D(usingTexture, t_coords);
	color = texColor + vec4(objectColor, 1.0);
}