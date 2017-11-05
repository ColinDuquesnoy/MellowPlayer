#pragma once

#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Infrastructure/System/IIniFile.hpp>

namespace MellowPlayer::Infrastructure
{
    class PluginMetadata: public Domain::PluginMetadata
    {
    public:
        PluginMetadata(const std::shared_ptr<IIniFile>& iniFile);

        void load() override;
    private:
        std::shared_ptr<IIniFile> iniFile_;
    };
}
