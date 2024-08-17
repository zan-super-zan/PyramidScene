#include "Renderer.h"
#include <array>

Renderer::Renderer(const Shader& shader)
	: m_Shader(shader)
{
}

void Renderer::Draw(Object& obj)
{
	static glm::vec3 objectCenterPosition = glm::vec3(0.0f, 0.0f, 0.5f);
	glm::vec3 rotationAxis = obj.GetRotationAxis();
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, objectCenterPosition);

	if(rotationAxis.x == 1)
		model = glm::rotate(model, glm::radians(obj.GetRotation().x), glm::vec3(obj.GetRotationAxis().x, 0, 0));
	if(rotationAxis.y == 1)
		model = glm::rotate(model, glm::radians(obj.GetRotation().y), glm::vec3(0, obj.GetRotationAxis().y, 0));
	if(rotationAxis.z == 1)
		model = glm::rotate(model, glm::radians(obj.GetRotation().z), glm::vec3(0, 0, obj.GetRotationAxis().z));

	model = glm::translate(model, -objectCenterPosition);

	model = glm::scale(model, obj.GetScale());
	
	m_Shader.SetMatrix4("u_Model", model);

	m_Shader.Use();
	obj.GetVertexArray().Bind();
	glDrawArrays(GL_TRIANGLES, 0, obj.GetVertexArray().GetSize());
	obj.GetVertexArray().Unbind();
}

