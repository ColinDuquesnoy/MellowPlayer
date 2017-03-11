#pragma once

#include "Infrastructure/AlbumArtDownloader.hpp"
#include "Infrastructure/ApplicationSettings.hpp"
#include "Infrastructure/PluginLoader.hpp"
#include "Infrastructure/Applications/Application.hpp"
#include "Infrastructure/Applications/IApplication.hpp"
#include "Infrastructure/Applications/SingleInstanceApplication.hpp"
#include "Infrastructure/Logging/SpdLogger.hpp"
#include "Infrastructure/Logging/SpdLoggerFactory.hpp"
#include "Infrastructure/Services/HotkeysService.hpp"
#include "Infrastructure/System/FileHelper.hpp"

#ifdef Q_OS_LINUX
#include "Infrastructure/Applications/LinuxApplication.hpp"
#include "Infrastructure/Services/MprisService.hpp"
#endif
