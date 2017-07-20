#include <QtCore/QMap>
#include "UpdaterStatusConverter.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

const QString UpdaterStatusConverter::NONE = "";
const QString UpdaterStatusConverter::CHECKING = QObject::tr("Checking for update");
const QString UpdaterStatusConverter::DOWNLOADING = QObject::tr("Downloading update");
const QString UpdaterStatusConverter::INSTALLING = QObject::tr("Installing update");

QString UpdaterStatusConverter::toString(Updater::Status status) {
    static QMap<Updater::Status, QString> map = {
            { Updater::Status::None,        NONE },
            { Updater::Status::Checking,    CHECKING },
            { Updater::Status::Downloading, DOWNLOADING },
            { Updater::Status::Installing,  INSTALLING }
    };

    return map[status];
}

Updater::Status UpdaterStatusConverter::fromString(const QString& string) {
    static QMap<QString, Updater::Status> map = {
            { NONE,        Updater::Status::None },
            { CHECKING,    Updater::Status::Checking },
            { DOWNLOADING, Updater::Status::Downloading },
            { INSTALLING,  Updater::Status::Installing }
    };

    if (map.contains(string))
        return map[string];
    return Updater::Status::None;
}
