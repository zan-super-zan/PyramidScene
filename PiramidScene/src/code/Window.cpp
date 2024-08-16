#include "Window.h"
#include "PerspectiveCamera.h"

bool Window::s_Keys[1024];
glm::vec2 Window::s_CursorPos;
bool Window::s_MouseButtonPressed[2];

Window::Window(const float scale, const AspectRatio aspectRatio, const char* title)
	: m_Scale(scale), m_AspectRatio(aspectRatio)
{
	_Init(title);
}


void Window::SetCallback(Callback callback)
{
	switch (callback)
	{
	case Callback::FRAMEBUFFER_SIZE:
		glfwSetFramebufferSizeCallback(m_Window, _FrameBufferSizeCallback);
		break;
	case Callback::KEY_PRESS:
		glfwSetKeyCallback(m_Window, _KeyPressCallback);
		break;
	case Callback::CURSOR_POSITION:
		glfwSetCursorPosCallback(m_Window, _CursorPositionCallback);
		break;
	case Callback::MOUSE_BUTTON:
		glfwSetMouseButtonCallback(m_Window, _MouseButtonCallback);
		break;
	default:
		LOG_ERROR("ERROR::INVALID_CALLBACK::Callback does not exist");
		break;
	}
}

void Window::Begin()
{
	glfwPollEvents();

	double xPos, yPos;
	glfwGetCursorPos(m_Window, &xPos, &yPos);
	
	s_CursorPos = glm::vec2(xPos, yPos);
}

void Window::End()
{
	glfwSwapBuffers(m_Window);

}

void Window::Clear(const glm::vec3& color) const
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Shutdown()
{
	glfwTerminate();
}

void Window::_Init(const char* title)
{
	_InitGLFW();
	_CreateWindow(title);
	_InitGLAD();
}

void Window::_InitGLFW()
{
	// OpenGL settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit())
		LOG_ERROR("ERROR::GLFW::Initalization failed");
}

void Window::_CreateWindow(const char* title)
{
	GLFWmonitor* mainMonitor = glfwGetPrimaryMonitor();
	if (!mainMonitor)
		LOG_ERROR("ERROR::GLFW::Failed to retrive monitor data");

	const GLFWvidmode* mode = glfwGetVideoMode(mainMonitor);
	int32_t screenWidth = mode->width;
	int32_t screenHeight = mode->height;

	_SetAspectRatio(m_AspectRatio, screenWidth, screenHeight);


	m_Window = glfwCreateWindow(m_Width, m_Height, title, nullptr, nullptr);
	if (!m_Window)
		LOG_ERROR("ERROR::GLFW::Failed to create window");
	glfwMakeContextCurrent(m_Window);
}

void Window::_InitGLAD()
{
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		LOG_ERROR("ERROR::GLAD::Failed to load OpenGL function pointers");

	glViewport(0, 0, m_Width, m_Height);
	glEnable(GL_DEPTH_TEST);
}

void Window::_SetAspectRatio(const AspectRatio aspectRatio, int32_t screenWidth, int32_t screenHeight)
{
	float ratioMajor = 0.0f, ratioMinor = 0.0f;
	switch (aspectRatio)
	{
	case AspectRatio::RATIO16_10:
		ratioMajor = 16.0f;
		ratioMinor = 10.0f;
		break;
	case AspectRatio::RATIO16_9:
		ratioMajor = 16.0f;
		ratioMinor = 9.0f;
		break;
	case AspectRatio::RATIO4_3:
		ratioMajor = 4.0f;
		ratioMinor = 3.0f;
		break;
	default:
		LOG_ERROR("ERROR::WINDOW::Invalid aspect ratio");
		break;
	}
	m_Width = screenHeight * ratioMajor / ratioMinor / m_Scale;
	m_Height = screenWidth * ratioMinor / ratioMajor / m_Scale;
}

void Window::_FrameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height)
{
	glViewport(0, 0, width, height);
}

void Window::_KeyPressCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			s_Keys[key] = true;
		else if (action == GLFW_RELEASE)
			s_Keys[key] = false;
	}
}

void Window::_CursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	static int32_t windowWidth = 0, windowHeight = 0;
	static bool firstMouse = true;
	if (firstMouse)
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

	static float lastX = windowWidth / 2.0f;
	static float lastY = windowHeight / 2.0f;

	if (firstMouse)
	{
		lastX = (float)xPos;
		lastY = (float)yPos;
		firstMouse = false;
	}

	float xOffset = (float)xPos - lastX;
	float yOffset = (float)yPos - lastY;

	lastX = (float)xPos;
	lastY = (float)yPos;

	static constexpr float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	PerspectiveCamera::ProcessMouseInput(xOffset, yOffset);
}

void Window::_MouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		s_MouseButtonPressed[GLFW_MOUSE_BUTTON_RIGHT] = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		s_MouseButtonPressed[GLFW_MOUSE_BUTTON_RIGHT] = false;
	}
}
