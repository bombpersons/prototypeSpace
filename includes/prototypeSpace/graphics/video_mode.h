/*
 * Functions to change the video mode
 *
*/

#ifndef VIDEO_MODE_INCLUDE
#define VIDEO_MODE_INCLUDE

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
	sf::RenderWindow* autoVideoMode(char* _title);
	
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
	sf::RenderWindow* setVideoMode(char* _title, int _width, int _height, int _depth, bool _fullscreen);
	sf::RenderWindow* setVideoMode(char* _title, sf::VideoMode _mode, bool _fullscreen);

}

#endif
