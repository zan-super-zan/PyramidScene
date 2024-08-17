#pragma once
#include "glad/glad.h"
#include <cstdint>

struct TextureSpecification
{
	uint32_t WrapS, WrapT;
	uint32_t InternalFormat, ImageFormat;
	uint32_t FilterMin, FilterMax;

	TextureSpecification(uint32_t wraps, uint32_t wrapt, uint32_t internalFormat, uint32_t imageFormat, uint32_t filterMin, uint32_t filterMax);
	TextureSpecification();
};


class Texture2D
{
public:
	Texture2D(const TextureSpecification& textureSpec);
	Texture2D();

	const TextureSpecification& GetTextureSpecification()const { return m_TextureSpec; }
	uint32_t GetWidth()const { return m_Width; }
	uint32_t GetHeight()const { return m_Height; }
	
	void SetWraping(uint32_t wraps, uint32_t wrapt);
	void SetFormats(uint32_t internalFormat, uint32_t imageFormat);
	void SetFilter(uint32_t filterMin, uint32_t filterMax);

	void Generate(uint32_t width, uint32_t height, uint8_t* data);
	void Bind();
	void Delete();

private:
	uint32_t m_Id;
	uint32_t m_Width, m_Height;
	TextureSpecification m_TextureSpec;
};

