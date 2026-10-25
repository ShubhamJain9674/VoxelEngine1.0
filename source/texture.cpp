#include "texture.h"
#include "filehandling.h"



Texture::Texture(const char* source)
	:_source(source)
{
}

bool Texture::Load()
{
	unsigned char* texData = FileManager::LoadTexture(_source,&_width, &_height,
							&_bitDepth,4);

	if (!texData) 
	{
		return false;
	}

	GLCall(glGenTextures(1, &_textureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, _textureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height,
						0, GL_RGBA, GL_UNSIGNED_BYTE, texData));

	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	FileManager::FreeTexture(texData);
	return true;
}

void Texture::Use()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, _textureID));
}
