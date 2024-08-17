#include "ResourceManager.h"

#include "stb_image/stb_image.h"

#include <string>
#include <fstream>
#include <sstream>

ResourceManager* ResourceManager::s_ResourceManager;

Shader ResourceManager::LoadShader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath)
{
	return _GetInstance()->_LoadShaderImpl(vertexShaderFilepath, fragmentShaderFilepath);
}

Texture2D ResourceManager::LoadTexture(const char* filepath)
{
	return _GetInstance()->_LoadTextureImpl(filepath);
}

void ResourceManager::Shutdown()
{
	delete _GetInstance();
}

ResourceManager* ResourceManager::_GetInstance()
{
	if (s_ResourceManager == nullptr)
		s_ResourceManager = new ResourceManager();
	return s_ResourceManager;
}

Shader ResourceManager::_LoadShaderImpl(const char* vertexShaderFilepath, const char* fragmentShaderFilepath)
{
	std::string vertexShaderCode, fragmentShaderCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	std::stringstream vs, fs;

	vertexShaderFile.open(vertexShaderFilepath);
	fragmentShaderFile.open(fragmentShaderFilepath);

	if (!vertexShaderFile.is_open() || !fragmentShaderFile.is_open())
		LOG_ERROR("ERROR::FILE_STREAM::Failed to open shader source file");

	vs << vertexShaderFile.rdbuf();
	fs << fragmentShaderFile.rdbuf();

	if (!(vs || fs))
		LOG_ERROR("ERROR::FILE_STREAM::Failed to read file buffer");

	vertexShaderCode = vs.str();
	fragmentShaderCode = fs.str();

	Shader shader;
	shader.Compile(vertexShaderCode.c_str(), fragmentShaderCode.c_str());
	return shader;
}

Texture2D ResourceManager::_LoadTextureImpl(const char* filepath)
{
	Texture2D texture;

	int32_t width, height, nrChannels;

	uint8_t* data = stbi_load(filepath, &width, &height, &nrChannels, 0);

	if (!data)
		LOG_ERROR("ERROR::STB_IMAGE::Failed to load image");

	if (nrChannels == 3)
		texture.SetFormats(GL_RGB, GL_RGB);
	else if (nrChannels == 4)
		texture.SetFormats(GL_RGBA, GL_RGBA);
	else
		LOG_ERROR("ERROR::TEXTURE::Wierd number of channels");

	//std::cout << (texture.GetTextureSpecification().InternalFormat == GL_RGB ? "rgb" : "rgba") << std::endl;
	//std::cout << nrChannels << std::endl;
	texture.Generate(width, height, data);
	stbi_image_free(data);
	return texture;
}


