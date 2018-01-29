#pragma once

#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <fakeit/fakeit.hpp>
#include <memory>

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
            return playPauseRequested_;
        }

        void setPlayPauseRequested(bool value)
        {
            playPauseRequested_ = value;
        }

        bool nextRequested() const override
        {
            return nextRequested_;
        }

        void setNextRequested(bool value)
        {
            nextRequested_ = value;
        }

        bool previousRequested() const override
        {
            return previousRequested_;
        }

        void setPreviousRequested(bool value)
        {
            previousRequested_ = value;
        }

        bool toggleFavoriteRequested() const override
        {
            return toggleFavoriteRequested_;
        }

        void setToggleFavoriteRequested(bool value)
        {
            toggleFavoriteRequested_ = value;
        }

        Domain::LogLevel logLevel() const override
        {
            return Domain::LogLevel::Error;
        }

        bool parsed = false;

    private:
        QString service_;
        bool playPauseRequested_ = false;
        bool nextRequested_ = false;
        bool previousRequested_ = false;
        bool toggleFavoriteRequested_ = false;
    };
}
