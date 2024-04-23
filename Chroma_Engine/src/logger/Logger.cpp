#include "logger/Logger.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

namespace chroma
{
	static Logger* instance;

	Logger::Logger() {}

	Logger* Logger::GetInstance()
	{
		if (instance == nullptr)
			instance = new Logger();

		return instance;
	}

	void Logger::Log(const std::string& content)
	{
		std::ofstream stream(m_FILE, std::ofstream::app);

		// Write Content to File
		if (m_firstWrite)
		{
			stream << "-- New Session --" << std::endl;
			m_firstWrite = false;
		}

		stream << content << std::endl;
		std::cout << content << std::endl;
	}
}