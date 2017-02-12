#version 330 core
in vec3 outColour;
in vec2 outTexCoord;

out vec4 colour;

//Texture samplers
uniform sampler2D outTexture1;

void main(){
	colour = texture(outTexture1, outTexCoord);
}