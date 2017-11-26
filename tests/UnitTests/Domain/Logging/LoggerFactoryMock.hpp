#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/ILoggerFactory.hpp>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <gmock/gmock.h>
#include "LoggerMock.hpp"

namespace MellowPlayer::Domain::Tests
{
    class LoggerFactoryMock: public ILoggerFactory
    {
    public:
        LoggerFactoryMock()
        {
            ON_CALL(*this, create(testing::_, testing::_)).WillByDefault(testing::Invoke(
                    [](const std::string&, const LoggerConfig&) -> std::unique_ptr<ILogger>
                    {
                        return std::make_unique<testing::NiceMock<LoggerMock>>();
                    }));
        }
        MOCK_CONST_METHOD2(create, std::unique_ptr<ILogger>(const std::string& name, const LoggerConfig& loggerConfig));
    };
}
