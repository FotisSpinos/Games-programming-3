#version 410

in vec2 V_textureCords;
in vec3 V_fragmentPos;
in vec3 V_norm;

struct Light{
	float intensity;
    vec3 ambient;
    vec3 diffuse;
	vec3 specular;
	vec3 pos;
	float attenuation;
	float specularExponent;
};

uniform Light lights[100];
uniform float gammaCorrection;
uniform vec3 cameraPos;
uniform sampler2D usingTexture;

uniform int lightsCount;

out vec4 color;

void main()
{
	vec4 texColor = texture2D(usingTexture, V_textureCords);

	// normalize normal
	vec3 norm = normalize(V_norm);

	//culculate distance magnitude with camera
	float distMagnitude = length(cameraPos - V_fragmentPos);

	vec3 combinedLight;

	for(int i = 0; i < lightsCount; i++)
	{
		//culculate distance vector
		vec3 lightDistVector = lights[i].pos - V_fragmentPos;

		float lightDistance = length(lightDistVector);

		// culculate light direction
		vec3 lightDir = normalize(lightDistVector);

		// culculate diffuse light
		float diffuseFactor = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diffuseFactor *  lights[i].diffuse;

		// Culculate specular light
		vec3 viewDir = normalize(cameraPos - V_fragmentPos);
		vec3 reflectionDir = reflect(-lightDir, norm);

		float specularFactor = max(dot(viewDir, reflectionDir), 0.0);
		specularFactor = pow(specularFactor, lights[i].specularExponent);
		vec3 specular = specularFactor * lights[i].specular;	

		// culculate distance factor
		float distanceFactor = 1 / (1 + lights[i].attenuation * pow(lightDistance, 2));

		// culculate total color
		vec3 lightColor = lights[i].ambient + distanceFactor * (diffuse + specular) * lights[i].intensity;
		combinedLight += lightColor;
	}

	// apply gama correction
	vec3 gamma = vec3(gammaCorrection);

	color = vec4(pow(combinedLight, gamma), 1.0) * texColor;
}