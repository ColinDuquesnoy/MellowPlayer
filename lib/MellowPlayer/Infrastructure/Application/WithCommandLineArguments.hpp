#pragma once

#include <MellowPlayer/Infrastructure/Application/ApplicationDecorator.hpp>

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments;

    class WithCommandLineArguments: public ApplicationDecorator
    {
    public:
        WithCommandLineArguments(IApplication& application, ICommandLineArguments& commandLineArguments);

        void initialize() override;

    private:
        ICommandLineArguments& commandLineArguments_;
    };
}
