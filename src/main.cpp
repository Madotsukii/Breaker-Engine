/*
Copyright (C) 2015 <Madotsuki>

This file is part of Breaker Engine.

Breaker Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Breaker Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with Breaker Engine.  If not, see <http://www.gnu.org/licenses/>.
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
			std::cout << "-h --help | Prints this out\n-v --version | Prints the version" << std::endl;
		//Prints README.md and the version
		else if (std::string(argv[i]) == "-v" || std::string(argv[i]) == "--version")
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
