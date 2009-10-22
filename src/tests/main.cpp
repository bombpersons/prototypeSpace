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
	sf::RenderWindow* window = space::setVideoMode("Test Window", 500, 500, 32, false);
	sf::Clock clock;
	while (clock.GetElapsedTime() < 2) {
		window->Display();
		sf::Sleep(1);
	}
	delete window;
	
	std::cout << "..." << std::endl;
	std::cout << "Saw a window?" << std::endl;
	std::cout << "Good =) We would have crashed otherwise." << std::endl;
	
	std::cout << std::endl;
	std::cout << "Now lets try opening a window for longer. Close this window to continue." << std::endl;
	sf::RenderWindow* test_window = space::setVideoMode("Close Me", 300, 300, 32, false);
	test_window->Display();
	space::Poller poller;
	poller.setWindow(test_window);
	poller.startPolling();
	std::cout << "A window should be open now, close it to continue." << std::endl;
	while (test_window->IsOpened()) { sf::Sleep(0.5f); }
	
}
