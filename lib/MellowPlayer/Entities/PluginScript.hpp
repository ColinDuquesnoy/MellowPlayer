#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Logging.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

class PluginScript: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString code READ getCode NOTIFY codeChanged);
    Q_PROPERTY(QString path READ getPath CONSTANT);
public:
    PluginScript(const QString& code, const QString& path);

    bool isValid() const;

    const QString& getCode() const;
    void setCode(const QString& value);

    const QString& getPath() const;

    Q_INVOKABLE QString updatePlayerInfo() const;
    Q_INVOKABLE QString updateSongInfo() const;
    Q_INVOKABLE QString play() const;
    Q_INVOKABLE QString pause() const;
    Q_INVOKABLE QString next() const;
    Q_INVOKABLE QString previous() const;
    Q_INVOKABLE QString setVolume(int volume) const;
    Q_INVOKABLE QString addToFavorites() const;
    Q_INVOKABLE QString removeFromFavorites() const;
    Q_INVOKABLE QString seekToPosition(int position) const;

signals:
    void codeChanged(QString);

private:
    Logging::ILogger& logger;
    QString code;
    QString path;
};

END_MELLOWPLAYER_NAMESPACE
