#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "Settings.hpp"
#include "ISettingsSchemaLoader.hpp"
#include "ISettingsProvider.hpp"
#include "SettingsCategory.hpp"

using namespace std;
USE_MELLOWPLAYER_NAMESPACE(Application)

Settings::Settings(ISettingsSchemaLoader& configurationLoader,
                                         ISettingsProvider& settingsProvider):
        settingsProvider(settingsProvider) {
    QJsonDocument jsonDocument = configurationLoader.load();
    QJsonObject rootObject = jsonDocument.object();
    QJsonArray categoriesArray = rootObject.value("categories").toArray();

    for (int i = 0; i < categoriesArray.count(); ++i) {
        QJsonObject categoryObject = categoriesArray.at(i).toObject();
        SettingsCategory::Data data;
        data.name = categoryObject.value("name").toString();
        data.icon = categoryObject.value("icon").toString();
        data.key = categoryObject.value("key").toString();
        data.parameters = categoryObject.value("settings").toArray();
        categories.append(new SettingsCategory(data, this));
    }

    for (SettingsCategory* category: categories)
        category->resolveDependencies();
}

const QList<SettingsCategory*>& Settings::getCategories() const {
    return categories;
}

SettingsCategory& Settings::getCategory(const QString& key) const {
    for (SettingsCategory* category: categories)
        if (category->getKey() == key)
            return *category;
    throw runtime_error("Unknown category: " + key.toStdString());
}

Setting& Settings::get(const QString& key) const {
    QStringList tokens = key.split("/");

    if (tokens.count() != 2)
        throw runtime_error("Malformed setting key: " + key.toStdString());

    QString categoryKey = tokens[0];
    QString parameterKey = tokens[1];

    auto& category = getCategory(categoryKey);

    return category.getSetting(parameterKey);
}

ISettingsProvider& Settings::getSettingsProvider() const {
    return settingsProvider;
}

Setting& Settings::get(SettingKey::Keys key) {
    return get(SettingKey::toString(key));
}

void Settings::restoreDefaults() {
    for(SettingsCategory* category: categories)
        category->restoreDefaults();
}
