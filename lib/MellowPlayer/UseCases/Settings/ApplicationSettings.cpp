#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "ApplicationSettings.hpp"
#include "ISettingsSchemaLoader.hpp"
#include "ISettingsProvider.hpp"
#include "SettingsCategory.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)

ApplicationSettings::ApplicationSettings(ISettingsSchemaLoader& configurationLoader, ISettingsProvider& settingsProvider) {
    QJsonDocument jsonDocument = configurationLoader.load();
    QJsonObject rootObject = jsonDocument.object();
    QJsonArray categoriesArray = rootObject.value("categories").toArray();

    for(int i = 0; i < categoriesArray.count(); ++i) {
        QJsonObject categoryObject = categoriesArray.at(i).toObject();
        SettingsCategory::Data data;
        data.name = categoryObject.value("name").toString();
        data.icon = categoryObject.value("icon").toString();
        data.key = categoryObject.value("key").toString();
        data.parameters = categoryObject.value("settings").toArray();
        categories.append(new SettingsCategory(settingsProvider, data, this));
    }

    for (SettingsCategory* category: categories)
        category->resolveDependencies();
}

const QList<SettingsCategory*>& ApplicationSettings::getCategories() const {
    return categories;
}

const SettingsCategory* ApplicationSettings::getCategory(const QString& key) const {
    for(SettingsCategory* category: categories)
        if (category->getKey() == key)
            return category;
    return nullptr;
}

Setting* ApplicationSettings::getSetting(const QString& key) const {
    QStringList tokens = key.split("/");

    if (tokens.count() != 2)
        return nullptr;

    QString categoryKey = tokens[0];
    QString parameterKey = tokens[1];

    auto* category = getCategory(categoryKey);

    if (category == nullptr)
        return nullptr;

    return category->getSetting(parameterKey);
}
