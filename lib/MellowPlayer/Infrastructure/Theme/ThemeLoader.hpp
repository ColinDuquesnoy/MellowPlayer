#pragma once

#include <MellowPlayer/Application/Theme/IThemeLoader.hpp>

namespace MellowPlayer::Application
{
    struct Theme;
}

namespace MellowPlayer::Infrastructure
{
    class ThemeLoader : public Application::IThemeLoader
    {
    public:
        Application::Theme load(const QString& path) const override;
    };
}
