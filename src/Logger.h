#pragma once

#include <memory>
#include <spdlog/logger.h>

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