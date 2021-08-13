#include <iostream>
#include <SDL.h>

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	std::cout << "Test" << std::endl;
	std::cin.get();
	return 0;
}