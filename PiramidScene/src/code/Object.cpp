#include "Object.h"

Object::Object(VertexArray& va, const glm::vec3& rotation, const glm::vec3& rotationAxis, const glm::vec3& scale)
	: m_VertexArray(va), m_RotationPerAxis(rotation), m_RotationAxis(rotationAxis), m_Scale(scale), m_VertexBuffer(VertexBuffer::DrawMode::STATIC)
{

	m_VertexBuffer.Generate(va.GetSize());
	m_VertexArray.Generate();
	
	m_VertexBuffer.Bind();
	m_VertexArray.Bind();

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * va.GetSize(), va.Data(), m_VertexBuffer.GetDrawMode());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);

	m_VertexBuffer.Unbind();
	m_VertexArray.Unbind();
}

Object::Object(VertexArray& va, const glm::vec3& rotation, const glm::vec3& rotationAxis)
	: Object(va, rotation, rotationAxis, glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Object::Object(VertexArray& va, const glm::vec3& rotation)
	: Object(va, rotation, glm::vec3(0.0f, 1.0f, 0.0f))
{
}

Object::Object(VertexArray& va)
	: Object(va, glm::vec3(0.0f))
{

}

Object::~Object()
{
	m_VertexBuffer.Delete();
	m_VertexArray.Delete();
}

//void Object::Draw(Renderer* renderer)
//{
//	renderer->Draw(*this,0.0f, m_RotationAxis, glm::vec3(1.0f, 1.0f, 1.0f));
//}
