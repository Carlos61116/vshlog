#pragma once

#include "LogEntry.h"
#include "Config.h"

#include <fstream>

namespace vsh {

	struct FileSinkContext
	{
		std::string path;
		std::ofstream file{};
		vsh::FileSinkConfig file_sink_config;
	};

	struct ConsoleSinkContext
	{
		vsh::ConsoleSinkConfig console_sink_config;
	};

	enum class SinkType
	{
		FILE_T,
		CONSOLE
	};

	using WriterFn = void(*)(const LogEntry&, void* context);

	struct Sink {
		WriterFn writer;
		void* context;
		SinkType type;
	};
	
	Sink make_console_sink(ConsoleSinkContext& context,SinkType sink_type);

	Sink make_file_sink(FileSinkContext& context, SinkType sink_type);
	
	Sink make_file_sink_dynamic(SinkType sink_type);


}