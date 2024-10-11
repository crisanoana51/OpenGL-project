#version 410 core

out vec4 fColor;

uniform sampler2D diffuseTexture;

in vec2 fTexCoords;

void main() 
{    
	vec4 colorFromTexture = texture(diffuseTexture, fTexCoords);
	if(colorFromTexture.a < 0.1)
		discard;
		
	fColor = colorFromTexture;
}
