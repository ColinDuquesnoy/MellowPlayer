#pragma once

#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Infrastructure/System/IIniFile.hpp>

namespace MellowPlayer::Infrastructure
{
    class PluginMetadata: public Domain::PluginMetadata
    {
    public:
        PluginMetadata(IFactory<IIniFile, QString>& iniFileFactory, const QString& path);

        void load() override;
    private:
        IFactory<IIniFile, QString>& iniFileFactory_;
        QString path_;
    };
}
