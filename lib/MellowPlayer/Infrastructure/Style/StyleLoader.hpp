#pragma once

#include <MellowPlayer/Application/Style/IStyleLoader.hpp>

namespace MellowPlayer::Infrastructure {

    class StyleLoader: public Application::IStyleLoader {
    public:
        Application::Style load(const QString& path) const override;
    };

}