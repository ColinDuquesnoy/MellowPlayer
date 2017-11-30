#include "MainWindow.hpp"
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>

using namespace MellowPlayer::Presentation;

MainWindow::MainWindow(IContextProperties& contextProperties, IQmlApplicationEngine& qmlApplicationEngine)
        : ContextProperty(contextProperties),
          qmlApplicationEngine_(qmlApplicationEngine),
          visible_(false)
{

}

QString MainWindow::name() const
{
    return "_window";
}

QObject* MainWindow::asQObject()
{
    return this;
}

void MainWindow::show()
{
    setVisible(true);
}

void MainWindow::load()
{
    qmlApplicationEngine_.addImportPath("qrc:/MellowPlayer/Presentation/Views");
    qmlApplicationEngine_.load(QUrl("qrc:/MellowPlayer/Presentation/Views/main.qml"));
}

void MainWindow::hide()
{
    setVisible(false);
}

bool MainWindow::isVisible() const
{
    return visible_;
}

void MainWindow::setVisible(bool visible)
{
    if (visible_ != visible)
    {
        visible_ = visible;
        emit visibleChanged();
    }
}
