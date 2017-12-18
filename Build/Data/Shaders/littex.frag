#version 330 core
out vec4 colour;

in vec2 outTexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColour;
uniform vec3 ambientColour;
uniform vec3 objectColour;

//Texture samplers
uniform sampler2D outTexture1;

void main()
{
	vec4 texColour = texture(outTexture1, outTexCoord);
    // Ambient
    float ambientStrength = 0.3f;
    vec3 ambient = ambientStrength * (ambientColour * objectColour);
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColour;  
	
	vec3 texNoAlpha = vec3(texColour.r, texColour.g, texColour.b);
        
    vec3 result = (ambient + diffuse + specular) * texNoAlpha;
	//colour = result;
	colour = vec4(result.r, result.g, result.b, 1.0f);
} 