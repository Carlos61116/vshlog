#pragma once

#include <string_view>

namespace vsh
{
	enum class LogLevel
	{
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERR,
		FATAL
	};

	std::string_view to_string(LogLevel level);

}