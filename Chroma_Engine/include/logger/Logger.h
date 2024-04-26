#pragma once

#include <string>

namespace chroma
{
	class Logger
	{
	public:
		static Logger* GetInstance();

		//! Prints out the given Content in the Console and writes it the Log File
		void Log(const std::string& content);

	private:
		Logger();
		Logger(const Logger& other);

		//! Output Log File Path
		const char* const m_FILE = "log/DebugLog.txt";

		//! Bool to check if the Log was written to in this Session
		bool m_firstWrite = true;
	};
}