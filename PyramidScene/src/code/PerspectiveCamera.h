#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"


class PerspectiveCamera
{
public:
	PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane);

	void SetMovementSpeed(float value) { m_Speed = value; }

	const glm::mat4& GetViewMatrix()const { return m_ViewMatrix; }
	const glm::mat4& GetProjectionMatrix()const { return m_ProjectionMatrix; }

	void ProcessInput(GLFWwindow* window, float deltaTime);
	static void ProcessMouseInput(float xOffset, float yOffset);
private:
	void _UpdateVectors();
	void _RecalculateViewMatrix();
private:
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	// camera directions definitions
	glm::vec3 m_Right;       // vector is perpindicular to the up directio and orientation
	glm::vec3 m_Orientation; // forward/backward
	glm::vec3 m_Up;			 // up/down

	glm::vec3 m_Position;

	float m_Speed;
	// Mouse movement directions
	static float s_Pitch;
	static float s_Yaw;
};

