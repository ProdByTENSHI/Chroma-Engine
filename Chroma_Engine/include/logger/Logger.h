#pragma once

#include <string>

namespace chroma
{
	class Logger
	{
	public:
		static Logger* GetInstance();

		void Log(const std::string& content);

	private:
		Logger();
		Logger(const Logger& other);

		const char* const m_FILE = "log/DebugLog.txt";
		bool m_firstWrite = true;
	};
}