#pragma once

#include <QtCore/QAbstractItemModel>
#include <MellowPlayer/Application/Settings/SettingsCategory.hpp>
#include "SettingModelFactory.hpp"

template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingsCategoryModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString icon READ getIcon CONSTANT)
    Q_PROPERTY(QString qmlComponent READ getQmlComponent CONSTANT)
    Q_PROPERTY(QAbstractItemModel* settings READ getSettingsModel CONSTANT)
public:
    SettingsCategoryModel(Application::SettingsCategory* settingsCategory= nullptr, QObject* parent= nullptr);

    virtual QString getName() const;
    virtual QString getIcon() const;
    virtual QString getQmlComponent() const;;
    QAbstractItemModel* getSettingsModel();

    Q_INVOKABLE void restoreDefaults();

private:
    Application::SettingsCategory* settingsCategory;
    QQmlObjectListModel<SettingModel>* settingsListModel;
    SettingModelFactory settingModelFactory;
};

class CustomSettingsCategoryModel: public SettingsCategoryModel
{
    Q_OBJECT
public:
    CustomSettingsCategoryModel(const QString& name, const QString& icon, const QString& qmlComponent, QObject* parent);

    QString getName() const override;
    QString getIcon() const override;
    QString getQmlComponent() const override;

private:
    QString name;
    QString icon;
    QString qmlComponent;
};

END_MELLOWPLAYER_NAMESPACE
