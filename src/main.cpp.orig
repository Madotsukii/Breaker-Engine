/*
Copyright © 2015 Madotsuki <madotsuki@redchan.it>

This software is provided 'as-is', without any express or implied warranty. In
no event will the authors be held liable for any damages arising from the use of
this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software in
		a product, an acknowledgment in the product documentation would be
		appreciated but is not required.

	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.

	3. This notice may not be removed or altered from any source distribution.
*/

#include "config.hpp"
#include "core/thread.hpp"
#include "core/logging/log.hpp"
//#include "core/io/file.hpp"

Breaker::Thread_Pool log_pool("Log", 1);

Breaker::Log systemLog("System", false);
//Breaker::Log testLog("Test", false);

//Entry point, decides what to do and does it
int main(int argc, char** argv)
{
	// Initialize threaded classes
	log_pool.async(std::function<void(Breaker::Log)>(systemLog.loop), systemLog);
	//log_pool.async(std::function<void(Breaker::Log)>(testLog.loop), testLog);
	
	//TODO: Open README.md and store in (string)variable
	//Get passed-in arguments and decide what to do based off of them
	for (int i = 0; i < argc; ++i)
	{
		//Prints README.md and general/command information
		if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
		{
			//TODO: Print out README.md
			systemLog.add(false, "Usage: BreakerEngine [OPTIONS]\n\n",
				"Option	Long option	Meaning\n",
				" -h	--help		Show this message and exits\n",
				" -v	--version	Prints the executable version and exits");
			
			//TODO: Make exception system later to exit
		}
		//Prints the program version
		else if (std::string(argv[i]) == "-v" ||
			std::string(argv[i]) == "--version")
		{
			systemLog.add(false, "Breaker Engine v",
				BreakerEngine_VERSION_MAJOR, ".", BreakerEngine_VERSION_MINOR);
			
			//TODO: Make exception system later to exit
		}
	}
	
	//Implement settings file at some point
	//Window window(800, 600, "Breaker Engine");
	//RenderingEngine renderer(window);
	
	//CoreEngine engine(60, &window, &renderer, &game);
	//engine.start();
	//
	//Implement Unit Tests?
	
	//Implement (if)error later
	
	systemLog.add("Destroying thread pool ->[", log_pool.getName(), "]<-");
		// TODO: Put clean up method in exception system
	return 0;
}
