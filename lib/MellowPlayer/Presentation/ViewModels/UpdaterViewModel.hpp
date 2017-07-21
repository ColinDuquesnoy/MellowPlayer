#pragma once

#include <MellowPlayer/Application/Updater/Updater.hpp>
#include <QtCore/QObject>

namespace MellowPlayer::Presentation
{
    class UpdaterViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString url READ getUrl CONSTANT)
        Q_PROPERTY(QString status READ getStatusString NOTIFY statusChanged)
        Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)
        Q_PROPERTY(bool visible READ isVisible NOTIFY visibleChanged)
        Q_PROPERTY(bool installEnabled READ isInstallEnabled NOTIFY installEnabledChanged)
        Q_PROPERTY(bool restartEnabled READ isRestartEnabled NOTIFY restartEnabledChanged)
        Q_PROPERTY(double progress READ getProgress NOTIFY progressChanged)
    public:
        UpdaterViewModel(Application::Updater &updater);

        QString getUrl() const;
        QString getStatusString() const;
        bool isBusy() const;
        bool isVisible() const;
        bool isInstallEnabled() const;
        bool isRestartEnabled() const;
        double getProgress() const;

        Q_INVOKABLE void close();
        Q_INVOKABLE void check();
        Q_INVOKABLE void install();
        Q_INVOKABLE void restart();

    signals:
        void visibleChanged();
        void installEnabledChanged();
        void restartEnabledChanged();
        void progressChanged();
        void statusChanged();
        void busyChanged();

    private slots:
        void setVisible(bool visible);
        void setInstallEnabled(bool enabled);
        void setRestartEnabled(bool enabled);
        void setProgress(double progress);
        void onUpdateAvailable();
        void onNoUpdateAvailable();
        void onProgressUpdated(double progress);
        void onInstalled();

    private:
        Application::Updater &updater_;
        bool visible_ = false;
        bool installEnabled_ = false;
        bool restartEnabled_ = false;
        double progress_ = -1;
    };
}
