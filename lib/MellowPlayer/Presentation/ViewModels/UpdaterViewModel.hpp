#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Application/Updater/Updater.hpp>

namespace MellowPlayer::Presentation {

    class UpdaterViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(QString message READ getMessage NOTIFY messageChanged)
        Q_PROPERTY(QString url READ getUrl CONSTANT)
        Q_PROPERTY(QString status READ getStatusString NOTIFY statusChanged)
        Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)
        Q_PROPERTY(bool visible READ isVisible NOTIFY visibleChanged)
        Q_PROPERTY(bool installEnabled READ isInstallEnabled NOTIFY installEnabledChanged)
        Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)
    public:
        UpdaterViewModel(Application::Updater& updater);

        QString getMessage() const;
        QString getUrl() const;
        QString getStatusString() const;
        bool isBusy() const;
        bool isVisible() const;
        bool isInstallEnabled() const;
        int getProgress() const;

        Q_INVOKABLE void close();
        Q_INVOKABLE void check();
        Q_INVOKABLE void install();

    signals:
        void messageChanged();
        void visibleChanged();
        void installEnabledChanged();
        void progressChanged();
        void statusChanged();
        void busyChanged();

    private slots:
        void setMessage(const QString& message);
        void setVisible(bool visible);
        void setInstallEnabled(bool enabled);
        void setProgress(int progress);
        void onUpdateAvailable();
        void onNoUpdateAvailable();
        void updateMessage();

    private:
        Application::Updater& updater_;
        QString message_;
        bool visible_ = false;
        bool installEnabled_ = false;
        int progress_ = -1;
        bool progressVisible_ = false;
    };
}
