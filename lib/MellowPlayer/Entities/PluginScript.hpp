#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

class ILogger;

class PluginScript: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString code READ getCode NOTIFY codeChanged);
    Q_PROPERTY(QString path READ getPath CONSTANT);
public:
    PluginScript(const QString& code, const QString& path);

    bool isValid() const;

    QString getConstants() const;
    QString getCode() const;
    void setCode(const QString& value);

    const QString& getPath() const;

    Q_INVOKABLE QString update() const;
    Q_INVOKABLE QString play() const;
    Q_INVOKABLE QString pause() const;
    Q_INVOKABLE QString next() const;
    Q_INVOKABLE QString previous() const;
    Q_INVOKABLE QString setVolume(double volume) const;
    Q_INVOKABLE QString addToFavorites() const;
    Q_INVOKABLE QString removeFromFavorites() const;
    Q_INVOKABLE QString seekToPosition(double position) const;

signals:
    void codeChanged(QString);

private:
    QString code;
    QString path;
};

END_MELLOWPLAYER_NAMESPACE
