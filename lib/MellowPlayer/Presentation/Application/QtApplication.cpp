#include "QtApplication.hpp"
#include <QtWebEngine>
#include <QtQuickControls2/QQuickStyle>

using namespace std;
using namespace MellowPlayer::Presentation;

QtApplication::QtApplication(int argc, char** argv)
        : qApplication_(argc, argv)
{
    connect(&qApplication_, &QApplication::aboutToQuit, this, &QtApplication::aboutToQuit);
    connect(&qApplication_, &QApplication::commitDataRequest, this, &QtApplication::commitDataRequest);

    QQuickStyle::setStyle("Material");
    QtWebEngine::initialize();
}

void QtApplication::setApplicationName(QString name)
{
    qApplication_.setApplicationName(name);
}

void QtApplication::setApplicationDisplayName(QString displayName)
{
    qApplication_.setApplicationDisplayName(displayName);
}

void QtApplication::setApplicationVersion(QString version)
{
    qApplication_.setApplicationVersion(version);
}

void QtApplication::setOrganizationDomain(QString domain)
{
    qApplication_.setOrganizationDomain(domain);
}

void QtApplication::setOrganizationName(QString name)
{
    qApplication_.setOrganizationName(name);
}

void QtApplication::setWindowIcon(const QIcon& icon)
{
    qApplication_.setWindowIcon(icon);
}

int QtApplication::exec()
{
    return qApplication_.exec();
}

void QtApplication::exit(int returnCode)
{
    qApplication_.exit(returnCode);
}

void QtApplication::installTranslator(QTranslator* translator)
{
    qApplication_.installTranslator(translator);
}

void QtApplication::setFont(const QFont& font)
{
    qApplication_.setFont(font);
}
