#version 330 core
in vec3 outColour;
in vec2 outTexCoord;

out vec4 colour;

//Texture samplers
uniform sampler2D outTexture1;

void main(){

	//colour = texture(outTexture1, outTexCoord) * vec4(outColour, 1.0f);
	colour = texture(outTexture1, outTexCoord);
	//colour = vec4(outTexCoord.x, 0, outTexCoord.y, 1.0f);
}