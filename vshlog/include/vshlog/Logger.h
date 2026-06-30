#pragma once

#include "LogLevel.h"
#include "vshlog/Config.h"

#include <string>


namespace vsh
{
	void init(vsh::LogLevel min_level);
	void shutdown();
	void add_console_sink(const vsh::ConsoleSinkConfig& config);
	void add_file_sink(const vsh::FileSinkConfig& config);
	void log(vsh::LogLevel level, const std::string& text, const std::string& category, const char* file, std::uint32_t line);

}
