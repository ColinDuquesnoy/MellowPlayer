#pragma once

class QString;

namespace MellowPlayer::Application
{
    class IUserScript
    {
    public:
        virtual ~IUserScript() = default;
        virtual QString path() const = 0;
        virtual QString code() const = 0;
        virtual QString name() const = 0;

        virtual void setName(const QString& name) = 0;

        virtual void import(const QString& path) = 0;
        virtual void load(const QString& path) = 0;
    };
}
