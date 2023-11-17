#version 330 core
in vec3 Normal;
in vec2 TexCoords;

out vec4 fragColor;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	fragColor = texture(diffuse0, TexCoords) * texture(specular0, TexCoords).r;
}