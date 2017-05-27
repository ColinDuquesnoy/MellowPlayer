#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IQtApplication: public QObject {
    Q_OBJECT
public:
    virtual ~IQtApplication();

    virtual int run() = 0;
    Q_INVOKABLE virtual void clearCache() const = 0;
    Q_INVOKABLE virtual void clearCookies() const = 0;
    Q_INVOKABLE virtual void requestQuit() = 0;
    Q_INVOKABLE virtual void restart() = 0;
    Q_INVOKABLE virtual void quit() = 0;

signals:
    void quitRequested();
};

END_MELLOWPLAYER_NAMESPACE
