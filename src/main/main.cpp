#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char * argv[])
{
    QGuiApplication qtApp(argc, argv);
    QQmlApplicationEngine qmlApplicationEngine;

    return qtApp.exec();
}
