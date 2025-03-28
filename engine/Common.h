#ifndef PIPELINE_COMMON_H_GUARD
#define PIPELINE_COMMON_H_GUARD


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/glm.hpp>       // 基本的GLM功能，包括向量和矩阵类型
#include <glm/gtc/matrix_transform.hpp>  // 包含平移、旋转、缩放等变换功能
#include <glm/gtc/quaternion.hpp>       // 如果需要用到四元数转换
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>


#include <stdint.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>

#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>
#include <array>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

enum kGPU_BUFFER_TYPE {
	kGPU_BUFFER_UNKNOW = -1,
	kGPU_BUFFER_INDEXBUFFER,
	kGPU_BUFFER_VERTEXBUFFER,
};



#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << vks::tools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << "\n"; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}


#endif
