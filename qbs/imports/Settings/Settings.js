var TextFile = require("qbs.TextFile");

function getSchema() {
    var schemaFile = new TextFile(project.sourceDirectory + "/src/lib/infrastructure/resources/Settings/schema.json");
    return JSON.parse(schemaFile.readAll());
}

function getKeys(schema) {
    var keys = [];
    for (var categoryIndex = 0; categoryIndex < schema.categories.length; categoryIndex++) {
        var category = schema.categories[categoryIndex];
        for (var settingIndex = 0; settingIndex < category.settings.length; settingIndex++) {
            var setting = category.settings[settingIndex];
            var fullKey = category.key + "/" + setting.key;
            keys.push(fullKey);
        }
    }
    return keys;
}

function getEnumValues(keys) {
    var values = [];
    for(var i = 0; i < keys.length; i++) {
        var tokens = keys[i].split('/');
        var category = tokens[0];
        var setting = tokens[1];
        values.push('            ' + category.replace(/-/g, '_').toUpperCase() + '_' + setting.replace(/-/g, '_').toUpperCase())
    }
    return values.join(",\n");
}

function getEnumNames(keys) {
    var names = [];
    for(var i = 0; i < keys.length; i++) {
        var key = keys[i];
        names.push('            enumToString << "' + key + '";')
    }
    return names.join("\n");
}

function getNames(schema) {
    var names = [];
    for (var categoryIndex = 0; categoryIndex < schema.categories.length; categoryIndex++) {
        var category = schema.categories[categoryIndex];
        for (var settingIndex = 0; settingIndex < category.settings.length; settingIndex++) {
            var setting = category.settings[settingIndex];
            if (setting.name)
            {
                var translationString = '        "' + setting.name + '": qsTr("' + setting.name + '")';
                names.push(translationString);
            }
        }
    }
    return names.join(",\n");
}

function getTooltips(schema) {
    var tooltips = [];
    for (var categoryIndex = 0; categoryIndex < schema.categories.length; categoryIndex++) {
        var category = schema.categories[categoryIndex];
        for (var settingIndex = 0; settingIndex < category.settings.length; settingIndex++) {
            var setting = category.settings[settingIndex];
            if (setting.tooltip)
            {
                var translationString = '        "' + setting.tooltip + '": qsTr("' + setting.tooltip + '")';
                tooltips.push(translationString);
            }
        }
    }
    return tooltips.join(",\n");
}

function getCategories(schema) {
    var categories = [];
    for (var categoryIndex = 0; categoryIndex < schema.categories.length; categoryIndex++) {
        var category = schema.categories[categoryIndex];
        var name = category.name;
        if (category.name)
        {
            var translationString = '        "' + category.name + '": qsTr("' + category.name + '")';
            categories.push(translationString);
        }
    }
    return categories.join(",\n");
}
