#pragma once

#include "Theme.hpp"

namespace MellowPlayer::Application {

    class IThemeLoader {
    public:
        virtual ~IThemeLoader() = default;

        virtual Theme load(const QString& path) const = 0;
    };
}