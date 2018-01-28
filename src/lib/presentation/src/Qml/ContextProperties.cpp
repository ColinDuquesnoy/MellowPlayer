#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperty.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <QtQml/QtQml>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ContextProperties::ContextProperties(IQmlApplicationEngine& qmlApplicationEngine, IPlayer& player)
        : qmlApplicationEngine_(qmlApplicationEngine),
          player_(player)
{

}

void ContextProperties::add(IContextProperty& contextProperty)
{
    contextProperties_.append(&contextProperty);
}

void ContextProperties::initialize()
{
    qmlRegisterUncreatableType<Player>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");
    qmlApplicationEngine_.setContextProperty("_player", &player_);

    for(auto* contextProperty: contextProperties_)
        contextProperty->initialize(qmlApplicationEngine_);
}
