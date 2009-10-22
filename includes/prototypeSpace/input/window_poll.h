/* 
 * A class that automatically polls a window.
 * 
 * The polling takes place in a seperate thread.
 *
*/

#ifndef WINDOW_POLL_INCLUDE
#define WINDOW_POLL_INCLUDE

#define POLLER_DEFAULT_WAIT_TIME 0.01f

namespace space {

	// We inherit sf::Thread to make threading the poll function easier.
	class Poller : private sf::Thread {
		public:
			Poller();
			~Poller();
			
			/* ---------------- startPolling ---------------------------
			 * Desc:
			 * 	Starts the poll thread in a seperate thread
			*/
			bool startPolling();
			
			/* ---------------- stopPolling ----------------------------
			 * Desc:
			 * 	Forces the poller to stop polling.
			 * 
			 * Note:
			 * 	You shouldn't need to use this, it is called in the 
			 * 	destructor.
			*/
			bool stopPolling();
			
			/* ----------------- getInput ------------------------------
			 * Desc:
			 * 	Returns a pointer to the sf::Input.
			*/
			const sf::Input* getInput();
			
			/* ---------------- getWindow ------------------------------
			 * Desc:
			 * 	Returns a pointer to associated window.
			*/
			sf::RenderWindow* getWindow();
			
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
			bool setWindow(sf::RenderWindow* _window);
			
			/* ------------------- getWaitTime -------------------------
			 * Desc:
			 * 	Returns the amount of time the Poller is waiting to poll.
			 * 
			 * Note:
			 * 	The returned value is a float in seconds.
			*/
			float getWaitTime();
			
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
			bool setWaitTime(float _time);
			
		private:
			/* -------------------  Run --------------------------------
			 * Desc:
			 * 	This function is run by sf:Thread when startPolling is
			 * 	called.
			*/
			virtual void Run();
			
			/* ------------------- poll --------------------------------
			 * Desc:
			 * 	This function polls the window and updates the windows
			 * 	states.
			*/
			bool poll();
		
			// The a pointer to the window this poller is associated with.
			sf::RenderWindow* window;
			
			// The pointer to the input from the window.
			const sf::Input* input;
			
			// Whether or not we are polling
			bool polling;
			
			// How long to wait between polling
			float wait_time;
	};
	
}

#endif
