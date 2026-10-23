#pragma once


#include <iostream>
#include <string>


namespace FileManager
{
	std::string GetExecutablePath();

	bool ReadShaderFile(const char* source, std::string& content);
}