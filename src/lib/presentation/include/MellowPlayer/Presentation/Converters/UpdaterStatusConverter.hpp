#pragma once

#include <QObject>
#include <QString>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>

class UpdaterStatusStrings : public QObject
{
    Q_OBJECT
public:
    QString none() const
    {
        return tr("");
    };
    QString checking() const
    {
        return tr("Checking for update...");
    };
    QString updateAvailable() const
    {
        return tr("An update is available...");
    };
    QString downloading() const
    {
        return tr("Downloading update...");
    };
    QString installing() const
    {
        return tr("Installing update...");
    };
    QString installed() const
    {
        return tr("Update installed, you can now restart the application...");
    };
    QString failure() const
    {
        return tr("Failed to install update, check logs for warning and errors and try again...");
    };
};

namespace MellowPlayer::Presentation
{
    class UpdaterStatusConverter
    {
    public:
        QString toString(Infrastructure::Updater::Status status);
        Infrastructure::Updater::Status fromString(const QString& string);

    private:
        UpdaterStatusStrings strings_;
    };
}
