#pragma once

#include <MellowPlayer/Domain/IDeprecatedQtApplication.hpp>
#include <QApplication>
#include <QTranslator>

#define MELLOWPLAYER_APP_NAME "MellowPlayer"

class AppStrings : public QObject
{
    Q_OBJECT
public:
    QString builtOnStr() const
    {
        return tr("Built on %1 at %2 (%3, %4 bit) with Qt %5");
    }
};

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Presentation
{
    class DeprecatedApplicationViewModel : public Domain::IDeprecatedQtApplication
    {
        Q_OBJECT
    public:
        DeprecatedApplicationViewModel(int& argc, char** argv, const QString& appName = MELLOWPLAYER_APP_NAME);

        void initialize() override;
        int run() override;
        Q_INVOKABLE void clearCache() const override;
        Q_INVOKABLE void clearCookies() const override;
        Q_INVOKABLE void restart() override;
        Q_INVOKABLE void requestQuit() override;
        Q_INVOKABLE void quit() override;

        QString buildInfo() const override;

        void setAutoQuitDelay(int delay);

        bool restartRequested() const override;

    signals:
        void forceQuitRequested();

    private:
        void onAboutToQuit();

        QApplication qtApp_;
        QTranslator translator_;
        bool restartRequested_ = false;
    };
}
