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

/* Logging */

#ifndef LOG_H
#define LOG_H

#include <string>
#include <vector>

#include "../io/file.h"

// Log class, for logging purposes
class Log
{
public:
	bool streamToFile = false;				// Continuously stream log to file?
	
	Log(const std::string name);			// Create log with name ->[name]<-
	
	void add(std::string content, bool endLine);	// Add content to log
	void _add(std::string content, bool endLine);	// Add content to log
	void write();							// Write content to log file

private:
	std::vector<std::string> log;			// Contents of the log
	//TODO: Implement File
	//File logFile;
	
	void append(bool endLine);				// Append content to log file
};

extern Log systemLog;

#endif // LOG_H
