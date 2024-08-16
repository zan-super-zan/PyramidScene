#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(DrawMode drawMode)
	: m_DrawMode(drawMode), m_NrVertices(0), m_Buffer(0)
{
}

void VertexBuffer::Generate(uint32_t nrVertices)
{
	glGenBuffers(1, &m_Buffer);
	if (!m_Buffer)
		LOG_ERROR("ERROR::VERTEX_BUFFER::Failed to generate vertex buffer");
	m_NrVertices = nrVertices;
}

void VertexBuffer::Bind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete()
{
	glDeleteBuffers(1, &m_Buffer);
}
