#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "Log.h"

class ResourceManager
{
public:
	static Shader LoadShader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);
	static Texture2D LoadTexture(const char* filepath);
	static void Shutdown();
private:
	static ResourceManager* _GetInstance();

	Shader _LoadShaderImpl(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);
	Texture2D _LoadTextureImpl(const char* filepath);
private:
	ResourceManager() = default;
	ResourceManager(ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;
private:
	static ResourceManager* s_ResourceManager;
};

