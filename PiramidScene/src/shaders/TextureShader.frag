#version 330 core

uniform sampler2D u_Image;
out vec4 FragColor;

in vec2 TexCoords;
in vec3 InterpolatedColor;

uniform vec3 u_Color;
uniform bool u_ApplyTexture;
uniform bool u_UseInterpolatedColors;

vec3 Color;

void main()
{
	if(u_UseInterpolatedColors)
		Color = InterpolatedColor;
	else
		Color = u_Color;

	if(u_ApplyTexture)
		FragColor = vec4(Color, 1.0) * texture(u_Image, TexCoords);
	else
		FragColor = vec4(Color, 1.0);

//FragColor =  vec4(InterpolatedColor, 1.0);
//	FragColor = vec4(TexCoords, 0.0, 1.0);
}
