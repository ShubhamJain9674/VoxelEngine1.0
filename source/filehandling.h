#pragma once


#include <iostream>
#include <string>



namespace FileManager
{
	std::string GetExecutablePath();

	bool ReadShaderFile(const char* source, std::string& content);

	unsigned char* LoadTexture(const char* source,
						int* width, int* height,
						int* bitDepth, int desiredNoOfChannels);

	void FreeTexture(unsigned char* data);
}