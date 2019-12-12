#version 410

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 textureCoords;
layout(location = 3) in vec3 normal;

// output model variables
out vec2 V_textureCords;
out vec3 V_fragmentPos;
out vec3 V_norm;

// model view projection matrix
uniform mat4 MVP;

//model
uniform mat4 model;

//camera position
uniform vec3 cameraPos;

void main()
{
	// Set vertex variables
	V_textureCords = textureCoords;
	V_fragmentPos = vec3(model * vec4(position, 0.0));

	V_norm = vec3(model * vec4(normal, 0.0));

	gl_Position = MVP * vec4(position, 1.0);
}