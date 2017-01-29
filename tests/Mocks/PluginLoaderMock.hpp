#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Plugins/IPluginLoader.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

class PluginLoaderMock{
public:
    static fakeit::Mock<MellowPlayer::UseCases::IPluginLoader> basicMock();
};
