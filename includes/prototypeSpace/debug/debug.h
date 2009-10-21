/*
 * An easy class to output debug information.
 * 
*/

#ifndef DEBUG_INCLUDE
#define DEBUG_INCLUDE

#include <config.h>

namespace space {

	#ifdef ENABLE_DEBUGGING

	class Debug {
		public:
			static Debug& Instantiate() {
				static Debug TheDebug;
				return TheDebug;
			}
		
			Debug() {
				to_file = true;
				to_stdout = true;
				level = ENABLE_DEBUGGING;
				log_prefix = "DEBUG: ";
				
				write(0, "Starting Log...");
			}
			
			~Debug() {}
			
			//Writes a string to debug. (This can go to a file and / or stdout)
			bool write(int _level, char* _string, ...);
			
		private:
			bool to_file;
			bool to_stdout;
			int level;
			char* log_prefix;
	};
	
	/* The only instance of Debug should be this one */
	static Debug debug = Debug::Instantiate();
	
	#endif
	
}

#endif
