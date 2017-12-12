#pragma once

#include <MellowPlayer/Infrastructure/Application/ApplicationDecorator.hpp>

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments;

    class WithCommandLineArguments: public ApplicationDecorator
    {
    public:
        WithCommandLineArguments(const std::shared_ptr<IApplication>& application, ICommandLineArguments& commandLineArguments);

        void initialize() override;

    private:
        ICommandLineArguments& commandLineArguments_;
    };
}
