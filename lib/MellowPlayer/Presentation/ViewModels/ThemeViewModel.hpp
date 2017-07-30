#pragma once

#include <MellowPlayer/Application/Theme/Theme.hpp>
#include <QMap>
#include <QObject>

namespace MellowPlayer::Application
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
        ThemeViewModel(Application::StreamingServicesController& streamingServices, Application::Settings& settings,
                       Application::IThemeLoader& themeLoader);

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

        Application::Theme customTheme() const;
        Application::Theme theme(const QString& themeName) const;

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
        void onCurrentServiceChanged(Application::StreamingService* streamingService);
        void onServiceAdded(Application::StreamingService* service);

    private:
        void setAccent(const QString& value);
        void setBackground(const QString& value);
        void setForeground(const QString& value);
        void setPrimary(const QString& value);
        void setPrimaryForeground(const QString& value);
        void setSecondary(const QString& value);
        void setSecondaryForeground(const QString& value);
        void fromTheme(const Application::Theme& newTheme);
        void collectThemes();

        Application::StreamingServicesController& streamingServices_;
        Application::IThemeLoader& loader_;
        Application::Setting& accentColorSetting_;
        Application::Setting& themeSetting_;
        Application::Setting& backgroundSetting_;
        Application::Setting& foregroundSetting_;
        Application::Setting& primaryBackgroundSetting_;
        Application::Setting& primaryForegroundSetting_;
        Application::Setting& secondaryBackgroundSetting_;
        Application::Setting& secondaryForegroundSetting_;
        Application::Theme currentTheme_;
        QMap<QString, Application::Theme> availableThemes_;

        bool isAdaptiveTheme() const;
    };
}
