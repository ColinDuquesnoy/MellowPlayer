#pragma once

#include <QString>
#include <QObject>

class BuildConfigStrings: public QObject
{
    Q_OBJECT
public:
    QString builtOnStr() const
    {
        return tr("Built on %1 at %2 (%3, %4 bit) with Qt %5");
    }
};

namespace MellowPlayer::Infrastructure
{
    class BuildConfig
    {
    public:
        static QString getVersion();
        static int getVersionMajor();
        static int getVersionMinor();
        static int getVersionPatch();
        static int getVersionBuildNumber();
        static QString getDefaultTheme();
        static QString getBuildDate();
        static QString getSourceDir();
        static QString buildInfo();

    };
}
