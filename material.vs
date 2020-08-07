#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;		// inversing is very expensive and should be done on the CPU instead!
															// basically do this before passing it to the shaders like the model matrix.
															// We multiply by an inverse transpose so we get a scaled perpenduclar vector
															// of the surface.

	gl_Position = projection * view * vec4(FragPos, 1.0);
	TexCoords = aTexCoords;
}