#pragma once

#include "Common.h"

namespace pipeline{

	class kFileManager
	{
	public:

		static std::vector<char> LoadShaderFile(const std::string& filePath);
	};

}

