#pragma once

#include <QList>

namespace MellowPlayer::Infrastructure
{
    class IPlatformFilter;

    class IPlatform
    {
    public:
        virtual ~IPlatform() = default;

        virtual QString name() const = 0;

        virtual bool isLinux() const = 0;
        virtual bool isAppImage() const = 0;
        virtual bool isWindows() const = 0;
        virtual bool isOsx() const = 0;

        virtual bool match(QList<IPlatformFilter>& filters) const = 0;
    };

    class Platform: public IPlatform
    {
    public:
        QString name() const override;

        bool isLinux() const override;

        bool isAppImage() const override;

        bool isWindows() const override;

        bool isOsx() const override;

        bool match(QList<IPlatformFilter>& filters) const override;

    private:
        static QString Unsupported;
        static QString Linux;
        static QString AppImage;
        static QString Windows;
        static QString OSX;
    };
}
