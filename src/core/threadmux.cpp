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

#include "threadmux.h"
#include "logging/log.h"

static std::mutex barrier;				// Mutex barrier to prevent racing
static std::mutex tBarrier;				// Mutex barrier to prevent racing

template<typename F, typename ... Args>
void ThreadMux::add(std::string name, F func, Args ... args)
{
	std::lock_guard<std::mutex> lk(barrier);
	
	threadList.push_back(std::thread(func, args...));
	nameList.push_back(name);
	statusList.push_back(0);
	
	systemLog.add("[System] Spawned thread: " + name, true);
	
	for (auto &t : threadList)
		t.join();
}
	
void ThreadMux::pause(std::string name)
{
	std::lock_guard<std::mutex> lk(tBarrier);
	//getThread[getTID(name)];
	
	systemLog.add("[System] Paused thread: " + name, true);
}

void ThreadMux::resume(std::string name)
{
	std::lock_guard<std::mutex> lk(tBarrier);
	//getThread[getTID(name)];
	
	systemLog.add("[System] Resumed thread: " + name, true);
}

void ThreadMux::restart(std::string name)
{
	std::lock_guard<std::mutex> lk(tBarrier);
	//getThread[getTID(name)];
	
	systemLog.add("[System] Restarted thread: " + name, true);
}

void ThreadMux::remove(std::string name)
{
	std::lock_guard<std::mutex> lk(tBarrier);
	//getThread[getTID(name)];
	
	systemLog.add("[System] Removed thread: " + name, true);
}

std::vector<std::string> ThreadMux::getThreadNames()
{
	return nameList;
}

int ThreadMux::getTID(std::string name)
{
	for (int i = 0; i < nameList.size(); ++i)
		if (nameList[i] == name)
			return i;
	
	return 0;
}

int ThreadMux::getStatus(std::string name)
{
	return statusList[getTID(name)];
}

std::thread* ThreadMux::getThread(int tid)
{
	return &threadList[tid];
}
