#pragma once

#include <QObject>
#include <QtDBus>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Mpris2Root : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2")
public:
    Q_PROPERTY(bool CanRaise READ canRaise)
    Q_PROPERTY(bool CanQuit READ canQuit)
    Q_PROPERTY(bool HasTrackList READ hasTrackList)
    Q_PROPERTY(bool CanSetFullscreen READ canSetFullscreen)
    Q_PROPERTY(bool Fullscreen READ fullscreen WRITE setFullscreen)
    Q_PROPERTY(QString Identity READ identity)
    Q_PROPERTY(QString DesktopEntry READ desktopEntry)
    Q_PROPERTY(QStringList SupportedUriSchemes READ supportedUriSchemes)
    Q_PROPERTY(QStringList SupportedMimeTypes READ supportedMimeTypes)

    Mpris2Root(UseCases::IMainWindow& window, UseCases::IQtApplication& qtApp, QObject *parent=nullptr);

    bool canRaise();
    bool canQuit();
    bool hasTrackList();
    bool canSetFullscreen();
    bool fullscreen();
    void setFullscreen(bool value);
    QString identity();
    QString desktopEntry();
    QStringList supportedUriSchemes();
    QStringList supportedMimeTypes();


public slots:
    void Raise();
    void Quit();

private:
    UseCases::ILogger& logger;
    UseCases::IMainWindow& window;
    UseCases::IQtApplication& qtApp;
};

END_MELLOWPLAYER_NAMESPACE
