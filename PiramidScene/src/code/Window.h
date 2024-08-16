#pragma once
#include "Log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

enum class Callback
{
	FRAMEBUFFER_SIZE,
	KEY_PRESS,
	CURSOR_POSITION,
	MOUSE_BUTTON
};
class Window
{
public:
	enum class AspectRatio
	{
		RATIO16_10,
		RATIO16_9,
		RATIO4_3
	};
	enum class MouseButton
	{
		LEFT = GLFW_MOUSE_BUTTON_LEFT,
		RIGHT = GLFW_MOUSE_BUTTON_RIGHT
	};
public:
	Window(const float scale, const AspectRatio aspectRatio, const char* title);

	bool ShouldClose()const { return glfwWindowShouldClose(m_Window); }

	uint32_t GetWidth()const { return m_Width; }
	uint32_t GetHeight()const { return m_Height; }

	GLFWwindow* GLFWwindowInstance() const { return m_Window; }

	static glm::vec2 GetCursorPosition() { return s_CursorPos; }
	static bool IsKeyPressed(uint32_t key) { return s_Keys[key]; }

	static bool MouseButtonPressed(const MouseButton button) { return s_MouseButtonPressed[(std::size_t)button]; }

	void SetCallback(Callback callback);
	void Begin();
	void End();
	void Clear(const glm::vec3& color)const;
	void Shutdown();
private:
	void _Init(const char* title);
	void _InitGLFW();
	void _CreateWindow(const char* title);
	void _InitGLAD();

	void _SetAspectRatio(const AspectRatio aspectRatio, int32_t screenWidth, int32_t screenHeight);

	static void _FrameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	static void _KeyPressCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
	static void _CursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
	static void _MouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);
private:
	GLFWwindow* m_Window;
	float m_Scale;
	uint32_t m_Width, m_Height;
	AspectRatio m_AspectRatio;

	static bool s_Keys[1024];
	static glm::vec2 s_CursorPos;

	static bool s_MouseButtonPressed[2];
};

