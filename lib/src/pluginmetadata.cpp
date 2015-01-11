#include "mellowplayer/pluginmetadata.h"


PluginMetaData extractMetaData(QPluginLoader *pluginLoader)
{
    PluginMetaData meta;
    meta.name = pluginLoader->metaData().value(
                "MetaData").toObject().value("name").toString();
    meta.author = pluginLoader->metaData().value(
                "MetaData").toObject().value("author").toString();
    meta.website = pluginLoader->metaData().value(
                "MetaData").toObject().value("website").toString();
    meta.version = pluginLoader->metaData().value(
                "MetaData").toObject().value("version").toString();
    meta.icon = QIcon(pluginLoader->metaData().value(
                          "MetaData").toObject().value("icon").toString());
    return meta;
}
