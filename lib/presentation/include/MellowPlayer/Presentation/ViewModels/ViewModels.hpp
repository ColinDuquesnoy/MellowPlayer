#pragma once

#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include "ApplicationViewModel.hpp"
#include "MainWindowViewModel.hpp"
#include "ClipBoardViewModel.hpp"
#include "DevToolsWindowViewModel.hpp"
#include "ThemeViewModel.hpp"
#include "UpdaterViewModel.hpp"
#include "ListeningHistory/ListeningHistoryViewModel.hpp"
#include "Settings/SettingsViewModel.hpp"
#include "CookiesViewModel.hpp"
#include "CacheViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class IViewModels
    {
    public:
        virtual ~IViewModels() = default;
        virtual void initialize() = 0;
        virtual void cleanup() = 0;
    };

    class ViewModels: public IViewModels
    {
    public:
        ViewModels(ApplicationViewModel& application,
                   IMainWindow& mainWindow,
                   SettingsViewModel& settings,
                   ThemeViewModel& theme,
                   UpdaterViewModel& updater,
                   ListeningHistoryViewModel& listeningHistory,
                   StreamingServicesViewModel& streamingServices,
                   IContextProperties& contextProperties);

        void initialize() override;
        void cleanup() override;

    private:
        IMainWindow& mainWindow_;
        UpdaterViewModel& updater_;
        ListeningHistoryViewModel& listeningHistory_;
        StreamingServicesViewModel& streamingServices_;
        CacheViewModel cache_;
        CookiesViewModel cookies_;
        ClipBoardViewModel clipboard_;
        DevToolsWindowViewModel devToolsWindow_;
    };
}
