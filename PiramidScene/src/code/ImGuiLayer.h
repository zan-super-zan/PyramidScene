#pragma once
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class ImGuiLayer
{
public:
	static void Init(GLFWwindow* window);
	static void Begin();
	static void End();
	static void Shutdown();
private:
};

