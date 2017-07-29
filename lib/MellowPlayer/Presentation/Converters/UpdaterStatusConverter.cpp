#include "UpdaterStatusConverter.hpp"
#include <QtCore/QMap>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

const QString UpdaterStatusConverter::NONE = "";
const QString UpdaterStatusConverter::CHECKING = QObject::tr("Checking for update...");
const QString UpdaterStatusConverter::UPDATE = QObject::tr("An update is available...");
const QString UpdaterStatusConverter::DOWNLOADING = QObject::tr("Downloading update...");
const QString UpdaterStatusConverter::INSTALLING = QObject::tr("Installing update...");
const QString UpdaterStatusConverter::INSTALLED = QObject::tr("Update installed, you can now restart the application...");
const QString UpdaterStatusConverter::FAILURE = QObject::tr("Failed to install update, check logs for warning and errors and try again...");

QString UpdaterStatusConverter::toString(Updater::Status status)
{
    static QMap<Updater::Status, QString> map = {{Updater::Status::None, NONE},
                                                 {Updater::Status::Checking, CHECKING},
                                                 {Updater::Status::UpdateAvailable, UPDATE},
                                                 {Updater::Status::Downloading, DOWNLOADING},
                                                 {Updater::Status::Installing, INSTALLING},
                                                 {Updater::Status::Installed, INSTALLED},
                                                 {Updater::Status::Failure, FAILURE}};

    return map[status];
}

Updater::Status UpdaterStatusConverter::fromString(const QString& string)
{
    static QMap<QString, Updater::Status> map = {{NONE, Updater::Status::None},
                                                 {CHECKING, Updater::Status::Checking},
                                                 {UPDATE, Updater::Status::UpdateAvailable},
                                                 {DOWNLOADING, Updater::Status::Downloading},
                                                 {INSTALLING, Updater::Status::Installing},
                                                 {INSTALLED, Updater::Status::Installed},
                                                 {FAILURE, Updater::Status::Failure}};

    if (map.contains(string))
        return map[string];
    return Updater::Status::None;
}
