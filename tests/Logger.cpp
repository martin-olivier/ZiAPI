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

TEST(Logger, Info)
{
    OSRedirector os(std::cout);

    ziapi::Logger::Info("infos");
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::BLUE + std::string(" [i] ") + ziapi::color::DEFAULT + "infos") !=
                std::string::npos);
}

TEST(Logger, Warning)
{
    OSRedirector os(std::cout);

    ziapi::Logger::Warning("warning");
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::YELLOW + std::string(" [!] ") + ziapi::color::DEFAULT + "warning") !=
                std::string::npos);
}

TEST(Logger, Error)
{
    OSRedirector os(std::cerr);

    ziapi::Logger::Error("error");
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::RED + std::string(" [X] ") + ziapi::color::DEFAULT + "error") !=
                std::string::npos);
}

TEST(Logger, Debug)
{
    OSRedirector os(std::cout);

    ziapi::Logger::Debug("debug");
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::GREEN + std::string(" [&] ") + ziapi::color::DEFAULT + "debug") !=
                std::string::npos);
}

TEST(Logger, Variadic)
{
    OSRedirector os(std::cout);

    ziapi::Logger::Debug("debug", ' ', 1.1);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(ziapi::color::GREEN + std::string(" [&] ") + ziapi::color::DEFAULT + "debug 1.1") !=
                std::string::npos);
}
