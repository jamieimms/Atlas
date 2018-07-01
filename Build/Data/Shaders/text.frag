#version 330 core
uniform vec3 objectColour;
in vec2 outTexCoord;

out vec4 colour;

//Texture samplers
uniform sampler2D outTexture1;

void main(){
	colour = vec4(objectColour.r, objectColour.g, objectColour.b, texture(outTexture1, outTexCoord).r);
}