#pragma once

#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexArray.h"

// Reperesents a generic object
class Object
{
public:
	Object(VertexArray& va, const glm::vec3& rotation, const glm::vec3& rotationAxis, const glm::vec3& scale);
	Object(VertexArray& va, const glm::vec3& rotation, const glm::vec3& rotationAxis);
	Object(VertexArray& va, const glm::vec3& rotation);
	Object(VertexArray& va);
	~Object();

	const uint32_t GetVAO()const { return m_VertexArray.GetVAO(); }
	VertexArray& GetVertexArray() { return m_VertexArray; }
	const VertexArray& GetVertexArray()const { return m_VertexArray; }
	const glm::vec3& GetScale()const { return m_Scale; }
	const glm::vec3& GetRotation()const { return m_RotationPerAxis; }
	const glm::vec3& GetRotationAxis()const { return m_RotationAxis; }

	void SetRotation(const glm::vec3& rotation) { m_RotationPerAxis = rotation; }
	void SetRotationAxis(const glm::vec3& axis) { m_RotationAxis = axis; }
	void SetScale(const glm::vec3& scale) { m_Scale = scale; }
	void SetScale(float scale) { m_Scale = glm::vec3(scale); }

private:
	VertexArray m_VertexArray;
	VertexBuffer m_VertexBuffer;

	glm::vec3  m_RotationPerAxis;
	glm::vec3 m_RotationAxis;
	glm::vec3 m_Scale;
};

