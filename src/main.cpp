#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char * argv[])
{
    QGuiApplication qtApp(argc, argv);
    QQmlApplicationEngine qmlApplicationEngine;
    qmlApplicationEngine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return qtApp.exec();
}
