#pragma once

#include <MellowPlayer/Domain/Theme/Theme.hpp>
#include <QMap>
#include <QObject>

namespace MellowPlayer::Domain
{
    class StreamingService;
    class StreamingServicesController;
    class Setting;
    class Settings;
    class IThemeLoader;
}

namespace MellowPlayer::Presentation
{
    class ThemeViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool dark READ isDark NOTIFY isDarkChanged)
        Q_PROPERTY(QString accent READ accent NOTIFY accentChanged)
        Q_PROPERTY(QString background READ background NOTIFY backgroundChanged)
        Q_PROPERTY(QString foreground READ foreground NOTIFY foregroundChanged)
        Q_PROPERTY(QString primary READ primary NOTIFY primaryChanged)
        Q_PROPERTY(QString primaryForeground READ primaryForeground NOTIFY primaryForegroundChanged)
        Q_PROPERTY(QString secondary READ secondary NOTIFY secondaryChanged)
        Q_PROPERTY(QString secondaryForeground READ secondaryForeground NOTIFY secondaryForegroundChanged)
    public:
        ThemeViewModel(Domain::StreamingServicesController& streamingServices, Domain::Settings& settings,
                       Domain::IThemeLoader& themeLoader);

        bool isDark() const;
        QString accent() const;
        QString background() const;
        QString foreground() const;
        QString primary() const;
        QString primaryForeground() const;
        QString secondary() const;
        QString secondaryForeground() const;
        QStringList availableThemes() const;

        Q_INVOKABLE double colorScaleFactor(const QString& color) const;
        Q_INVOKABLE bool isDark(const QString& color) const;

        Domain::Theme customTheme() const;
        Domain::Theme theme(const QString& themeName) const;

    signals:
        void isDarkChanged();
        void accentChanged();
        void backgroundChanged();
        void foregroundChanged();
        void primaryChanged();
        void primaryForegroundChanged();
        void secondaryChanged();
        void secondaryForegroundChanged();

    private slots:
        void update();
        void onCurrentServiceChanged(Domain::StreamingService* streamingService);
        void onServiceAdded(Domain::StreamingService* service);

    private:
        void setAccent(const QString& value);
        void setBackground(const QString& value);
        void setForeground(const QString& value);
        void setPrimary(const QString& value);
        void setPrimaryForeground(const QString& value);
        void setSecondary(const QString& value);
        void setSecondaryForeground(const QString& value);
        void fromTheme(const Domain::Theme& newTheme);
        void collectThemes();

        Domain::StreamingServicesController& streamingServices_;
        Domain::IThemeLoader& loader_;
        Domain::Setting& accentColorSetting_;
        Domain::Setting& themeSetting_;
        Domain::Setting& backgroundSetting_;
        Domain::Setting& foregroundSetting_;
        Domain::Setting& primaryBackgroundSetting_;
        Domain::Setting& primaryForegroundSetting_;
        Domain::Setting& secondaryBackgroundSetting_;
        Domain::Setting& secondaryForegroundSetting_;
        Domain::Theme currentTheme_;
        QMap<QString, Domain::Theme> availableThemes_;

        bool isAdaptiveTheme() const;
    };
}
