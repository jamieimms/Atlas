#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 transform;

out vec3 outColour;

void main()
{
	gl_Position = transform * vec4(position, 1.0f);
	outColour = vec3(0.0f, 1.0f, 0);
}