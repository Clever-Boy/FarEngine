#pragma once

#include <vector>
#include <fstream>

class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
};

