#include "Ziapi/Logger.hpp"

void logger_example()
{
    ziapi::Logger("some informations");
    ziapi::Logger("some informations again", ziapi::LogType::INFO);
    ziapi::Logger("something unusual happend", ziapi::LogType::WARNING);
    ziapi::Logger("oh a critical error", ziapi::LogType::ERROR);
    ziapi::Logger("some debug print", ziapi::LogType::DEBUG);
}