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

#include <iostream>

#include "../thread.hpp"
//#include "../io/file.hpp"

namespace Breaker
{
	static std::mutex log_mutex;				// Mutex lock
	
	inline std::string const& to_string(std::string const& s) {return s;}
	
	// Log class, for logging purposes
	class Log
	{
	public:
		Log(std::string name, bool stream);		// Constructor
		
		template<typename... Args>				// Add content to log
		void add(bool prefix, bool endLine, Args... args)
		{
			std::string content;

			if (prefix)
				content += '[' + name + "]> ";
			
			using Breaker::to_string;
			using std::to_string;
			int unpack[]{0, (content += to_string(args), 0)...};
			static_cast<void>(unpack);			// Avoids "unused variable"

			if (endLine)
				content += '\n';

			log_mutex.lock();
			log.push_back(content);
			std::cout << content;
			log_mutex.unlock();

			if (streamToFile)
				append();
		}
		
		template<typename... Args>
		void add(bool prefix, Args... args)		// ..prefix
		{
			add(prefix, true, args...);
		}
		
		template<typename... Args>
		void add(Args... args)					// ..prefix and endLine
		{
			add(true, true, args...);
		}
		
		void write();							// Write content to log file
		
		std::vector<std::string> getLog();		// Get log contents
		std::string getName();					// Get log name
		//Breaker::File getFile();				// Get log file
		
		static void loop(Breaker::Log log)		// Thread loop
		{
			log.add("->[", log.getName(), "]<- log initialized");

			/*while (!endOfTheLine)
			{

			}*/
		}

	private:
		std::vector<std::string> log;			// Contents of the log
		//TODO: Implement File
		//Breaker::File file;
		std::string name;						// Name of the log
		bool streamToFile;						// Stream to file?
		
		void append();							// Append content to log file
	};
}

extern Breaker::Log systemLog;					// System log

#endif // LOG_H
