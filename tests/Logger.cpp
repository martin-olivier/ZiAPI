#include <gtest/gtest.h>

#include "ZiAPI/Logger.hpp"

class OSRedirector {
    private:
        std::ostringstream _oss{};
        std::streambuf *_backup{};
        std::ostream &_c;

    public:
        OSRedirector(OSRedirector &) = delete;
        OSRedirector &operator=(OSRedirector &) = delete;

        OSRedirector(std::ostream &c) : _c(c) {
            _backup = _c.rdbuf();
            _c.rdbuf(_oss.rdbuf());
        }

        ~OSRedirector() {
            _c.rdbuf(_backup);
        }

        const std::string getContent() {
            _oss << std::flush;
            return _oss.str();
        }
};

TEST(Logger, info)
{
    OSRedirector os(std::cout);

    ziapi::Logger("infos");
    auto out = os.getContent();
    EXPECT_TRUE(out.find(Color::BLUE + std::string("[i] ") + Color::DEFAULT + "infos") != std::string::npos);
}

TEST(Logger, warning)
{
    OSRedirector os(std::cout);

    ziapi::Logger("warning", ziapi::LogType::WARNING);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(Color::YELLOW + std::string("[!] ") + Color::DEFAULT + "warning") != std::string::npos);
}

TEST(Logger, error)
{
    OSRedirector os(std::cout);

    ziapi::Logger("error", ziapi::LogType::ERROR);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(Color::RED + std::string("[X] ") + Color::DEFAULT + "error") != std::string::npos);
}

TEST(Logger, debug)
{
    OSRedirector os(std::cout);

    ziapi::Logger("debug", ziapi::LogType::DEBUG);
    auto out = os.getContent();
    EXPECT_TRUE(out.find(Color::GREEN + std::string("[&] ") + Color::DEFAULT + "debug") != std::string::npos);
}