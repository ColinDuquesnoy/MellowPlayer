#pragma once

#include <MellowPlayer/Domain/Theme/IThemeLoader.hpp>

namespace MellowPlayer::Domain
{
    struct Theme;
}

namespace MellowPlayer::Infrastructure
{
    class ThemeLoader : public Domain::IThemeLoader
    {
    public:
        Domain::Theme load(const QString& path) const override;
    };
}
