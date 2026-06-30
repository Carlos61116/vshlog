#include "vshlog/Logger.h"
#include "vshlog/Config.h"
#include <vector>
#include <chrono>
#include <filesystem>
#include "vshlog/sink.h"
#include <unordered_map>
#include <vshlog/Hash.h>


namespace
{
		std::vector<vsh::Sink> sinks;
		vsh::LogLevel minLogLevel;
		std::unordered_map<std::uint32_t, vsh::FileSinkContext> file_contexts;
		std::vector<vsh::ConsoleSinkContext> console_contexts;
		vsh::FileSinkConfig file_config;
};

namespace vsh
{
	void init(vsh::LogLevel min_level)
	{
		minLogLevel = min_level;
		file_contexts.reserve(16);
	}

	void shutdown()
	{
		sinks.clear();
		file_contexts.clear();
		console_contexts.clear();
	}

	void add_console_sink(const vsh::ConsoleSinkConfig& config)
	{
		console_contexts.emplace_back();

		auto& ctx = console_contexts.back();

		ctx.console_sink_config = config;

		sinks.push_back(vsh::make_console_sink(ctx, vsh::SinkType::CONSOLE));
	}

	vsh::FileSinkContext* get_file_context(const char* file, const std::string& category)
	{
		std::string log_path = "Logs/" + category + "/" + std::filesystem::path(file).stem().string() + ".log";


		auto id = vsh::hash_str(file);

		auto [it, inserted] = file_contexts.try_emplace(id);

		if (inserted)
		{

			it->second.path = log_path;
			it->second.file_sink_config = file_config;


			auto dir = std::filesystem::path(log_path).parent_path();

			if (!dir.empty())
			{
				std::filesystem::create_directories(
					std::filesystem::path(log_path).parent_path()
				);
			}

			it->second.file.open(log_path, std::ios::app);

		}

		return &it->second;

	}


	void add_file_sink(const vsh::FileSinkConfig& filesinkConfig)
	{
		file_config = filesinkConfig;
		sinks.push_back(vsh::make_file_sink_dynamic(vsh::SinkType::FILE_T));
	}

	void* get_context(void* context, SinkType sink_t, const char* file, const std::string& category)
	{
		switch (sink_t)
		{
		case vsh::SinkType::FILE_T: return get_file_context(file, category);
		case vsh::SinkType::CONSOLE: return context;
		default: return nullptr;
		}
	}

	void log(vsh::LogLevel level, const std::string& text, const std::string& category, const char* file, std::uint32_t line)
	{
		vsh::LogEntry le = vsh::LogEntry{ .loglevel = level, .text = text, .time = std::chrono::system_clock::now() ,.category = category,.file = file,.line = line };


		for (auto& sinksr : sinks)
		{
			sinksr.writer(le, get_context(sinksr.context,sinksr.type,file, category));
		}
	}
	
}