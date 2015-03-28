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

#ifndef THREAD_H
#define THREAD_H

#include <atomic>
#include <deque>
#include <functional>
#include <future>
#include <list>
#include <vector>
#include <string>

/**
*	Breaker Engine namespace.
*	Contains various functions and classes used by the Breaker Engine.
*/
namespace Breaker
{
/**
*	Thread pool.
*	Creates and manipulates a pool of threads for multithreaded tasks.
*/
class Thread_Pool
{
public:
    /**
    *	A constructor.
    *	Initializes the threads.
    *	@param name Name of the thread pool.
    *	@param num_threads Number of threads in the thread pool.
    *	@see init_threads()
    *	@see task_mutex
    */
    Thread_Pool(std::string name, unsigned int num_threads);

    /**
    *	A destructor.
    *	Joins the threads and destroys the thread pool.
    *	@see join
    *	@see threads
    *	@see task_mutex
    */
    ~Thread_Pool();

    /**
    *	Add asynchronous thread.
    *	Add an asynchronous thread to the thread pool and return a future.
    *	\tparam Ret Type to work with.
    *	\tparam Args Variadic arguments.
    *	@param f Function passed in for use by thread.
    *	@param args Variadic arguments passed in.
    *	@see tasks
    *	@see task_mutex
    *	@return The asynchronous future
    */
    template<typename Ret, typename... Args>
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

    /**
    *	Add asynchronous thread.
    *	Add an asynchronous thread to the thread pool and return a future.
    *	\tparam Ret Type to work with.
    *	@param f Function passed in for use by thread.
    *	@see tasks
    *	@see task_mutex
    *	@return The asynchronous future
    */
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

    /**
    *	Add asynchronous thread.
    *	Add an asynchronous thread to the thread pool and return a future.
    *	\tparam Args Variadic arguments.
    *	@param f Function passed in for use by thread.
    *	@param args Variadic arguments passed in.
    *	@see tasks
    *	@see task_mutex
    *	@return The asynchronous future
    */
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

    /**
    *	Add asynchronous thread.
    *	Add an asynchronous thread to the thread pool and return a future.
    *	@param f Function passed in for use by thread.
    *	@see tasks
    *	@see task_mutex
    *	@return The asynchronous future
    */
    std::future<void> async(std::function<void()> f);

    /**
    *	Get this name.
    *	Get the pool thread's name.
    *	@see name
    *	@return The pool thread's name
    */
    std::string getName();

protected:
    /**
    *	Maintain threads.
    *	Maintain threads in a for loop until joined.
    *	@see ~Thread()
    *	@see tasks
    *	@see task_mutex
    *	@see join
    */
    void thread_func();

    /**
    *	Initialize threads.
    *	Put threads into a vector and initialize them.
    *	@see thread_func()
    *	@see num_threads
    *	@see threads
    */
    void init_threads();

private:
    /**
    *	Join boolean.
    *	Boolean used to determine whether or not to join the threads.
    */
    bool join = false;

    /**
    *	Thread pool name.
    *	The thread pool name.
    */
    std::string name;

    /**
    *	Number of threads.
    *	The number of threads in the thread pool.
    */
    unsigned int num_threads;

    /**
    *	Task mutex.
    *	Locks the current thread and unlocks to prevent race conditions.
    */
    std::mutex task_mutex;

    /**
    *	Task list.
    *	List of tasks to execute across the threads in the thread pool.
    */
    std::deque<std::future<void>> tasks;

    /**
    *	Thread list.
    *	List of threads in the thread pool
    */
    std::list<std::thread> threads;
};

// Command queue class, a queue of commands to execute
class CommandQueue
{
public:
    /**
    *	Add to queue.
    *	Add command to command queue.
    *	@see command_mutex
    *	@see queue
    */
    void add(std::string cmd);

    /**
    *	Add to queue.
    *	Add command to command queue.
    *	@see command_mutex
    *	@see queue
    */
    std::vector<std::string> getQueue();	///<  Get command queue
    std::string getLast();					///<  Get last command

private:
    std::mutex command_mutex;				///< Mutex lock
    std::vector<std::string> queue;			///< Command queue
};
}

#endif // THREAD_H
