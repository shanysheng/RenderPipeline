#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "vkContext.h"


void createSurface(vkContext& contextref);
void initWindow(vkContext& contextref);