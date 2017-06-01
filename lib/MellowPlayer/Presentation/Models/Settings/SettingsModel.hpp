#pragma once

#include <MellowPlayer/Application/Settings/Settings.hpp>
#include "SettingModelFactory.hpp"
#include "SettingsCategoryModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingsModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* categories READ getCategories CONSTANT)
public:
    SettingsModel(Application::Settings& settings, QObject* parent= nullptr);

    Q_INVOKABLE SettingModel* get(int key);
    QAbstractItemModel* getCategories() const;
    Q_INVOKABLE void restoreDefaults();

private:
    Application::Settings& settings;
    SettingModelFactory settingModelFactory;
    QQmlObjectListModel<SettingsCategoryModel>* categories;
};

END_MELLOWPLAYER_NAMESPACE
