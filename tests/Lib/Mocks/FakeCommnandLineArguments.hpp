#pragma once

#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <fakeit.hpp>
#include <memory>
#include <gmock/gmock.h>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeCommandLineArguments: public ICommandLineArguments
    {
    public:
        void parse() override
        {
            parsed = true;
        }

        void setService(const QString& service)
        {
            service_ = service;
        }

        QString service() const override
        {
            return service_;
        }

        int autoQuitDelay() const override
        {
            return 0;
        }

        bool playPauseRequested() const override
        {
            return false;
        }

        bool nextRequested() const override
        {
            return false;
        }

        bool previousRequested() const override
        {
            return false;
        }

        bool toggleFavoriteRequested() const override
        {
            return false;
        }

        Domain::LogLevel logLevel() const override
        {
            return Domain::LogLevel::Info;
        }

        bool parsed = false;

    private:
        QString service_;
    };
}
