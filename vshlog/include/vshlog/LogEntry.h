#pragma once

#include <string>
#include <chrono>

#include "LogLevel.h"

namespace vsh {
	struct LogEntry {
		vsh::LogLevel loglevel;
		std::string text;
		std::chrono::system_clock::time_point time;
		std::string category; //Proximamente Category
		const char* file;
		std::uint32_t line;
	};
}
