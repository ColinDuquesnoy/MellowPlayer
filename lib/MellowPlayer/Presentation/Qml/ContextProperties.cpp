#include "ContextProperties.hpp"
#include "IContextProperty.hpp"
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>

using namespace MellowPlayer::Presentation;

ContextProperties::ContextProperties(IQmlApplicationEngine& qmlApplicationEngine)
        : qmlApplicationEngine_(qmlApplicationEngine)
{

}

void ContextProperties::add(IContextProperty& contextProperty)
{
    qmlApplicationEngine_.setContextProperty(contextProperty.name(), contextProperty.asQObject());
}
