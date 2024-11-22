#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include "vkContext.h"


void createCommandPool(vkContext& contextref);
void createCommandBuffer(vkContext& contextref);