#pragma once

#include <QObject>
#include <MellowPlayer/Domain/Macros.hpp>

namespace MellowPlayer::Domain
{
    class PluginMetadata: public QObject
    {
        Q_OBJECT
        READONLY_PROPERTY(QString, author, updateAuthor)
        READONLY_PROPERTY(QString, authorUrl, updateAuthorUrl)
        READONLY_PROPERTY(QString, logo, updateLogo)
        READONLY_PROPERTY(QString, name, updateName)
        READONLY_PROPERTY(QString, version, updateVersion)
    public:
        PluginMetadata();
    };
}
