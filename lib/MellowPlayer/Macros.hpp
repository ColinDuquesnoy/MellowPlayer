#pragma once

#define BEGIN_MELLOWPLAYER_NAMESPACE(n) namespace MellowPlayer { namespace n {
#define END_MELLOWPLAYER_NAMESPACE }}
#define USING_MELLOWPLAYER_NAMESPACE(n) using namespace MellowPlayer::n;

#define PREDECLARE_MELLOWPLAYER_CLASS(n, name) namespace MellowPlayer { namespace n { class name; } }
#define PREDECLARE_MELLOWPLAYER_STRUCT(n, name) namespace MellowPlayer { namespace n { struct name; } }
#define PREDECLARE_MELLOWPLAYER_ENUM(n, name) namespace MellowPlayer { namespace n { enum class name; } }