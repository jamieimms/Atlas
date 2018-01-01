#version 330 core
in vec3 outColour;
in vec2 outTexCoord;

out vec4 colour;

//Texture samplers
uniform sampler2D outTexture1;

void main(){
	colour = vec4(colour.r, colour.g, colour.b, 1.0);// * vec4(1,1,1, texture(outTexture1, outTexCoord).r);
}