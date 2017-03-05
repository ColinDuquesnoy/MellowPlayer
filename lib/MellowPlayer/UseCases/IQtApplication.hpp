#pragma once

#include <MellowPlayer/Macros.hpp>
#include "IMainWindow.hpp"
#include "LocalAlbumArt.hpp"
#include "StreamingServicesManager.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IQtApplication {
public:
    virtual ~IQtApplication() = default;

    virtual int run() = 0;
    virtual void quit() = 0;
    virtual QIcon getWindowIcon() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
