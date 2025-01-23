#ifndef PIPELINE_COMMON_H_GUARD
#define PIPELINE_COMMON_H_GUARD


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <cmath>
#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <optional>
#include <set>


enum kGPU_BUFFER_TYPE {
	kGPU_BUFFER_UNKNOW = -1,
	kGPU_BUFFER_INDEXBUFFER,
	kGPU_BUFFER_VERTEXBUFFER,
};




#endif
