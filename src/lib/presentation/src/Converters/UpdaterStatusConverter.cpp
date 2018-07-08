#include <MellowPlayer/Presentation/Converters/UpdaterStatusConverter.hpp>
#include <QtCore/QMap>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

QString UpdaterStatusConverter::toString(Updater::Status status)
{
    static QMap<Updater::Status, QString> map = {{Updater::Status::None, strings_.none()},
                                                 {Updater::Status::Checking, strings_.checking()},
                                                 {Updater::Status::UpdateAvailable, strings_.updateAvailable()},
                                                 {Updater::Status::Downloading, strings_.downloading()},
                                                 {Updater::Status::Installing, strings_.installing()},
                                                 {Updater::Status::Installed, strings_.installed()},
                                                 {Updater::Status::Failure, strings_.failure()}};

    return map[status];
}

Updater::Status UpdaterStatusConverter::fromString(const QString& string)
{
    static QMap<QString, Updater::Status> map = {{strings_.none(), Updater::Status::None},
                                                 {strings_.checking(), Updater::Status::Checking},
                                                 {strings_.updateAvailable(), Updater::Status::UpdateAvailable},
                                                 {strings_.downloading(), Updater::Status::Downloading},
                                                 {strings_.installing(), Updater::Status::Installing},
                                                 {strings_.installed(), Updater::Status::Installed},
                                                 {strings_.failure(), Updater::Status::Failure}};

    if (map.contains(string))
        return map[string];
    return Updater::Status::None;
}
