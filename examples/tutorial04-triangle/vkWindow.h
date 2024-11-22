#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "vkContext.h"


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

void createSurface(vkContext& contextref);
void initWindow(vkContext& contextref);