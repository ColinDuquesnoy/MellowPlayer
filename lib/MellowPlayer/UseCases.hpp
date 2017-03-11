#pragma once

#include "UseCases/Interfaces/IApplicationSettings.hpp"
#include "UseCases/Interfaces/IQtApplication.hpp"
#include "UseCases/Interfaces/IAlbumArtDownloader.hpp"
#include "UseCases/Interfaces/IMainWindow.hpp"
#include "UseCases/Interfaces/IPluginLoader.hpp"
#include "UseCases/Interfaces/ISystemTrayIcon.hpp"

#include "UseCases/Logging/LoggerConfig.hpp"
#include "UseCases/Logging/ILogger.hpp"
#include "UseCases/Logging/ILoggerFactory.hpp"
#include "UseCases/Logging/LoggingMacros.hpp"
#include "UseCases/Logging/LoggingManager.hpp"

#include "UseCases/Player/IPlayer.hpp"
#include "UseCases/Player/Player.hpp"
#include "UseCases/Player/PlayerProxy.hpp"
#include "UseCases/Player/PlayersManager.hpp"
#include "UseCases/Player/Song.hpp"

#include "UseCases/Plugin/Plugin.hpp"
#include "UseCases/Plugin/PluginManager.hpp"
#include "UseCases/Plugin/PluginMetadata.hpp"
#include "UseCases/Plugin/PluginScript.hpp"

#include "UseCases/Services/LocalAlbumArtService.hpp"
#include "UseCases/Services/IHotkeysService.hpp"
#ifdef Q_OS_LINUX
#include "UseCases/Services/IMprisService.hpp"
#endif
