#include "FileManager.h"

namespace pipeline {



    std::vector<char> kFileManager::LoadShaderFile(const std::string& filePath) {

        std::ios::openmode mode = std::ios::binary | std::ios::in | std::ios::ate;

        std::ifstream file(filePath, mode);
        if (!file.is_open()) {
            std::cout << "Failed to load shader file:" << filePath << std::endl;
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::cout << "Successfully loaded shader file:" << filePath << std::endl;

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

}