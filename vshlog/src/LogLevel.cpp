#include "vshlog/LogLevel.h"

namespace vsh
{
	std::string_view to_string(LogLevel level)
	{
		switch (level)
		{
			case LogLevel::TRACE: return "TRACE";
			case LogLevel::DEBUG: return "DEBUG";
			case LogLevel::INFO: return "INFO";
			case LogLevel::WARN: return "WARN";
			case LogLevel::ERR: return "ERR";
			case LogLevel::FATAL: return "FATAL";
			default: return "UNKNOWN";
		}
	}
}