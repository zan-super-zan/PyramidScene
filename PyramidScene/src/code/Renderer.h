#pragma once
#include "glad/glad.h"

#include "Shader.h"
#include "utility/Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Object.h"

class Renderer
{
public:
	Renderer(const Shader& shader);
	void SetShader(const Shader& shader) { m_Shader = shader; }

	void Draw(Object& obj);

private:
	Shader m_Shader;
};

