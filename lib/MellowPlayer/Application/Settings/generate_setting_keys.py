#!/usr/bin/env python3
"""
This script generates ApplicationSettingKeys.hpp which contains all the settings keys found schema.json and an utility
function to retrieve the key string value from a member of the enum.

Run this script every time you modify schema.json.
"""
import json

import os


def get_template():
    with open('SettingKey.hpp.in') as f:
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


def get_enum_values(keys):
    names = []
    for key in keys:
        cat_key, setting_key = key.split('/')
        names.append('        ' + cat_key.replace('-', '_').upper() + '_' +
                      setting_key.replace('-', '_').upper())

    names.sort()
    return ',\n'.join(names)


def get_enum_names(keys):
    strings = []
    for key in keys:
        strings.append('        enumToString << "%s";' % key)

    strings.sort()
    return '\n'.join(strings)


def create_file(enum_names, enum_values, template):
    content = template % {'enum_values': enum_values, 'enum_names': enum_names}
    with open('SettingKey.hpp', 'w') as f:
        f.write(content)


def main():
    template = get_template()
    schema = load_schema()
    keys = get_keys(schema)
    enum_values = get_enum_values(keys)
    enum_names = get_enum_names(keys)
    create_file(enum_names, enum_values, template)


if __name__ == '__main__':
    main()
