#include "IOManager.h"

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	// Go to the end of the file
	file.seekg(0, std::ios::end);

	// Get the size
	int fileSize = file.tellg();

	// Go back to the beginning of the file
	file.seekg(0, std::ios::beg);

	// Reduce file size (ignore headers byte if present)
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*) &buffer[0], fileSize);
	file.close();

	return true;
}
