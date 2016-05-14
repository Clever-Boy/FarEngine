#include "Error.h"

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit" << std::endl;
	int tmp = 0;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}
