#version 330

in vec2 texCoord0;
in vec3 normal0;

layout(location = 0) out vec4 FragColor;

uniform sampler2D diffuse;

void main()
{
	FragColor = texture(diffuse, texCoord0)
		* clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0);
}
