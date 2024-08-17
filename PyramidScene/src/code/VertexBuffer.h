#pragma once
#include "glad/glad.h"

#include "utility/Vertex.h"
#include "Log.h"

class VertexBuffer
{
public:
	enum class DrawMode
	{
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW,
		STREAM = GL_STREAM_DRAW
	};
public:
	VertexBuffer(DrawMode drawMode);

	uint32_t NumberOfVertices()const { return m_NrVertices; }
	GLenum GetDrawMode()const { return (GLenum)m_DrawMode; }
	
	void Generate(uint32_t nrVertices);
	void Bind()const;
	void Unbind();
	void Delete();
private:
	uint32_t m_Buffer;
	uint32_t m_NrVertices;
	DrawMode m_DrawMode;
};

