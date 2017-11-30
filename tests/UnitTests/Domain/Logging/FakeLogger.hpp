#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <iostream>

namespace MellowPlayer::Domain::Tests
{
    class FakeLogger: public ILogger
    {
    public:
        FakeLogger() : name_("fakeLogger") { }

        void log(const std::string&, LogLevel, const char*, int) override
        {
        }

        const std::string& name() const override
        {
            return name_;
        }

    private:
        std::string name_;
    };
}
