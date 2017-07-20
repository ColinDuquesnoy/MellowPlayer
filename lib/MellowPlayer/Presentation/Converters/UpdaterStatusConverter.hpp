#pragma once

#include <MellowPlayer/Application/Updater/Updater.hpp>

namespace MellowPlayer::Infrastructure {

    class UpdaterStatusConverter {
    public:
        static QString toString(Application::Updater::Status status);
        static Application::Updater::Status fromString(const QString& string);

        static const QString NONE;
        static const QString CHECKING;
        static const QString DOWNLOADING;
        static const QString INSTALLING;
    };

}
