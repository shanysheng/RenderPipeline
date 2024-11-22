#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <fstream>


std::vector<char> readFile(const std::string& filename);


VkShaderModule createShaderModule(VkDevice plogicaldevice, const std::vector<char>& code);
