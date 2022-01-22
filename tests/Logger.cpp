#include "ziapi/Logger.hpp"

#include <gtest/gtest.h>

class OSRedirector {
private:
    std::ostringstream _oss{};
    std::streambuf *_backup{};
    std::ostream &_c;

public:
    OSRedirector(OSRedirector &) = delete;
    OSRedirector &operator=(OSRedirector &) = delete;

    OSRedirector(std::ostream &c) : _c(c)
    {
        _backup = _c.rdbuf();
        _c.rdbuf(_oss.rdbuf());
    }

    ~OSRedirector() { _c.rdbuf(_backup); }

    const std::string getContent()
    {
        _oss << std::flush;
        return _oss.str();
    }
};

TEST(Logger, info)
{
    OSRedirector os(std::cout);

    ziapi::Logger("infos");
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::BLUE + std::string("[i] ") + ziapi::color::DEFAULT + "infos") !=
                std::string::npos);
}

TEST(Logger, warning)
{
    OSRedirector os(std::cout);

    ziapi::Logger("warning", ziapi::LogType::WARNING);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::YELLOW + std::string("[!] ") + ziapi::color::DEFAULT + "warning") !=
                std::string::npos);
}

TEST(Logger, error)
{
    OSRedirector os(std::cout);

    ziapi::Logger("error", ziapi::LogType::ERROR);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::RED + std::string("[X] ") + ziapi::color::DEFAULT + "error") !=
                std::string::npos);
}

TEST(Logger, debug)
{
    OSRedirector os(std::cout);

    ziapi::Logger("debug", ziapi::LogType::DEBUG);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::GREEN + std::string("[&] ") + ziapi::color::DEFAULT + "debug") !=
                std::string::npos);
}

TEST(Logger, stream)
{
    OSRedirector os(std::cerr);

    ziapi::Logger("debug on cerr", ziapi::LogType::DEBUG, std::cerr);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::GREEN + std::string("[&] ") + ziapi::color::DEFAULT + "debug on cerr") !=
                std::string::npos);
}