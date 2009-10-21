/*
 * Just a small test app, to test wether or not the library
 * was built properly.
 *
*/

#include <SFML/System.hpp>

#include <iostream>
#include <prototypeSpace/prototypeSpace.h>

int main() {
	std::cout << "Testing..." << std::endl;
	space::test();
	
	std::cout << std::endl << "Let's try and open a window! You should see a window show for a few seconds." << std::endl;
	sf::Window* window = space::setVideoMode("Test Window", 500, 500, 32, false);
	sf::Clock clock;
	while (clock.GetElapsedTime() < 2) {
		window->Display();
		sf::Sleep(1);
	}
	
	std::cout << "..." << std::endl;
	std::cout << "Saw a window?" << std::endl;
	std::cout << "Good =) We would have crashed otherwise." << std::endl;
	
	std::cout << std::endl;
	std::cout << "Now let's try loading a sprite?" << std::endl;
	
}
