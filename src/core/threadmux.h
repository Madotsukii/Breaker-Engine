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

/* Thread multiplexor */

#ifndef THREADMUX_H
#define THREADMUX_H

#include <thread>
#include <vector>
#include <string>

// Thread multiplexor class, manipulates, stores, and regulates threads
class ThreadMux
{
public:
	template<typename F, typename ... Args>			// Add thread
	void add(std::string name, F func, Args ... args);
	
	void pause(std::string name);					// Pause thread
	void resume(std::string name);					// Resume thread
	
	void restart(std::string name);					// Restart thread
	void remove(std::string name);					// Remove thread
	
	std::vector<std::string> getThreadNames();		// Get thread names, use
													// .size() for # of threads
	
	int getTID(std::string name);					// Get thread ID
	int getStatus(std::string name);				// Get status of thread ->
													// 0 = Running - 1 = Paused
													// 3 = Non-existant

private:
	std::vector<std::thread> threadList;			// List of threads
	std::vector<int> statusList;					// List of thread status'
	std::vector<std::string> nameList;				// List of thread names
	
	std::thread* getThread(int tid);				// Get thread handle
};

extern ThreadMux threadMux;

#endif // THREADMUX_H
