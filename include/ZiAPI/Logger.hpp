#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <map>
#include "Color.hpp"

namespace ziapi {
enum class LogType : uint8_t
{
    INFO,
    WARNING,
    ERROR,
    DEBUG,
};

inline void Logger(const std::string &message, LogType log_type = LogType::INFO)
{
    static const std::map<LogType, std::string> log_type_map {
        {LogType::INFO, Color::BLUE + std::string("[i] ") + Color::DEFAULT},
        {LogType::WARNING, Color::YELLOW + std::string("[!] ") + Color::DEFAULT},
        {LogType::ERROR, Color::RED + std::string("[X] ") + Color::DEFAULT},
        {LogType::DEBUG, Color::GREEN + std::string("[&] ") + Color::DEFAULT},
    };

    time_t actual_time = std::time(nullptr);
    std::string time_str = std::ctime(&actual_time);
    time_str.erase(remove_if(time_str.begin(), time_str.end(), [](char a) {return a == '\n';}), time_str.end());

    std::cout << '[' << time_str << ']';
    std::cout << log_type_map.at(log_type) << message << Color::DEFAULT << std::endl;
}
}