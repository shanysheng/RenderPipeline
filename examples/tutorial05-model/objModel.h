#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "tiny_obj_loader.h"

#include "vkVertexBuffer.h"

#include <vector>
#include <array>


const std::string MODEL_PATH = "resources/viking_room.obj";
const std::string TEXTURE_PATH = "resources/viking_room.png";


struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};


class objModel {
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;


public:

};



void loadModel(objModel& modelref);
