#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Log.h"


class Shader
{
private:
	enum class ShaderType { SHADER_PROGRAM, VERTEX, FRAGMENT };
public:
	Shader();

	Shader& Use();
	void Shutdown();
	uint32_t ShaderId()const { return m_Id; }

	void SetFloat(const char* name, float value);
	void SetInteger(const char* name, int32_t value);
	void SetVector2f(const char* name, float x, float y);
	void SetVector2f(const char* name, glm::vec2 value);
	void SetVector3f(const char* name, float x, float y, float z);
	void SetVector3f(const char* name, const glm::vec3& value);
	void SetVector4f(const char* name, float x, float y, float z, float w);
	void SetVector4f(const char* name, const glm::vec4& value);
	void SetMatrix4(const char* name, const glm::mat4& matrix);

	void Compile(const char* vertexShaderSource, const char* fragmentShaderSource);
private:
	void _CheckForCompilationErrors(uint32_t object, const ShaderType shaderType);
private:
	uint32_t m_Id;

};

