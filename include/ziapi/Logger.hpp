#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <string>

#include "Color.hpp"

namespace ziapi {

/**
 *  Log a message in a stream
 *  @param message message to be logged
 *  @param log_type Debug, Info, Warning or Error
 *  @param stream the stream where the message will be logged
 */
class Logger {
private:
    enum LogType { debug, info, warning, error };
    static void Log(const std::string &message, std::ostream &stream, LogType log_type)
    {
        static const std::map<LogType, std::string> log_type_map{
            {LogType::info, color::BLUE + std::string(" [i] ") + color::DEFAULT},
            {LogType::warning, color::YELLOW + std::string(" [!] ") + color::DEFAULT},
            {LogType::error, color::RED + std::string(" [X] ") + color::DEFAULT},
            {LogType::debug, color::GREEN + std::string(" [&] ") + color::DEFAULT},
        };
        time_t actual_time = std::time(nullptr);
        std::string time_str = std::ctime(&actual_time);
        time_str.erase(std::remove_if(time_str.begin(), time_str.end(), [](char a) { return a == '\n'; }),
                       time_str.end());

        stream << color::CYAN << time_str << color::DEFAULT;
        stream << log_type_map.at(log_type) << message << color::DEFAULT << std::endl;
    }

public:
    static void Debug(const std::string &message, std::ostream &stream = std::cout)
    {
        Log(message, stream, LogType::debug);
    }
    static void Info(const std::string &message, std::ostream &stream = std::cout)
    {
        Log(message, stream, LogType::info);
    }
    static void Warning(const std::string &message, std::ostream &stream = std::cout)
    {
        Log(message, stream, LogType::warning);
    }
    static void Error(const std::string &message, std::ostream &stream = std::cerr)
    {
        Log(message, stream, LogType::error);
    }
};

}  // namespace ziapi
