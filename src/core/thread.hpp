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

/* Threads and thread manipulation */

#ifndef THREAD_H
#define THREAD_H

#include <atomic>
#include <deque>
#include <functional>
#include <future>
#include <list>
#include <vector>
#include <string>

namespace Breaker
{
	class Thread_Pool
	{
	public:
		Thread_Pool(std::string name, unsigned int);// Constructor
		~Thread_Pool();								// Destructor
		
		template<typename Ret, typename... Args>	// Start asynchronous thread
		std::future<Ret> async(std::function<Ret(Args...)> f, Args... args)
		{
			typedef std::function<Ret(Args...)> F;
			
			std::atomic<bool>* ready = new std::atomic<bool>(false);
			std::promise<Ret>* p = new std::promise<Ret>;
			
			auto task_wrapper = [p, ready](F&& f, Args&&... args)
			{
				p->set_value(f(args...));
				ready->store(true);
			};
			
			auto ret_wrapper = [p, ready]() -> Ret
			{
				while (!ready->load())
					std::this_thread::yield();
				
				auto temp = p->get_future().get();
				
				// Clean up resources
				delete p;
				delete ready;
				
				return temp;
			};
			
			task_mutex.lock();
			tasks.emplace_back(std::async(std::launch::deferred, task_wrapper,
				std::move(f), std::move(args...)));
			task_mutex.unlock();
			
			return std::async(std::launch::deferred, ret_wrapper);
		}
		
		template<typename Ret>
		std::future<Ret> async(std::function<Ret()> f)
		{
			typedef std::function<Ret()> F;
			
			std::atomic<bool>* ready = new std::atomic<bool>(false);
			std::promise<Ret>* p = new std::promise<Ret>;
			
			auto task_wrapper = [p, ready](F&& f)
			{
				p->set_value(f());
				ready->store(true);
			};
			
			auto ret_wrapper = [p, ready]() -> Ret
			{
				while (!ready->load())
					std::this_thread::yield();
				
				auto temp = p->get_future().get();
				
				// Clean up resources
				delete p;
				delete ready;
				
				return temp;
			};
			
			task_mutex.lock();
			tasks.emplace_back(std::async(std::launch::deferred, task_wrapper,
				std::move(f)));
			task_mutex.unlock();
			
			return std::async(std::launch::deferred, ret_wrapper);
		}
		
		template<typename... Args>
		std::future<void> async(std::function<void(Args...)> f, Args... args)
		{
			typedef std::function<void(Args...)> F;
			
			std::atomic<bool>* ready = new std::atomic<bool>(false);
			std::promise<void>* p = new std::promise<void>;
			
			auto task_wrapper = [p, ready](F&& f, Args&&... args)
			{
				f(args...);
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
				std::move(f), std::move(args...)));
			task_mutex.unlock();
			
			return std::async(std::launch::deferred, ret_wrapper);
		};
		
		std::future<void> async(std::function<void()> f);
		
		std::string getName();						// Get pool name
		
	protected:
		void thread_func();							// Maintain until joined
		void init_threads();						// Initialize threads
	
	private:
		bool join = false;							// Join the threads?
		std::string name;							// Name of thread pool
		unsigned int num_threads;					// Number of threads
		
		std::mutex task_mutex;						// Mutex lock
		std::deque<std::future<void>> tasks;		// List of tasks
		
		std::list<std::thread> threads;				// List of threads
	};
	
	// Command queue class, a queue of commands to execute
	class CommandQueue
	{
		public:
			void add(std::string cmd);				// Add to queue
			
			std::vector<std::string> getQueue();	// Get command queue
			std::string getLast();					// Get last command
		
		private:
			std::mutex command_mutex;				// Mutex lock
			std::vector<std::string> queue;			// Command queue
	};
}

#endif // THREAD_H
