#version 330 core
in vec2 outTexCoord;

out vec4 colour;

//Texture samplers
uniform sampler2D outTexture1;

void main(){
	colour = vec4(1,1,1,1);//vec4(1, 1, 1, texture(outTexture1, outTexCoord).r);
}