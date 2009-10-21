/*
 * Functions to change the video mode
 *
*/

#include <config.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <prototypeSpace/debug/debug.h>

namespace space {

	/* -------------------- autoVideoMode ----------------------------------
	 * Desc:
	 * 	Automatically selects the best video mode available. 
	 * 	Always in fullscreen. Returns null if fails.
	 * 
	 * Params:
	 * 	_title: the title of the window created.
	 * 
	 * Note: 
	 * 	This doesn't always work.
	*/
	sf::RenderWindow* autoVideoMode(char* _title) {
		// Try to create a window using the best mode.
		sf::VideoMode mode = sf::VideoMode::GetMode(0);
		
		sf::RenderWindow* window = new sf::RenderWindow(mode, 
											_title, sf::Style::Fullscreen);
		
		// Did that work?
		if (window != NULL) {
			#ifdef ENABLE_DEBUGGING
			debug.write(1, "Opened Window %i x %i @ %i bits.", mode.Width, mode.Height, mode.BitsPerPixel);
			#endif
			
			// Return the window
			return window;
		} else {
			#ifdef ENABLE_DEBUGGING
			debug.write(1, "Error: Couldn't open Window %i x %i @ %i bits.", mode.Width, mode.Height, mode.BitsPerPixel);
			#endif
			
			// We couldn't get the window
			delete window; // Delete the window, we shouldn't leave pointers
							// lying around.
			return NULL;
		}

	}
	
	/* ---------------------- setVideoMode -----------------------------
	 * Desc:
	 * 	Sets the video mode to a specific setting. Fullscreen or Windowed
	 * 	Returns null if fails.
	 * 
	 * Params:
	 * 	_title: the title of the window created.
	 * 	_width: the width of the window created.
	 * 	_height: the height of the window created.
	 * 	_fullscreen: Boolean described whether or not to make the window
	 * 		fullscreen
	 * 
	 *  Note:
	 * 	Only certain values will work for fullscreen mode. 
	*/
	sf::RenderWindow* setVideoMode(char* _title, int _width, int _height, int _depth, bool _fullscreen) {
		// Try and make a window with these settings
		sf::VideoMode mode = sf::VideoMode(_width, _height, _depth);
		
		sf::RenderWindow* window = NULL;
		
		if (_fullscreen) {
			window = new sf::RenderWindow(mode, _title, sf::Style::Fullscreen);
		} else {
			window = new sf::RenderWindow(mode, _title);
		}
		
		// Did that work?
		if (window != NULL) {
			#ifdef ENABLE_DEBUGGING
			debug.write(1, "Opened Window %i x %i @ %i bits.", mode.Width, mode.Height, mode.BitsPerPixel);
			#endif
			
			// Return the window
			return window;
		} else {
			#ifdef ENABLE_DEBUGGING
			debug.write(1, "Error: Couldn't open Window %i x %i @ %i bits.", mode.Width, mode.Height, mode.BitsPerPixel);
			#endif
			
			// We couldn't get the window
			delete window; // Delete the window, we shouldn't leave pointers
							// lying around.
			return NULL;
		}
		
	}
	/* OVERLOAD -----
	 * Desc:
	 * 	Convenience to use a sf::VideoMode directly
	*/
	sf::RenderWindow* setVideoMode(char* _title, sf::VideoMode _mode, bool _fullscreen) {
		return setVideoMode(_title, _mode.Width, _mode.Height, _mode.BitsPerPixel, _fullscreen);
	}
}
