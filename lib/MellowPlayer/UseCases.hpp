#pragma once

#include "UseCases/LocalAlbumArt.hpp"
#include "UseCases/PluginManager.hpp"

#include "UseCases/Interfaces/IApplicationSettings.hpp"
#include "UseCases/Interfaces/IQtApplication.hpp"
#include "UseCases/Interfaces/IAlbumArtDownloader.hpp"
#include "UseCases/Interfaces/IMainWindow.hpp"
#include "UseCases/Interfaces/IPluginLoader.hpp"
#include "UseCases/Interfaces/ISystemTrayIcon.hpp"

#include "UseCases/Player/IPlayer.hpp"
#include "UseCases/Player/Player.hpp"
#include "UseCases/Player/PlayerProxy.hpp"
#include "UseCases/Player/PlayersManager.hpp"

#include "UseCases/Services/IService.hpp"
#include "UseCases/Services/IHotkeysService.hpp"
#ifdef Q_OS_LINUX
#include "UseCases/Services/IMprisService.hpp"
#endif
