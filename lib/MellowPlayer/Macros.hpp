#pragma once

#define BEGIN_MELLOWPLAYER_NAMESPACE(subNamespace) namespace MellowPlayer { namespace subNamespace {
#define END_MELLOWPLAYER_NAMESPACE }}
#define USE_MELLOWPLAYER_NAMESPACE(subNamespace) using namespace MellowPlayer::subNamespace;

namespace MellowPlayer {

class NonCopyable {
protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;
    NonCopyable(NonCopyable &) = delete;
    NonCopyable(NonCopyable &&) = delete;
    void operator=(NonCopyable &) = delete;
    void operator=(NonCopyable &&) = delete;
};

}
