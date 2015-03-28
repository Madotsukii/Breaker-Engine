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

#include "log.hpp"

// Log
// Public
Breaker::Log::Log(std::string _name, bool stream) : name(_name),
	streamToFile(stream)
{
	//TODO: If streaming, then stream to file on another thread
	//logFile.setFileFromRoot("/log/" name ".log");
	
	add("->[", getName(), "]<- log created");
}

void Breaker::Log::write()
{
	add("Writing system log to [insert file path here]");
	//TODO: Write to file and insert file path to the above
}

std::vector<std::string> Breaker::Log::getLog()
{
	return log;
}

std::string Breaker::Log::getName()
{
	return name;
}

/*Breaker::File Breaker::Log::getFile()
{
	return file;
}*/

// Private
void Breaker::Log::append()
{
	//TODO: Append to file
}
