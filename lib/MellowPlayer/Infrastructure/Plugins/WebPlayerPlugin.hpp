#include <MellowPlayer/Domain/Plugins/WebPlayerPlugin.hpp>
#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include <MellowPlayer/Infrastructure/System/IFile.hpp>

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
                        IFactory<Domain::WebPlayerScript, QString>& webPlayerScriptFactory,
                        Domain::ISettingsStore& settingsStore);
        void load() override;

    private:
        void loadIntegrationScript();
        QString customUrlSettingsKey() const;
        QString isEnabledSettingsKey() const;

        IFactory<Domain::WebPlayerScript, QString>& webPlayerScriptFactory_;
        Domain::ISettingsStore& settingsStore_;
    };
}