#pragma once

#include "UseCases/Interfaces/IApplicationSettings.hpp"
#include "UseCases/Interfaces/IQtApplication.hpp"
#include "UseCases/Interfaces/IAlbumArtDownloader.hpp"
#include "UseCases/Interfaces/IMainWindow.hpp"
#include "UseCases/Interfaces/IPlayer.hpp"
#include "UseCases/Interfaces/IStreamingServicesLoader.hpp"
#include "UseCases/Interfaces/ISystemTrayIcon.hpp"

#include "UseCases/Core/LocalAlbumArt.hpp"
#include "UseCases/Core/Player.hpp"
#include "UseCases/Core/PlayerProxy.hpp"
#include "UseCases/Core/StreamingService.hpp"
#include "UseCases/Core/StreamingServicesManager.hpp"

#include "UseCases/Services/IService.hpp"
#include "UseCases/Services/IHotkeysService.hpp"
#ifdef Q_OS_LINUX
#include "UseCases/Services/IMprisService.hpp"
#endif