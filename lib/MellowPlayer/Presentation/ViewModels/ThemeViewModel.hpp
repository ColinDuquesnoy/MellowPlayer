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
        Q_PROPERTY(QString accent READ getAccent NOTIFY accentChanged)
        Q_PROPERTY(QString background READ getBackground NOTIFY backgroundChanged)
        Q_PROPERTY(QString foreground READ getForeground NOTIFY foregroundChanged)
        Q_PROPERTY(QString primary READ getPrimary NOTIFY primaryChanged)
        Q_PROPERTY(QString primaryForeground READ getPrimaryForeground NOTIFY primaryForegroundChanged)
        Q_PROPERTY(QString secondary READ getSecondary NOTIFY secondaryChanged)
        Q_PROPERTY(QString secondaryForeground READ getSecondaryForeground NOTIFY secondaryForegroundChanged)
    public:
        ThemeViewModel(Application::StreamingServicesController &streamingServices, Application::Settings &settings,
                       Application::IThemeLoader &themeLoader);

        bool isDark() const;
        QString getAccent() const;
        QString getBackground() const;
        QString getForeground() const;
        QString getPrimary() const;
        QString getPrimaryForeground() const;
        QString getSecondary() const;
        QString getSecondaryForeground() const;
        QStringList getAvailableThemes() const;

        Q_INVOKABLE double getColorScaleFactor(const QString &color) const;
        Q_INVOKABLE bool isDark(const QString &color) const;

        Application::Theme getCustomTheme() const;
        Application::Theme getTheme(const QString &themeName) const;

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
        void onCurrentServiceChanged(Application::StreamingService *streamingService);
        void onServiceAdded(Application::StreamingService *service);

    private:
        void setAccent(const QString &value);
        void setBackground(const QString &value);
        void setForeground(const QString &value);
        void setPrimary(const QString &value);
        void setPrimaryForeground(const QString &value);
        void setSecondary(const QString &value);
        void setSecondaryForeground(const QString &value);
        void fromTheme(const Application::Theme &newTheme);
        void collectThemes();

        Application::StreamingServicesController &streamingServices;
        Application::IThemeLoader &loader;
        Application::Setting &accentColorSetting;
        Application::Setting &themeSetting;
        Application::Setting &backgroundSetting;
        Application::Setting &foregroundSetting;
        Application::Setting &primaryBackgroundSetting;
        Application::Setting &primaryForegroundSetting;
        Application::Setting &secondaryBackgroundSetting;
        Application::Setting &secondaryForegroundSetting;
        Application::Theme currentTheme;
        QMap<QString, Application::Theme> availableThemes;

        bool isAdaptiveTheme() const;
    };
}
