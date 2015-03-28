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

/* Directory manipulation */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>

// Directory class, a container for information relating to said directory
class Directory
{
public:
	Directory();									// Finds and sets default
													// path (engine root)
	
	std::string getDirPath();						// Get directory path
	std::string getDirName();						// Get directory name
	
	std::string setDir(std::string path);			/* Find and set directory
													from current directory */
	std::string setDirFromRoot(std::string path);	/* Find and set directory
													from (engine) root */
	
	bool exists();									// Check if directory exists
	
	

private:
	std::string path;
	std::string name;
};

#endif // DIRECTORY_H
