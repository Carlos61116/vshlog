#include "vshlog/Sink.h"
#include <iostream>

namespace vsh
{
	void console_writer(const LogEntry& entry, void* context)
	{
		auto* cslContext = static_cast<ConsoleSinkContext*>(context);

		if (cslContext->console_sink_config.min_log_level <= entry.loglevel) {
			std::cout << "[" << vsh::to_string(entry.loglevel) << "] "<< entry.file << " " << entry.line << " " << entry.text << "\n";
		}
	}

	void file_writer(const LogEntry& entry, void* context)
	{
		auto* fileCtx = static_cast<FileSinkContext*>(context);

		if (fileCtx && fileCtx->file.is_open() && fileCtx->file_sink_config.min_log_level <= entry.loglevel)
		{
			fileCtx->file << "[" << vsh::to_string(entry.loglevel) << "] " << entry.file << " " << entry.line << " " << entry.text << "\n";
		}

	}

	Sink make_console_sink(ConsoleSinkContext& context, SinkType sink_type)
	{
		return vsh::Sink{.writer = console_writer, .context = &context,.type=sink_type };
	}

	Sink make_file_sink(FileSinkContext& context, SinkType sink_type)
	{

		return vsh::Sink{ .writer = file_writer, .context = &context,.type = sink_type };
	}

	Sink make_file_sink_dynamic(SinkType sink_type)
	{
		return vsh::Sink{ .writer = file_writer, .context = nullptr,.type = sink_type };


	}

}