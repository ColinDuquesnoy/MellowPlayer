#pragma once

#include <QObject>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceStyle.hpp>

namespace MellowPlayer::Application {
 
    class StreamingService;
    class StreamingServicesController;
    class Setting;
    class Settings;
    
}

namespace MellowPlayer::Presentation {

    class StyleViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(QString theme READ getTheme NOTIFY themeChanged)
        Q_PROPERTY(QString accent READ getAccent NOTIFY accentChanged)
        Q_PROPERTY(QString background READ getBackground NOTIFY backgroundChanged)
        Q_PROPERTY(QString foreground READ getForeground NOTIFY foregroundChanged)
        Q_PROPERTY(QString primary READ getPrimary NOTIFY primaryChanged)
        Q_PROPERTY(QString primaryForeground READ getPrimaryForeground NOTIFY primaryForegroundChanged)
        Q_PROPERTY(QString secondary READ getSecondary NOTIFY secondaryChanged)
        Q_PROPERTY(QString secondaryForeground READ getSecondaryForeground NOTIFY secondaryForegroundChanged)
        Q_PROPERTY(bool useServiceStyle READ getUseServiceStyle WRITE setUseServiceStyle NOTIFY useServiceStyleChanged)
    public:
        StyleViewModel(Application::StreamingServicesController& streamingServices, Application::Settings& settings);

        QString getTheme() const;
        QString getAccent() const;
        QString getBackground() const;
        QString getForeground() const;
        QString getPrimary() const;
        QString getPrimaryForeground() const;
        QString getSecondary() const;
        QString getSecondaryForeground() const;
        bool getUseServiceStyle() const;
        void setUseServiceStyle(bool value);

        Q_INVOKABLE double getColorScaleFactor(const QString& color) const;
        Q_INVOKABLE bool isDark(const QString& color) const;

        Application::StreamingServiceStyle getDefaultStyle();

    signals:
        void themeChanged();
        void accentChanged();
        void backgroundChanged();
        void foregroundChanged();
        void primaryChanged();
        void primaryForegroundChanged();
        void secondaryChanged();
        void secondaryForegroundChanged();
        void useServiceStyleChanged();

    private slots:
        void updateStyle();
        void onCurrentServiceChanged(Application::StreamingService* streamingService);

    private:
        void setAccent(const QString& value);
        void setBackground(const QString& value);
        void setForeground(const QString& value);
        void setPrimary(const QString& value);
        void setPrimaryForeground(const QString& value);
        void setSecondary(const QString& value);
        void setSecondaryForeground(const QString& value);
        void fromStyle(const Application::StreamingServiceStyle& newStyle);

        bool useServiceStyle;
        Application::StreamingServicesController& streamingServices;
        Application::Setting& accentColorSetting;
        Application::Setting& adaptiveThemeSetting;
        Application::Setting& backgroundSetting;
        Application::Setting& foregroundSetting;
        Application::Setting& primaryBackgroundSetting;
        Application::Setting& primaryForegroundSetting;
        Application::Setting& secondaryBackgroundSetting;
        Application::Setting& secondaryForegroundSetting;
        Application::StreamingServiceStyle style;
    };

}

