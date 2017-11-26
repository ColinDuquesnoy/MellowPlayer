#pragma once

#include <MellowPlayer/Domain/Logging/ILoggerFactory.hpp>
#include "ApplicationDecorator.hpp"

namespace MellowPlayer::Domain
{
    class ILoggerFactory;
}

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments;

    class WithLogging: public ApplicationDecorator
    {
    public:
        WithLogging(IApplication& application,
                    std::unique_ptr<Domain::ILoggerFactory>& loggerFactory,
                    ICommandLineArguments& commandLineArguments);

        void initialize() override;

    private:
        std::unique_ptr<Domain::ILoggerFactory>& loggerFactory_;
        ICommandLineArguments& commandLineArguments_;
    };
}
