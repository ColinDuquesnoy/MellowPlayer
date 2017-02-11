#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/IStreamingServicesLoader.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

class StreamingServiceLoaderMock{
public:
    static fakeit::Mock<MellowPlayer::UseCases::IStreamingServicesLoader> basicMock();
};
