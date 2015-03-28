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

#include "thread.hpp"
#include "logging/log.hpp"

// Thread_Pool
// Public
Breaker::Thread_Pool::Thread_Pool(std::string name, unsigned int num_threads) :
	name(name), num_threads(num_threads)
{
	systemLog.add("Creating thread pool ->[", name, "]<- consisting of ",
		std::to_string(num_threads), " threads");
	
	task_mutex.lock();
	init_threads();
	task_mutex.unlock();
}

Breaker::Thread_Pool::~Thread_Pool()
{
	task_mutex.lock();
	join = true;
	task_mutex.unlock();
	
	for (auto i = threads.begin(); i != threads.end(); ++i)
		i->join();
}

std::future<void> Breaker::Thread_Pool::async(std::function<void()> f)
{
	typedef std::function<void()> F;
	
	std::atomic<bool>* ready = new std::atomic<bool>(false);
	std::promise<void>* p = new std::promise<void>;
	
	auto task_wrapper = [p, ready](F&& f)
	{
		f();
		p->set_value();
		ready->store(true);
	};
	
	auto ret_wrapper = [p, ready]()
	{
		while (!ready->load())
			std::this_thread::yield();
		
		p->get_future().get();
		
		// Clean up resources
		delete p;
		delete ready;
		
		return;
	};
	
	task_mutex.lock();
	tasks.emplace_back(std::async(std::launch::deferred, task_wrapper,
		std::move(f)));
	task_mutex.unlock();
	
	return std::async(std::launch::deferred, ret_wrapper);
}

std::string Breaker::Thread_Pool::getName()
{
	return name;
}


// Protected
void Breaker::Thread_Pool::thread_func()
{
	for (;;)
	{
		task_mutex.lock();
		
		if (tasks.empty() && !join)
		{
			task_mutex.unlock();
			
			std::this_thread::yield();
			
			continue;
		}
		else if (!tasks.empty())
		{
			auto f = std::move(tasks.front());
			
			tasks.pop_front();
			
			task_mutex.unlock();
			
			f.get();
		}
		else if (join)
		{
			task_mutex.unlock();
			
			return;
		}
	}
}

void Breaker::Thread_Pool::init_threads()
{
	for (int i = 0; i < num_threads; ++i)
	{
		std::function<void(void)> f = std::bind(
			&Breaker::Thread_Pool::thread_func, this);
		threads.push_back(std::move(std::thread(f)));
	}
}

// Command Queue
// Public
void Breaker::CommandQueue::add(std::string cmd)
{
	command_mutex.lock();
	queue.push_back(cmd);
	command_mutex.unlock();
}

std::vector<std::string> Breaker::CommandQueue::getQueue()
{
	return queue;
}

std::string Breaker::CommandQueue::getLast()
{
	return queue.back();
}
