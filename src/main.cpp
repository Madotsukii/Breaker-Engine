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

#include <iostream>
#include <string>

//CMake crap
#include "config.h"

//Source includes
#include "core/io/file.h"

//Entry point, decides what to do and does it
int main(const int argc, const char** argv)
{
	//TODO: Open README.md and store in (string)variable
	//Get passed-in arguments and decide what to do based off of them
	for (int i = 0; i < argc; i++)
	{
		//Prints README.md and general/command information
		if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
			//TODO: Print out README.md
			std::cout << "Usage: BreakerEngine [OPTIONS] FILE\n\n" <<
				"Option	Long option	Meaning\n" <<
				" -h	--help		Show this message\n" <<
				" -v	--version	Prints the program version\n";
		//Prints the program version
		else if (std::string(argv[i]) == "-v" ||
				std::string(argv[i]) == "--version")
			std::cout << "Breaker Engine v" << BreakerEngine_VERSION_MAJOR <<
				"." << BreakerEngine_VERSION_MINOR << std::endl;
	}
	
	//Implement settings file at some point
	//Window window(800, 600, "Breaker Engine");
	//RenderingEngine renderer(window);
	
	//CoreEngine engine(60, &window, &renderer, &game);
	//engine.start();
	//
	//Implement Unit Tests?
	
	//Implement (if)error later
	return 0;
}
