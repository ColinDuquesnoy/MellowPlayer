#include "MainWindowViewModel.hpp"
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>

using namespace MellowPlayer::Presentation;

MainWindowViewModel::MainWindowViewModel(IContextProperties& contextProperties,
                                         IQmlApplicationEngine& qmlApplicationEngine)
        : ContextProperty("_window", this, contextProperties),
          qmlApplicationEngine_(qmlApplicationEngine),
          visible_(false)
{

}

void MainWindowViewModel::show()
{
    setVisible(true);
}

void MainWindowViewModel::load()
{
    qmlApplicationEngine_.addImportPath("qrc:/MellowPlayer/Presentation/Views");
    qmlApplicationEngine_.load(QUrl("qrc:/MellowPlayer/Presentation/Views/main.qml"));
}

void MainWindowViewModel::hide()
{
    setVisible(false);
}

bool MainWindowViewModel::isVisible() const
{
    return visible_;
}

void MainWindowViewModel::setVisible(bool visible)
{
    if (visible_ != visible)
    {
        visible_ = visible;
        emit visibleChanged();
    }
}

void MainWindowViewModel::requestQuit()
{
    emit quitRequest();
}
