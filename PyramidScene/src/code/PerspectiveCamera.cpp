#include "PerspectiveCamera.h"
 
float PerspectiveCamera::s_Yaw = 90.0f;
float PerspectiveCamera::s_Pitch = 0.0f;

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane)
	: m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f, 0.0f, 3.0f)), m_Speed(2.5f)
{
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Right = glm::normalize(glm::cross(m_Orientation, m_Up));

	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void PerspectiveCamera::ProcessInput(GLFWwindow* window, float deltaTime)
{
	float velocity = m_Speed * deltaTime;

	if (Window::IsKeyPressed(GLFW_KEY_W))
		m_Position += m_Orientation * velocity;
	else if (Window::IsKeyPressed(GLFW_KEY_S))
		m_Position -= m_Orientation * velocity;
	if (Window::IsKeyPressed(GLFW_KEY_A))
		m_Position -= m_Right * velocity;
	else if (Window::IsKeyPressed(GLFW_KEY_D))
		m_Position += m_Right * velocity;
	if (Window::IsKeyPressed(GLFW_KEY_SPACE))
		m_Position += m_Up * velocity;
	else if (Window::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		m_Position -= m_Up * velocity;

	_UpdateVectors();
	_RecalculateViewMatrix();
}

void PerspectiveCamera::ProcessMouseInput(float xOffset, float yOffset)
{
	s_Yaw += xOffset;
	s_Pitch += yOffset;

	if (s_Pitch > 89.0f)
		s_Pitch = 89.0f;
	else if (s_Pitch < -89.0f)
		s_Pitch = -89.0f;
}

void PerspectiveCamera::_RecalculateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}

void PerspectiveCamera::_UpdateVectors()
{
	glm::vec3 front{0.0f};
	front.x = cos(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));
	front.y = sin(glm::radians(s_Pitch));
	front.z = sin(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));
	m_Orientation = glm::normalize(-front);

	m_Right = glm::normalize(glm::cross(m_Orientation, m_Up));
	//m_Up = glm::normalize(glm::cross(m_Right, m_Orientation)); // causes roll type of movement which is not expected behaviour
}
