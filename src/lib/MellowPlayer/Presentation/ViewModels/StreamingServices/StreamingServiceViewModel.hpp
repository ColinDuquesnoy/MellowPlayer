#pragma once

#include <QtCore/QObject>
#include <memory>
#include <MellowPlayer/Domain/Properties.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptsViewModel.hpp>


namespace MellowPlayer::Domain
{
    class ISettingsStore;
    class IUserScriptFactory;
    class StreamingService;
    class Player;
    class Players;
}

namespace MellowPlayer::Infrastructure
{
    class NetworkProxy;
    class INetworkProxies;
}

namespace MellowPlayer::Presentation
{
    class StreamingServiceViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString logo READ logo CONSTANT)
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(Domain::Player* player READ player CONSTANT)
        Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
        Q_PROPERTY(QString version READ version CONSTANT)
        Q_PROPERTY(QString authorName READ authorName CONSTANT)
        Q_PROPERTY(QString authorWebsite READ authorWebsite CONSTANT)
        Q_PROPERTY(bool isEnabled READ isEnabled WRITE setEnabled NOTIFY isEnabledChanged)
        Q_PROPERTY(int sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
        Q_PROPERTY(QObject* userScripts READ userScripts CONSTANT)
        Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor NOTIFY zoomFactorChanged)
        Q_PROPERTY(bool notificationsEnabled READ notificationsEnabled WRITE setNotificationsEnabled NOTIFY notificationsEnabledChanged)
        Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)
        Q_PROPERTY(QString previewImageUrl READ previewImageUrl WRITE setPreviewImageUrl NOTIFY previewImageUrlChanged)
        Q_PROPERTY(QString sourceCode READ sourceCode NOTIFY sourceCodeChanged)

        CONSTANT_OBJECT_PROPERTY(Infrastructure::NetworkProxy, networkProxy)

    public:
        StreamingServiceViewModel(Domain::StreamingService& streamingService,
                                  Domain::ISettingsStore& settingsStore,
                                  Domain::IUserScriptFactory& userScriptFactory,
                                  Domain::Players& players,
                                  Infrastructure::INetworkProxies& networkProxies,
                                  QObject* parent = nullptr);

        QString logo() const;
        QString name() const;
        Domain::Player* player();
        QString url() const;
        QString version() const;
        QString authorName() const;
        QString authorWebsite() const;

        bool operator==(const StreamingServiceViewModel& rhs) const;
        bool operator!=(const StreamingServiceViewModel& rhs) const;

        Domain::StreamingService* streamingService() const;

        int sortOrder() const;
        void setSortOrder(int newOrder);

        bool isEnabled() const;
        void setEnabled(bool enabled);

        QObject* userScripts();

        int zoomFactor() const;
        void setZoomFactor(int zoomFactor);

        bool notificationsEnabled() const;
        void setNotificationsEnabled(bool value);

        bool isActive() const;

        QString previewImageUrl() const;
        QString sourceCode() const;

    public slots:
        void setUrl(const QString& newUrl);
        void setActive(bool isActive);

        void setPreviewImageUrl(QString previewImageUrl);

    signals:
        void urlChanged(const QString&);
        void sortOrderChanged();
        void isEnabledChanged();
        void zoomFactorChanged();
        void notificationsEnabledChanged();
        void isActiveChanged();
        void previewImageUrlChanged();
        void sourceCodeChanged();

    private:
        QString customUrlSettingsKey() const;
        QString sortOrderSettingsKey() const;
        QString isEnabledSettingsKey() const;
        QString zoomFactorSettingsKey() const;
        QString notificationsEnabledSettingsKey() const;

        Domain::StreamingService& streamingService_;
        Domain::ISettingsStore& settingsStore_;
        std::shared_ptr<Domain::Player> player_;
        UserScriptsViewModel userScriptsViewModel_;
        int zoomFactor_;
        bool isActive_;
        QString previewImageUrl_;
    };
}
