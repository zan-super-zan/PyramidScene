#pragma once
#include "glad/glad.h"

#include "utility/Vertex.h"
#include "Log.h"

#include <vector>

class VertexArray
{

public:
	VertexArray() = default;
	VertexArray(std::size_t vertexCount);

	std::size_t GetSize()const { return m_Vertices.size(); }
	const Vertex* Data()const { return m_Vertices.data(); }
	const uint32_t GetVAO()const { return m_Object; }

	void Append(const Vertex& vertex);
	void Clear();

	void Generate();
	void Bind()const;
	void Unbind();
	void Delete();

public:
	Vertex& operator[](std::size_t index);
	const Vertex& operator[](std::size_t index)const;
private:
	std::vector<Vertex> m_Vertices;
	uint32_t m_Object;
};

