#pragma once

#include "Infrastructure/Applications/Application.hpp"
#include "Infrastructure/Applications/IApplication.hpp"
#include "Infrastructure/Applications/SingleInstanceApplication.hpp"
#include "Infrastructure/Logging/SpdLogger.hpp"
#include "Infrastructure/Logging/SpdLoggerFactory.hpp"
#include "Infrastructure/Services/HotkeysService.hpp"
#include "Infrastructure/System/AlbumArtDownloader.hpp"
#include "Infrastructure/System/FileHelper.hpp"
#include "Infrastructure/System/StreamingServicesLoader.hpp"

#ifdef Q_OS_LINUX
#include "Infrastructure/Applications/LinuxApplication.hpp"
#include "Infrastructure/Services/MprisService.hpp"
#endif
