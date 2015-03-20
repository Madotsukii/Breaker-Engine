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
#include <mutex>

#include "log.h"
#include "../threadmux.h"

static std::mutex barrier;				// Mutex barrier to prevent racing

Log::Log(std::string name)
{
	//log(File.setFileFromRoot("/log/" name ".log"));
	
	//TODO: If streaming, then stream to file on another thread
}

void Log::add(std::string content, bool endLine)
{
	threadMux.add("System Log", &Log::_add, content, endLine);
}

void Log::_add(std::string content, bool endLine)
{
	std::lock_guard<std::mutex> lk(barrier);
	
	log.push_back(content);
	
	std::cout << log.back();
	
	if (endLine)
		std::cout << std::endl;
	
	if (streamToFile && endLine)
		append(true);
	else if (streamToFile)
		append(false);
}

void Log::write()
{
	add("[System] Writing system log to [insert file path here]", true);
	//TODO: Write to file and insert file path to the above
}

void Log::append(bool endLine)
{
	//TODO: Append to file
}
