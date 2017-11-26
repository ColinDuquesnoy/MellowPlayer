#include "Application.hpp"
#include "MellowPlayer/Presentation/IconProvider.hpp"
#include <MellowPlayer/Domain/BuildConfig.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <QtCore/QDirIterator>
#include <QtCore/QProcess>
#include <QtCore/QStandardPaths>
#include <QtGui/QFontDatabase>
#include <QtWebEngineWidgets/QWebEngineProfile>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

Application::Application(IQtApplication& qtApplication, IContextProperties& contextProperties)
        : ContextProperty(contextProperties), qtApp_(qtApplication)
{
    qtApp_.setApplicationName("MellowPlayer");
    qtApp_.setApplicationDisplayName("MellowPlayer");
    qtApp_.setApplicationVersion(BuildConfig::getVersion());
    qtApp_.setOrganizationDomain("org.mellowplayer");
    qtApp_.setOrganizationName("MellowPlayer");
    qtApp_.setWindowIcon(IconProvider::windowIcon());

    connect(&qtApp_, &IQtApplication::commitDataRequest, this, &Application::commitDataRequest);
}

QString Application::name() const
{
    return "_application";
}

QObject* Application::asQObject()
{
    return this;
}

void Application::initialize()
{
    setupFont();
    registerMetaTypes();
    setupTranslations();
    emit initialized();
}

int Application::run()
{
    emit started();
    auto returnCode = qtApp_.exec();

    if (restartRequested_)
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    return returnCode;
}

void Application::quit()
{
    qtApp_.exit(0);
}

void Application::restart()
{
    restartRequested_ = true;
    quit();
}

void Application::restoreWindow()
{
    emit restoreWindowRequest();
}

void Application::setupFont()
{
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-BlackItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Italic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-LightItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-MediumItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-ThinItalic.ttf");
    qtApp_.setFont(QFont("Roboto"));
}

void Application::registerMetaTypes()
{
    qRegisterMetaType<Song*>("Domain::Song*");
    qRegisterMetaType<Song*>("Song*");
    qRegisterMetaType<StreamingService*>("Domain::StreamingService*");
    qRegisterMetaType<StreamingService*>("StreamingService*");
    qRegisterMetaType<ListeningHistoryEntry>("Domain::ListeningHistoryEntry");
    qRegisterMetaType<ListeningHistoryEntry>("ListeningHistoryEntry");
    qRegisterMetaType<Player*>("Domain::Player*");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<SettingViewModel*>("Presentation::SettingViewModel*");
    qRegisterMetaType<SettingViewModel*>("SettingViewModel*");
}

void Application::setupTranslations()
{
    if (!translator_.load(QLocale(), "MellowPlayer", "_", ":/MellowPlayer/Translations")) {
        qWarning() << "failed to load translation: " << QLocale::system().name();
        qInfo() << "available translations: ";
        QDirIterator it(":/MellowPlayer/Translations", QStringList() << "*.qm", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
            qInfo() << "  - " << it.next();
    } else
        qInfo() << "translation successfully loaded: " << QLocale::system().name();

    qtApp_.installTranslator(&translator_);
}

void Application::requestQuit()
{
    emit quitRequest();
}
