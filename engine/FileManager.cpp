#include "FileManager.h"

namespace pipeline {



    std::vector<char> kFileManager::LoadFile(const std::string& filePath, bool bbinary) {

        std::ios::openmode mode = std::ios::in | std::ios::ate;
        if (bbinary) {
            mode = std::ios::binary | std::ios::ate;
        }

        std::ifstream file(filePath, mode);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

}