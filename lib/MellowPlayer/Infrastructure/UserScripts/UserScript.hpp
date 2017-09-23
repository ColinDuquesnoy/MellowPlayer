#pragma once

#include <MellowPlayer/Application/UserScripts/UserScriptBase.hpp>

namespace MellowPlayer::Infrastructure
{

    class UserScriptDirectory
    {
    public:
        QString path() const;
        bool create() const;
        QString generateFileName() const;
    };

    class UserScript : public Application::UserScriptBase
    {
    public:
        bool import(const QString& sourcePath) override;
        bool load(const QString& path) override;
    };
}
