#include "Logger.h"

std::ostringstream oss;
std::shared_ptr<spdlog::logger> Logger::s_outputLogger;
std::shared_ptr<spdlog::logger> Logger::s_fileLogger;

void Logger::Init()
{
	auto msvc_sink_mt = std::make_shared<spdlog::sinks::msvc_sink_mt>();

	s_outputLogger = std::make_shared<spdlog::logger>("Output logger", msvc_sink_mt);
	s_outputLogger->set_level(spdlog::level::trace);
	s_outputLogger->set_pattern("%^[%T] [%n] [%l] %v%$");
	
	auto basic_file_sink_mt = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);
	
	s_fileLogger = std::make_shared<spdlog::logger>("File logger", basic_file_sink_mt);
	s_fileLogger->set_pattern("%^[%c] [%l] %v%$");
}

void Logger::LogInfo(std::string message)
{
	s_outputLogger->info(message);
	s_fileLogger->info(message);
}

void Logger::LogWarning(std::string message)
{
	s_outputLogger->warn(message);
	s_fileLogger->warn(message);
}

void Logger::LogError(std::string message)
{
	s_outputLogger->error(message);
	s_fileLogger->error(message);
}
