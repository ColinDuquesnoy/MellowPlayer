#pragma once

#include <QString>

namespace MellowPlayer::Infrastructure
{
    class FileHelper
    {
    public:
        static QString createLogDirectory();
        static QString appDataDirectory();
        static QString userScriptsDirectory();
        static QString logDirectory();
    };
}