#pragma once

#include "StreamingServiceMetadata.hpp"
#include <MellowPlayer/Domain/Theme/Theme.hpp>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <memory>

namespace MellowPlayer::Domain
{
    class StreamingServiceScript;
    class SettingsCategory;

    class StreamingService : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString author READ author CONSTANT)
        Q_PROPERTY(QString authorWebsite READ authorWebsite CONSTANT)
        Q_PROPERTY(QString logo READ logo CONSTANT)
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString url READ url CONSTANT)
        Q_PROPERTY(QString version READ version CONSTANT)
        Q_PROPERTY(StreamingServiceScript* script READ script CONSTANT)
        Q_PROPERTY(SettingsCategory* settings READ settings CONSTANT)
    public:
        StreamingService(const StreamingServiceMetadata& metadata, const Theme& theme = Theme(),
                         const std::shared_ptr<SettingsCategory>& settings=nullptr);
        ~StreamingService();

        bool isValid() const;
        const QString& author() const;
        const QString& authorWebsite() const;
        QString logo() const;
        const QString& name() const;
        QString url() const;
        const QString& version() const;
        StreamingServiceScript* script() const;
        const Theme& theme() const;

        QString pluginDirectory() const;

        void updateTheme(Theme& newTheme);
        void updateScript(const QString& script);

        bool operator==(const StreamingService& rhs) const;
        bool operator!=(const StreamingService& rhs) const;

        SettingsCategory* settings() const;

    signals:
        void scriptChanged();
        void themeChanged();

    private:
        StreamingServiceMetadata metadata_;
        Theme theme_;
        std::shared_ptr<SettingsCategory> _settings;
        std::unique_ptr<StreamingServiceScript> script_;
    };
}
