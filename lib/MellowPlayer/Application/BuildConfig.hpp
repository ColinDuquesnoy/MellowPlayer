#pragma once

#include <QString>

namespace MellowPlayer::Application
{
    class BuildConfig
    {
    public:
        static QString getVersion();
        static int getVersionMajor();
        static int getVersionMinor();
        static int getVersionPatch();
        static int getVersionBuildNumber();
        static QString getBuildDate();
        static QString getSourceDir();

    };
}
