#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/common.h"

class Logger
{
public:
	static void Init();
	static void LogInfo(std::string message);
	static void LogWarning(std::string message);
	static void LogError(std::string message);

private:
	static std::shared_ptr<spdlog::logger> s_outputLogger;
	static std::shared_ptr<spdlog::logger> s_fileLogger;
};