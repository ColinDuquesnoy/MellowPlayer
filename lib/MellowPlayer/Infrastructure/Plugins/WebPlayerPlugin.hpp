#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Domain/Plugins/WebPlayerPlugin.hpp>
#include <MellowPlayer/Infrastructure/System/IFile.hpp>
#include <MellowPlayer/Infrastructure/System/IIniFile.hpp>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
}

namespace MellowPlayer::Infrastructure
{
    class IFileFactory;
    class IIniFileFactory;

    class WebPlayerPlugin: public Domain::WebPlayerPlugin
    {
    public:
        WebPlayerPlugin(const QString& path,
                        IFileFactory& fileFactory,
                        IIniFileFactory& iniFileFactory,
                        Domain::ISettingsStore& settingsStore);
        void load() override;

    private:
        void loadIntegrationScript();
        void loadMetadata();
        QString customUrlSettingsKey() const;
        QString isEnabledSettingsKey() const;
        QString filePath(const QString& fileName) const;

        IFileFactory& fileFactory_;
        IIniFileFactory& iniFileFactory_;
        Domain::ISettingsStore& settingsStore_;
    };
}