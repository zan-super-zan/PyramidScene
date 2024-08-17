#include "Shader.h"

#include <string>
#include <sstream>

Shader::Shader()
	: m_Id(0)
{
}

Shader& Shader::Use() 
{
	glUseProgram(m_Id);
	return *this;
}

void Shader::Shutdown()
{
	glDeleteProgram(m_Id);
}

void Shader::SetFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_Id, name), value);
}

void Shader::SetInteger(const char* name, int32_t value)
{
	glUniform1i(glGetUniformLocation(m_Id, name), value);
}

void Shader::SetVector2f(const char* name, float x, float y)
{
	glUniform2f(glGetUniformLocation(m_Id, name), x, y);
}

void Shader::SetVector2f(const char* name, glm::vec2 value)
{
	SetVector2f(name, value.x, value.y);
}

void Shader::SetVector3f(const char* name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(m_Id, name), x, y, z);
}

void Shader::SetVector3f(const char* name, const glm::vec3& value)
{
	SetVector3f(name, value.x, value.y, value.z);
}

void Shader::SetVector4f(const char* name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(m_Id, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, const glm::vec4& value)
{
	SetVector4f(name, value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, false, glm::value_ptr(matrix));
}

void Shader::Compile(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	_CheckForCompilationErrors(vertexShader, ShaderType::VERTEX);

	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	_CheckForCompilationErrors(fragmentShader, ShaderType::FRAGMENT);

	m_Id = glCreateProgram();
	glAttachShader(m_Id, vertexShader);
	glAttachShader(m_Id, fragmentShader);
	glLinkProgram(m_Id);
	_CheckForCompilationErrors(m_Id, ShaderType::SHADER_PROGRAM);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::_CheckForCompilationErrors(uint32_t object, const ShaderType shaderType)
{
	int32_t success;
	char infoLog[1024];

	if (shaderType != ShaderType::SHADER_PROGRAM)
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (success)
			return;

		glGetShaderInfoLog(object, 1024, nullptr, infoLog);
		std::stringstream ss;
		ss << "ERROR::SHADER::COMPILE_TIME::" << (shaderType == ShaderType::VERTEX ? "VERTEX\nInfo Log: " : "FRAGMENT\nInfo Log: ") << infoLog;
		LOG_ERROR(ss.str());
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (success)
			return;

		glGetProgramInfoLog(object, 1024, nullptr, infoLog);
		std::stringstream ss;
		ss << "ERROR::PROGRAM::LINK_TIME::" << infoLog;
		LOG_ERROR(ss.str());
	}
}
