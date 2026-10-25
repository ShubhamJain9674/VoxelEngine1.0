#include "filehandling.h"

#include <fstream>
#include <filesystem>
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

namespace fs = std::filesystem;

std::string FileManager::GetExecutablePath() {

#ifdef _WIN32

    char buffer[MAX_PATH];
    DWORD len = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (len == 0) {
        throw std::runtime_error("Failed to get executable path (Windows)");
    }
    return std::string(buffer, len);

#elif __APPLE__

    std::cout << "who uses apple!" << std::endl;
    throw std::runtime_error("Unsupported platform");
#elif __linux__
    /*
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len == -1) {
        throw std::runtime_error("Failed to get executable path (Linux)");
    }

    buffer[len] = '\0';
    return fs::path(buffer);
    */

    std::cout << "Unsupported platform" << std::endl;
    throw std::runtime_error("Unsupported platform");

#else
#error Unsupported platform
    throw std::runtime_error("Unsupported platform");
#endif

}


bool FileManager::ReadShaderFile(const char* source, std::string& content)
{
    

    fs::path exePath = fs::absolute(GetExecutablePath()).parent_path();
    
    exePath = exePath / source;

    std::ifstream f(exePath);

    if (!f.is_open())
    {
        std::cout << "SHADER ERROR : Failed to open : "
                    << source << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(f, line))
    {
        content += (line + "\n");
    }
    
    return true;
}

/*
*loads a single texture file.
* Doesnt manage atlas because no time right now
* returns NULL if invalid.
*/
unsigned char* FileManager::LoadTexture(const char* source, int* width, int* height, int* bitDepth, int desiredNoOfChannels)
{
    fs::path filepath = fs::absolute(GetExecutablePath()).parent_path();
    filepath = filepath / source;


    const std::string pathString = filepath.string();


    unsigned char* texData = stbi_load(pathString.c_str(), width, height, bitDepth, desiredNoOfChannels);

    if (!texData)
    {
        std::cout << "Failed to find Texture file : "
                  << source  << std::endl;
    }

    return texData;
}


void FileManager::FreeTexture(unsigned char* source)
{
    if (source)
    {
        stbi_image_free(source);
    }
}