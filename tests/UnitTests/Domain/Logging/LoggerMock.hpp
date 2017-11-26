#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <gmock/gmock.h>
#include <iostream>

namespace MellowPlayer::Domain::Tests
{
    class LoggerMock: public ILogger
    {
    public:
        LoggerMock(): name_("fakeLogger")
        {
            ON_CALL(*this, log(testing::_, testing::_, testing::_, testing::_)).WillByDefault(testing::Invoke(
                    [](const std::string& message, LogLevel, const char*, int)
                    {
                        std::cout << message << std::endl;
                    }));

            ON_CALL(*this, name()).WillByDefault(testing::Invoke(
                    [&]() -> const std::string&
                    {
                        return name_;
                    }
            ));
        }

        MOCK_METHOD4(log, void(const std::string&, LogLevel, const char*, int));
        MOCK_CONST_METHOD0(name, const std::string&());

    private:
        std::string name_;
    };
}
