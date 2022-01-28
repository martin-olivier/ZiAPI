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
    template<typename ...Args>
    static void Log(std::ostream &stream, LogType log_type, Args &&...args)
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
        stream << log_type_map.at(log_type);
        ((stream << args), ...) << std::endl;
    }

public:
    template<typename ...Args>
    static void Debug(Args &&...args)
    {
        Log(std::cout, LogType::debug, std::forward<Args>(args)...);
    }
    template<typename ...Args>
    static void Info(Args &&...args)
    {
        Log(std::cout, LogType::info, std::forward<Args>(args)...);
    }
    template<typename ...Args>
    static void Warning(Args &&...args)
    {
        Log(std::cout, LogType::warning, std::forward<Args>(args)...);
    }
    template<typename ...Args>
    static void Error(Args &&...args)
    {
        Log(std::cerr, LogType::error, std::forward<Args>(args)...);
    }
};

}  // namespace ziapi
