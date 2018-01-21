#include <MellowPlayer/Infrastructure/BuildConfig.hpp>

using namespace MellowPlayer::Infrastructure;

QString BuildConfig::getVersion()
{
    return MELLOWPLAYER_VERSION_STR;
}

int BuildConfig::getVersionMajor()
{
    return MELLOWPLAYER_VERSION_MAJOR;
}

int BuildConfig::getVersionMinor()
{
    return MELLOWPLAYER_VERSION_MINOR;
}

int BuildConfig::getVersionPatch()
{
    return MELLOWPLAYER_VERSION_PATCH;
}

int BuildConfig::getVersionBuildNumber()
{
    return MELLOWPLAYER_VERSION_TWEAK;
}

QString BuildConfig::getBuildDate()
{
    return MELLOWPLAYER_BUILD_DATE;
}

QString BuildConfig::getSourceDir()
{
    return MELLOWPLAYER_SOURCE_DIR;
}

static QString compilerString()
{
#if defined(Q_CC_CLANG) // must be before GNU, because clang claims to be GNU too
    QString isAppleString;
#if defined(__apple_build_version__) // Apple clang has other version numbers
    isAppleString = QLatin1String(" (Apple)");
#endif
    return QLatin1String("Clang ") + QString::number(__clang_major__) + QLatin1Char('.') + QString::number(__clang_minor__) + isAppleString;
#elif defined(Q_CC_GNU)
    return QLatin1String("GCC ") + QLatin1String(__VERSION__);
#elif defined(Q_CC_MSVC)
    if (_MSC_VER >= 1800) // 1800: MSVC 2013 (yearly release cycle)
        return QLatin1String("MSVC ") + QString::number(2008 + ((_MSC_VER / 100) - 13));
    if (_MSC_VER >= 1500) // 1500: MSVC 2008, 1600: MSVC 2010, ... (2-year release cycle)
        return QLatin1String("MSVC ") + QString::number(2008 + 2 * ((_MSC_VER / 100) - 15));
#else
    return QObject::tr("<unknown compiler>");
#endif
}

QString BuildConfig::buildInfo()
{
    return BuildConfigStrings().builtOnStr().arg(
            QString(__DATE__),
            QString(__TIME__),
            compilerString(),
            QString::number(QSysInfo::WordSize),
            QString(QT_VERSION_STR));
}
