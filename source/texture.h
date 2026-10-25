#pragma once

#include "utility.h"



class Texture
{

public:

	Texture(const char* source);

	bool Load();

	void Use();

private:

	uint32_t _textureID{ 0 };

	int _width{0};
	int _height{0};
	int _bitDepth{0};

	const char* _source;
};

struct BlockTexture 
{
	std::unique_ptr<Texture> top{nullptr};
	std::unique_ptr<Texture> bottom{nullptr};
	std::unique_ptr<Texture> side{nullptr};
};
