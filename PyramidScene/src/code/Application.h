#pragma once
#include "Window.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "PerspectiveCamera.h"
#include "ImGuiLayer.h"
#include "VertexArray.h"
#include "Object.h"
#include "Renderer.h"

class Application
{
public:
public:
	Application();
	void Run();

private:
	void _Init();
	void _Update(float delatTime);
	void _Render();
	void _Shutdown();
	void _ImGuiWidget();
	void _ImGuiShowColorSettings();
	void _ImGuiShowRenderFrameOption()const;
	void _ImGuiShowAutomaticRotationOption(bool& rotationOnYAxisEnabled);
	void _ImGuiShowScalingSettings();
	void _ImGuiShowRotationSettings(bool isObjectRotating);
	void _ImGuiShowRotationSettingsEnabled(int32_t& x, int32_t& y, int32_t& z);
	void _ImGuiShowRotationSettingsDisabled(int32_t& x, int32_t& y, int32_t& z);
private:
	PerspectiveCamera* m_Camera;
	Shader m_Shader;
	Window* m_Window;
	Renderer* m_Renderer;
	Texture2D* m_Texture;
	Object* m_PiramidObject;

	bool m_ApplyTexture;
	bool m_InterpolatedColor;
	
	glm::vec3 m_ObjectColor{ 1.0f };
	glm::vec3 m_ClearColor{ 0.2f, 0.2f, 0.2f };
	glm::vec3 m_ObjectScale{ 1.0f };

	glm::vec3 m_Rotation;
	float m_LinearScaleValue;
	bool m_LinearScale;
};
