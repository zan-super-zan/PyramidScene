#include "VertexArray.h"

VertexArray::VertexArray(std::size_t vertexCount)
	: m_Vertices(vertexCount), m_Object(0)
{
}


void VertexArray::Append(const Vertex& vertex)
{
	m_Vertices.push_back(vertex);
}

void VertexArray::Clear()
{
	m_Vertices.clear();
}

void VertexArray::Generate()
{
	glGenVertexArrays(1, &m_Object);
	if (!m_Object)
		LOG_ERROR("ERROR::VERTEX_ARRAY::Failed to generate vertex array object");
}

void VertexArray::Bind()const
{
	glBindVertexArray(m_Object);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &m_Object);
}

Vertex& VertexArray::operator[](std::size_t index)
{
    if (index >= m_Vertices.size() || index < 0)
        LOG_ERROR("ERROR::VERTEX_ARRAY::Index out of bounds");
    return m_Vertices[index];
}

const Vertex& VertexArray::operator[](std::size_t index) const
{
	if (index >= m_Vertices.size() || index < 0)
		LOG_ERROR("ERROR::VERTEX_ARRAY::Index out of bounds");
	return m_Vertices[index];
}
