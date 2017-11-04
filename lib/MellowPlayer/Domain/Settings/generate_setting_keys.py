#!/usr/bin/env python3
"""
This script generates ApplicationSettingKeys.hpp which contains all the settings keys found schema.json and an utility
function to retrieve the key string value from a member of the enum.

Run this script every time you modify schema.json.
"""
import json


def get_setting_key_template():
    with open('SettingKey.hpp.in') as f:
        return f.read()


def get_translator_template():
    with open("SettingTranslator.js.in") as f:
        return f.read()


def get_schema():
    with open('schema.json') as f:
        return f.read()


def load_schema():
    return json.loads(get_schema())


def get_keys(schema):
    keys = []

    for category in schema['categories']:
        for setting in category['settings']:
            keys.append(category['key'] + '/' + setting['key'])

    return keys


def get_names(schema):
    names = []

    for category in schema['categories']:
        for setting in category['settings']:
            name = setting['name']
            if name:
                names.append("        %r: qsTr(%r)" % (name, name))

    return ',\n'.join(names)


def get_tooltips(schema):
    tooltips = []

    for category in schema['categories']:
        for setting in category['settings']:
            try:
                tooltips.append("        %r: qsTr(%r)" % (setting['tooltip'], setting['tooltip']))
            except KeyError:
                pass

    return ',\n'.join(tooltips)


def get_categories(schema):
    categories = []

    for category in schema['categories']:
        name = category['name']
        if name:
            categories.append("        %r: qsTr(%r)" % (name, name))

    return ',\n'.join(categories)


def get_setting_key_values(keys):
    names = []
    for key in keys:
        cat_key, setting_key = key.split('/')
        names.append('            ' + cat_key.replace('-', '_').upper() + '_' +
                     setting_key.replace('-', '_').upper())

    names.sort()
    return ',\n'.join(names)


def get_setting_key_names(keys):
    strings = []
    for key in keys:
        strings.append('            enumToString << "%s";' % key)

    strings.sort()
    return '\n'.join(strings)


def create_setting_key(enum_names, enum_values, template):
    content = template % {'enum_values': enum_values, 'enum_names': enum_names}
    with open('SettingKey.hpp', 'w') as f:
        f.write(content)


def create_translator(names, tooltips, categories, template):
    content = template % {'names': names, 'tooltips': tooltips, "categories": categories}
    with open('../../Presentation/Views/MellowPlayer/SettingsTranslator.js', 'w') as f:
        f.write(content)


def main():
    schema = load_schema()

    setting_key_template = get_setting_key_template()

    keys = get_keys(schema)
    enum_values = get_setting_key_values(keys)
    enum_names = get_setting_key_names(keys)
    create_setting_key(enum_names, enum_values, setting_key_template)

    translator_template = get_translator_template()
    create_translator(get_names(schema), get_tooltips(schema), get_categories(schema), translator_template)


if __name__ == '__main__':
    main()
