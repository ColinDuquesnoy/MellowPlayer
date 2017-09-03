#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Application
{
    struct Theme;

    class IThemeLoader
    {
    public:
        virtual ~IThemeLoader() = default;

        virtual Theme load(const QString& path) const = 0;
    };
}