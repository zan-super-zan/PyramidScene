#include "Application.h"
#include <iostream>

Application::Application()
	: m_ApplyTexture(false), m_InterpolatedColor(false), m_Rotation(glm::vec3(0.0f)), m_PiramidObject(nullptr), m_LinearScale(false), m_LinearScaleValue(1.0f)
{
	m_Window = new Window(1.6f, Window::AspectRatio::RATIO16_10, "Piramid Scene");
	m_Window->SetCallback(Callback::KEY_PRESS);
	m_Window->SetCallback(Callback::FRAMEBUFFER_SIZE);
	m_Window->SetCallback(Callback::CURSOR_POSITION);
	m_Window->SetCallback(Callback::MOUSE_BUTTON);

	m_Shader = ResourceManager::LoadShader("src/shaders/TextureShader.vert", "src/shaders/TextureShader.frag").Use();
	
	m_Camera = new PerspectiveCamera(60.0f, (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f, 100.0f);
	m_Texture = new Texture2D();
	*m_Texture = ResourceManager::LoadTexture("assets/RedWood.jpg");
	m_Texture->SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

	m_Renderer = new Renderer(m_Shader);

	ImGuiLayer::Init(m_Window->GLFWwindowInstance());
	m_Camera->ProcessInput(m_Window->GLFWwindowInstance(), 1.0f);
}


void Application::Run()
{
	_Init();

	float lastFrame = 0.0f;
	float deltaTime = 0.0f;
	while (!m_Window->ShouldClose())
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Window->Clear(m_ClearColor);
		m_Window->Begin();
		_Update(deltaTime);
		_Render();
		m_Window->End();
	}
	_Shutdown();
}

