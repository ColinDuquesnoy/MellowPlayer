#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <QQmlContext>

using namespace MellowPlayer::Presentation;

void QmlApplicationEngine::setContextProperty(const QString& name, QObject* object)
{
    engine_.rootContext()->setContextProperty(name, object);
}

void QmlApplicationEngine::addImportPath(const QString& path)
{
    engine_.addImportPath(path);
}

void QmlApplicationEngine::load(const QUrl& url)
{
    engine_.load(url);
}
