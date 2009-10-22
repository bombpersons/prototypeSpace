/* 
 * A class that automatically polls a window.
 * 
 * The polling takes place in a seperate thread.
 *
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <prototypeSpace/debug/debug.h>
#include <prototypeSpace/input/window_poll.h>

namespace space {
	
	Poller::Poller() {
		window = NULL;
		polling = false;
		wait_time = POLLER_DEFAULT_WAIT_TIME;
	}
	
	Poller::~Poller() {
		// Stop the tread
		stopPolling();
	}
	
	/* ---------------- startPolling ---------------------------
	 * Desc:
	 * 	Starts the poll thread in a seperate thread
	*/
	bool Poller::startPolling() {
		// Check if we have a valid window (not NULL)
		if (window != NULL) {
			
			// Start Polling
			#ifdef ENABLE_DEBUGGING
			debug.write(3, "Started Polling Window %i x %i @ %i", window->GetWidth(), window->GetHeight(), window->GetSettings().DepthBits);
			#endif
			polling = true;
			
			// Start the thread
			Launch();
			return true;
		
		// Window was null
		} else {
			
			// Failed
			#ifdef ENABLE_DEBUGGING
			debug.write(3, "Error: Tried to poll a NULL Window");
			#endif
			return false;
		
		}
	}
	
	/* ---------------- stopPolling ----------------------------
	 * Desc:
	 * 	Forces the poller to stop polling.
	 * 
	 * Note:
	 * 	You shouldn't need to use this, it is called in the 
	 * 	destructor.
	*/
	bool Poller::stopPolling() {
		// Check we are actually polling
		if (!polling) {
			#ifdef ENABLE_DEBUGGING
			debug.write(3, "Error: Poller was already stopped");
			#endif
			return true;
		} else {
			// Stop the thread
			polling = false;
			Wait(); // The thread should finish when polling == false
			
			#ifdef ENABLE_DEBUGGING
			debug.write(3, "Stopped polling Window %i x %i @ %i", window->GetWidth(), window->GetHeight(), window->GetSettings().DepthBits);
			#endif
			
			return true;
		}
	}
	
	/* ----------------- getInput ------------------------------
	 * Desc:
	 * 	Returns a pointer to sf::Input.
	*/
	const sf::Input* Poller::getInput() {
		// Just return the input
		return input;
	}
	
	/* ---------------- getWindow ------------------------------
	 * Desc:
	 * 	Returns a pointer to associated window.
	*/
	sf::RenderWindow* Poller::getWindow() {
		// Just return the window, if it's NULL then it hasn't been set.
		return window;
		
	}
	
	/* ------------------ setWindow ----------------------------
	 * Desc:
	 * 	Set's the window to poll
	 * 
	 * Params:
	 * 	_window: A pointer to the window you wish to set this
	 * 		Poller to.
	 * 
	 * Note:
	 * 	startPolling will fail if you haven't called this
	 * 	beforehand.
	 * 
	 * 	This function will fail if you try to pass a NULL
	 * 	pointer.
	*/
	bool Poller::setWindow(sf::RenderWindow* _window) {
		// Check whether or not this is valid
		if (_window != NULL) {
			
			// Good, now set this as the window
			window = _window;
			#ifdef ENABLE_DEBUGGING
			debug.write(4, "Set Window %i x %i @ %i bits to a poll object.", window->GetWidth(), window->GetHeight(), window->GetSettings().DepthBits);
			#endif
			
			return true;
		
		// If we failed...
		} else {
			
			#ifdef ENABLE_DEBUGGING
			debug.write(3, "Error: Couldn't register window with Poller object. Window was NULL.");
			#endif
			
			return false;
		}
	}
	
	/* ------------------- getWaitTime -------------------------
	 * Desc:
	 * 	Returns the amount of time the Poller is waiting to poll.
	 * 
	 * Note:
	 * 	The returned value is a float in seconds.
	*/
	float Poller::getWaitTime() {
		// Just return the wait time.
		return wait_time;
	
	}
	
	/* ------------------- setWaitTime -------------------------
	 * Desc:
	 * 	Set's the amount of time to wait to poll the window.
	 * 
	 * Params:
	 * 	_time: The amount of time to wait, in seconds.
	 * 
	 * Note:
	 * 	If this is set to 0, then the polling thread will take
	 * 	a lot of cpu time and may slow down other threads /
	 * 	processes.
	*/
	bool Poller::setWaitTime(float _time) {
		// Check this float is valid
		
		// It's not negative, right?
		if (_time >= 0) {
			
			// Set this
			wait_time = _time;
			
			// Return
			return true;
		
		// A negative wait time?
		} else {
			#ifdef ENABLE_DEBUGGING
			debug.write(3, "Error: Tried to set a negative wait time for Poller.");
			#endif
			
			return false;
		}
	}
		
	
	/* -----------------------------------------------------------------
	 * ===================== PRIVATE ===================================
	 * -----------------------------------------------------------------
	*/
	
	/* -------------------  Run --------------------------------
	 * Desc:
	 * 	This function is run by sf:Thread when startPolling is
	 * 	called.
	*/
	void Poller::Run() {
		// Call poll while we are still polling.
		while (polling) {
			// Check if this window is still open.
			if (!window->IsOpened()) polling = false;
			
			// Poll
			poll();
			
			// Sleep for a little while
			sf::Sleep(wait_time);
		}
	}
	
	/* ------------------- poll --------------------------------
	 * Desc:
	 * 	This function polls the window and updates the windows
	 * 	states.
	*/
	bool Poller::poll() {
		// If we are polling
		if (polling) {
				sf::Event event;
				while (window->GetEvent(event)) {
					// Get inputs
					input = &(window->GetInput());
					
					// Window closes
					if (event.Type == sf::Event::Closed) {
						window->Close();
					}
				}
				
				// Display the window
				window->Display();
		}
		
		return true;
	}
	
}
