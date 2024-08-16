#include "Texture2D.h"
#include <iostream>

TextureSpecification::TextureSpecification(uint32_t wraps, uint32_t wrapt, uint32_t internalFormat, uint32_t imageFormat, uint32_t filterMin, uint32_t filterMax)
	: WrapS(wraps), WrapT(wrapt), InternalFormat(internalFormat), ImageFormat(imageFormat), FilterMin(filterMin), FilterMax(filterMax)
{
}

TextureSpecification::TextureSpecification()
	: TextureSpecification(GL_REPEAT, GL_REPEAT, GL_RGB, GL_RGB, GL_LINEAR, GL_LINEAR)
{
}

void Texture2D::SetWraping(uint32_t wraps, uint32_t wrapt)
{
	m_TextureSpec.WrapS = wraps;
	m_TextureSpec.WrapT = wrapt;
}

void Texture2D::SetFormats(uint32_t internalFormat, uint32_t imageFormat)
{
	m_TextureSpec.InternalFormat = internalFormat;
	m_TextureSpec.ImageFormat = imageFormat;
}

void Texture2D::SetFilter(uint32_t filterMin, uint32_t filterMax)
{
	m_TextureSpec.FilterMin = filterMin;
	m_TextureSpec.FilterMax = filterMax;
}

Texture2D::Texture2D(const TextureSpecification& textureSpec)
	: m_Width(0), m_Height(0), m_TextureSpec(textureSpec)
{
	glGenTextures(1, &m_Id);
}

Texture2D::Texture2D() : Texture2D(TextureSpecification())
{
}


void Texture2D::Generate(uint32_t width, uint32_t height, uint8_t* data)
{
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexImage2D(GL_TEXTURE_2D, 0, m_TextureSpec.InternalFormat, width, height, 0, m_TextureSpec.ImageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TextureSpec.WrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TextureSpec.WrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TextureSpec.FilterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TextureSpec.FilterMax);
}

void Texture2D::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture2D::Delete()
{
	glDeleteTextures(1, &m_Id);
}
