#pragma once

#include "SettingViewModel.hpp"
#include <MellowPlayer/Application/TimeLimits.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>

class TimeLimitSettingStrings : public QObject
{
    Q_OBJECT
public:
    QString today() const
    {
        return tr("Today");
    };
    QString yesterday() const
    {
        return tr("Yesterday");
    };
    QString lastWeek() const
    {
        return tr("Last week");
    };
    QString lastMonth() const
    {
        return tr("Last month");
    };
    QString lastYear() const
    {
        return tr("Last year");
    };
    QString never() const
    {
        return tr("Never");
    };
};

namespace MellowPlayer::Presentation
{
    class TimeLimitSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
        Q_PROPERTY(QStringList values READ values CONSTANT)
    public:
        TimeLimitSettingViewModel(Application::Setting& setting, QObject* parent = nullptr);

        QString value() const;
        QStringList values() const;
        QString qmlComponent() override;

    signals:
        void valueChanged();

    public slots:
        void setValue(QString value);

    protected slots:
        void onValueChanged() override;

    private:
        void registerEnumTranslation(Application::TimeLimits value, const QString& translation);

        QMap<QString, Application::TimeLimits> stringToEnum_;
        QMap<Application::TimeLimits, QString> enumToString_;
    };
}