void Application::_Init()
{
	VertexArray piramidVertices(18);
	// front face
	piramidVertices[0] = Vertex({ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
	piramidVertices[1] = Vertex({ 0.0f,  0.5f, 0.5f }, { 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	piramidVertices[2] = Vertex({ 0.5f, -0.5f, 0.0f }, { 0.5f, 1.0f }, { 0.0f, 0.0f, 1.0f });
	// right face 	 	 	 										   
	piramidVertices[3] = Vertex({ 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	piramidVertices[4] = Vertex({ 0.0f,  0.5f, 0.5f }, { 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f });
	piramidVertices[5] = Vertex({ 0.5f, -0.5f, 1.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
	// left face 		 										   
	piramidVertices[6] = Vertex({ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
	piramidVertices[7] = Vertex({ 0.0f,  0.5f, 0.5f }, { 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f });
	piramidVertices[8] = Vertex({ -0.5f, -0.5f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	// back face 													   
	piramidVertices[9] = Vertex({ -0.5f, -0.5f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	piramidVertices[10] = Vertex({ 0.0f,  0.5f, 0.5f }, { 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f });
	piramidVertices[11] = Vertex({ 0.5f, -0.5f, 1.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
	// bottom sqare
	piramidVertices[12] = Vertex({ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
	piramidVertices[13] = Vertex({ -0.5f, -0.5f, 1.0f }, { 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f });
	piramidVertices[14] = Vertex({ 0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });

	piramidVertices[15] = Vertex({ 0.5f, -0.5f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
	piramidVertices[16] = Vertex({ -0.5f, -0.5f, 1.0f }, { 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f });
	piramidVertices[17] = Vertex({ 0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });

	m_PiramidObject = new Object(piramidVertices);
	m_PiramidObject->SetRotationAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	m_PiramidObject->SetScale(glm::vec3(2.0f, 2.0f, 1.0f));
}

void Application::_Update(float deltaTime)
{
	ImGuiLayer::Begin();

	if (Window::MouseButtonPressed(Window::MouseButton::RIGHT))
		m_Camera->ProcessInput(m_Window->GLFWwindowInstance(), deltaTime);

	m_Shader.SetMatrix4("u_Projection", m_Camera->GetProjectionMatrix());
	m_Shader.SetMatrix4("u_View", m_Camera->GetViewMatrix());
	m_Shader.SetVector3f("u_Color", m_ObjectColor);
	m_Shader.SetInteger("u_ApplyTexture", m_ApplyTexture);
	m_Shader.SetInteger("u_UseInterpolatedColors", m_InterpolatedColor);

	m_PiramidObject->SetRotation(m_Rotation);

	if (m_LinearScale)
		m_PiramidObject->SetScale(m_LinearScaleValue);
	else
		m_PiramidObject->SetScale(m_ObjectScale);
}

void Application::_Render()
{
	m_Renderer->Draw(*m_PiramidObject);
	_ImGuiWidget();
	ImGuiLayer::End();
}

void Application::_Shutdown()
{
	m_Shader.Shutdown();
	m_Window->Shutdown();
	ImGuiLayer::Shutdown();
	m_Texture->Delete();
	ResourceManager::Shutdown();
	delete m_Window, m_Camera, m_Shader, m_Renderer, m_Texture, m_PiramidObject;
}

void Application::_ImGuiWidget()
{
	ImGui::Begin("Settings");

	_ImGuiShowColorSettings();
	_ImGuiShowRenderFrameOption();
	static bool rotationOnYAxisEnabled = false;
	_ImGuiShowAutomaticRotationOption(rotationOnYAxisEnabled);
	_ImGuiShowScalingSettings();
	_ImGuiShowRotationSettings(rotationOnYAxisEnabled);

	ImGui::End();
}

void Application::_ImGuiShowColorSettings()	 
{
	static bool animateColors = false, applyTexture = false;

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::ColorEdit3("Object Color", &m_ObjectColor.x);

	static glm::vec3 color = glm::vec3(m_ClearColor);
	ImGui::ColorEdit3("Screen Clear Color", &color.r);
	m_ClearColor = color;

	ImGui::Checkbox("Animate Colors", &animateColors);
	if (animateColors)
	{
		float time = glfwGetTime();
		m_ObjectColor.r = sin(time);
		m_ObjectColor.g = cos(time / 2.0f);

		if (m_ObjectColor.r < 0.0f)
			m_ObjectColor.r *= -1.0f;

		if (m_ObjectColor.g < 0.0f)
			m_ObjectColor.g *= -1.0f;
	}

	static bool useInterpolatedColors = false;
	ImGui::Checkbox("Use Interpolated Colors", &useInterpolatedColors);
	m_InterpolatedColor = useInterpolatedColors;

	ImGui::Checkbox("Apply Texture", &applyTexture);
	m_ApplyTexture = applyTexture;
}

void Application::_ImGuiShowRenderFrameOption() const
{
	static bool renderInLineMode = false;
	ImGui::Checkbox("Render in Line Mode", &renderInLineMode);
	renderInLineMode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void Application::_ImGuiShowAutomaticRotationOption(bool& rotationOnYAxisEnabled)
{
	ImGui::Checkbox("Auto Rotation Y Axis", &rotationOnYAxisEnabled);
	static float lastFrame = 0.0f;
	if (rotationOnYAxisEnabled)
	{
		float currentFrame = (float)glfwGetTime();
		float deltaTime = currentFrame - lastFrame;

		m_Rotation.y += deltaTime * 40.0f;
		lastFrame = currentFrame;
	}
	else
		lastFrame = glfwGetTime();
}
void Application::_ImGuiShowScalingSettings()
{
	if (ImGui::CollapsingHeader("Scale Settings"))
	{
		static bool linearScale = true;
		static constexpr float minScale = 0.0f;
		static constexpr float maxScale = 3.0f;

		ImGui::Checkbox("Enable Linear Scale", &linearScale);
		m_LinearScale = linearScale;
		if (!m_LinearScale)
		{
			ImGui::SliderFloat("Width", &m_ObjectScale.x, minScale, maxScale);
			ImGui::SliderFloat("Height", &m_ObjectScale.y, minScale, maxScale);
			ImGui::SliderFloat("Length", &m_ObjectScale.z, minScale, maxScale);
		}
		else
			ImGui::SliderFloat("Length", &m_LinearScaleValue, 1.0f, 3.0f);
	}
}
void Application::_ImGuiShowRotationSettings(bool isObjectRotating)
{
	static int x = 0, y = 0, z = 0;
	if (ImGui::CollapsingHeader("Rotation Settings"))
		!isObjectRotating ?_ImGuiShowRotationSettingsEnabled(x, y, z) : _ImGuiShowRotationSettingsDisabled(x, y, z);
}
void Application::_ImGuiShowRotationSettingsEnabled(int32_t& x, int32_t& y, int32_t& z)
{
	static constexpr int16_t minAngle = 0;
	static constexpr int16_t maxAngle = 360;

	if (ImGui::SliderInt("X Axis", &x, minAngle, maxAngle))
		m_PiramidObject->SetRotationAxis(glm::vec3(1, y != 0, z != 0));
	else if (ImGui::SliderInt("Y Axis", &y, minAngle, maxAngle))
		m_PiramidObject->SetRotationAxis(glm::vec3(x != 0, 1, z != 0));
	else if (ImGui::SliderInt("Z Axis", &z, minAngle, maxAngle))
		m_PiramidObject->SetRotationAxis(glm::vec3(x != 0, y != 1, 1));

	m_Rotation.x = (float)x;
	m_Rotation.y = (float)y;
	m_Rotation.z = (float)z;
}

void Application::_ImGuiShowRotationSettingsDisabled(int32_t& x, int32_t& y, int32_t& z)
{
	int disposable[3] = { x, y, z };
	static int16_t minAngle = 0;
	static int16_t maxAngle = 360;

	if (ImGui::SliderInt("X Axis", &disposable[0], minAngle, maxAngle) ||
		ImGui::SliderInt("Y Axis", &disposable[1], minAngle, maxAngle) ||
		ImGui::SliderInt("Z Axis", &disposable[2], minAngle, maxAngle))
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("Automatic rotation must be disabled!");
		ImGui::PopStyleColor();
	}
}




