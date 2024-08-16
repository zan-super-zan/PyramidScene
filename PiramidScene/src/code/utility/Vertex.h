#pragma once

#include "glm/glm.hpp"

struct Vertex
{
	Vertex() = default;

	Vertex(const glm::vec3& position) : Position(position), TexCoords({ 0.0f })
	{}
	Vertex(const glm::vec3& position, const glm::vec2& texCoords)
		: Position(position), TexCoords(texCoords)
	{ }
	Vertex(const glm::vec3& position, const glm::vec2& texCoords, const glm::vec3& normal)
		: Position(position), TexCoords(texCoords), Normal(normal)
	{ }
public:
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};