#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <string>

#include "Color.hpp"

namespace ziapi {

/**
 *  Set the log type to alter the print format
 */
enum class LogType : uint8_t {
    INFO,
    WARNING,
    ERROR,
    DEBUG,
};

/**
 *  Log a message in a stream
 *  @param message message to be logged
 *  @param log_type set the log type to alter the print format (default: LogType::INFO)
 *  @param stream the stream where the message will be logged (default: std::cout)
 */
inline void Logger(const std::string &message, LogType log_type = LogType::INFO, std::ostream &stream = std::cout)
{
    static const std::map<LogType, std::string> log_type_map{
        {LogType::INFO, color::BLUE + std::string(" [i] ") + color::DEFAULT},
        {LogType::WARNING, color::YELLOW + std::string(" [!] ") + color::DEFAULT},
        {LogType::ERROR, color::RED + std::string(" [X] ") + color::DEFAULT},
        {LogType::DEBUG, color::GREEN + std::string(" [&] ") + color::DEFAULT},
    };

    time_t actual_time = std::time(nullptr);
    std::string time_str = std::ctime(&actual_time);
    time_str.erase(std::remove_if(time_str.begin(), time_str.end(), [](char a) { return a == '\n'; }), time_str.end());

    stream << color::CYAN << time_str << color::DEFAULT;
    stream << log_type_map.at(log_type) << message << color::DEFAULT << std::endl;
}

}  // namespace ziapi
