#pragma once

#include <MellowPlayer/UseCases/Settings/Settings.hpp>
#include "SettingModelFactory.hpp"
#include "SettingsCategoryModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingsModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* categories READ getCategories CONSTANT)
public:
    SettingsModel(UseCases::Settings& settings, QObject* parent= nullptr);

    Q_INVOKABLE SettingModel* get(int key);
    QAbstractItemModel* getCategories() const;

private:
    UseCases::Settings& settings;
    SettingModelFactory settingModelFactory;
    QQmlObjectListModel<SettingsCategoryModel>* categories;
};

END_MELLOWPLAYER_NAMESPACE
