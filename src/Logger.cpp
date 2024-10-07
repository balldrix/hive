#include "Logger.h"

std::ostringstream oss;
std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::Init()
{
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
	s_Logger = std::make_shared<spdlog::logger>("Hive", sink);
	s_Logger->set_level(spdlog::level::trace);
	s_Logger->set_pattern("%^[%T] [%n] [%l] %v%$");
}

void Logger::LogInfo(std::string message)
{
	s_Logger->info(message);
}

void Logger::LogWarning(std::string message)
{
	s_Logger->warn(message);
}

void Logger::LogError(std::string message)
{
	s_Logger->error(message);
}
