#pragma once

#include "Common.h"

namespace pipeline{

	class kFileManager
	{
	public:

		static std::vector<char> LoadFile(const std::string& filePath, bool bbinary = true);
	};

}

