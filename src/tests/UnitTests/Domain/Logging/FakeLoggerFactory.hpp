#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/ILoggerFactory.hpp>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include "FakeLogger.hpp"

namespace MellowPlayer::Domain::Tests
{
    class FakeLoggerFactory: public ILoggerFactory
    {
    public:
        std::unique_ptr<ILogger> create(const std::string&, const LoggerConfig&) const override
        {
            return std::make_unique<FakeLogger>();
        }
    };
}
