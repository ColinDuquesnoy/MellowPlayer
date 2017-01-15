#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>

int main(int argc, char * argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication qtApp(argc, argv);

    QtWebEngine::initialize();

    QQmlApplicationEngine qmlApplicationEngine;    
    qmlApplicationEngine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return qtApp.exec();
}
