#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aVertexColor;

out vec2 TexCoords;
out vec3 InterpolatedColor;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
//	gl_Position = vec4(aPos, 1.0);
	TexCoords = aTexCoords;
	InterpolatedColor = aVertexColor;
}