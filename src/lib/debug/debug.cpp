/*
 * Functions for the debug class.
 * 
*/

#include <config.h>

#include <stdarg.h>
#include <stdio.h>
#include <iostream>

#include <prototypeSpace/debug/debug.h>

namespace space {
	#ifdef ENABLE_DEBUGGING
	
	/*------------------------ write ---------------------------------------
	 * Desc:
	 * 	Writes a string to debug, with debug level _level.
	 * 
	 * Params:
	 * 	_level: Describes the level of debugging required for this to appear
	 * 	_string: The string to send to debug
	 * 	... : Extra params to modify _string (same format as printf())
	 * 
	 * Notes:
	 * 	Use #ifdef DEBUGGING when using this function. This means that
	 * 	this program can easily be compiled without debugging for speed.
	*/
	bool Debug::write(int _level, char* _string, ... ) {
		// Make somewhere where we can store the extra arguments.
		va_list arguments;
		va_start(arguments, _string);
		
		// Check if we are in the right debug level
		if (level >= _level) {
		
			// Now try to print to stdout
			if (to_stdout) {
				printf(log_prefix);
				vprintf(_string, arguments);
				printf("\n");
			}
			
			// Now try to write to debug file
			if (to_file) {
				FILE* file = fopen("debug.log", "a");
				fprintf(file, log_prefix);
				vfprintf(file, _string, arguments);
				fprintf(file, "\n");
				fclose(file);
			}
			
		}
			
	}
	
	#endif
}
