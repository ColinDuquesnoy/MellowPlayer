#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Application/Updater/Updater.hpp>

namespace MellowPlayer::Presentation {

    class UpdaterViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(bool visible READ isVisible NOTIFY visibleChanged)
        Q_PROPERTY(bool canInstall READ canInstall NOTIFY canInstallChanged)
        Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)
    public:
        UpdaterViewModel(Application::Updater& updater);

        bool isVisible() const;
        bool canInstall() const;
        int getProgress() const;

        Q_INVOKABLE void close();
        Q_INVOKABLE void check();
        void install();

    signals:
        void visibleChanged();
        void canInstallChanged();
        void progressChanged();

    private slots:
        void setVisible(bool visible);
        void setCanInstall(bool canInstall);
        void setProgress(int progress);
        void onUpdateAvailable();

    private:
        Application::Updater& updater_;
        bool visible_ = false;
        bool canInstall_ = false;
        int progress_ = -1;
    };
}
