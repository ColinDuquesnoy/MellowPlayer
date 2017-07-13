#pragma once

#include "Style.hpp"

namespace MellowPlayer::Application {

    class IStyleLoader {
    public:
        virtual ~IStyleLoader() = default;

        virtual Style load(const QString& path) const = 0;
    };
}