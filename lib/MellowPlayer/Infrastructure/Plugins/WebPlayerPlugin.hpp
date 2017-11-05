#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Domain/Plugins/WebPlayerPlugin.hpp>
#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include <MellowPlayer/Infrastructure/System/IFile.hpp>
#include <MellowPlayer/Infrastructure/System/IIniFile.hpp>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
}

namespace MellowPlayer::Infrastructure
{
    class WebPlayerPlugin: public Domain::WebPlayerPlugin
    {
    public:
        WebPlayerPlugin(const QString& path,
                        IFactory<IFile, QString>& fileFactory,
                        IFactory<IIniFile, QString>& iniFileFactory,
                        Domain::ISettingsStore& settingsStore);
        void load() override;

    private:
        void loadIntegrationScript();
        void loadMetadata();
        void loadUrl();
        QString customUrlSettingsKey() const;
        QString isEnabledSettingsKey() const;
        QString filePath(const QString& fileName) const;

        IFactory<IFile, QString>& fileFactory_;
        IFactory<IIniFile, QString>& iniFileFactory_;
        Domain::ISettingsStore& settingsStore_;
    };
}