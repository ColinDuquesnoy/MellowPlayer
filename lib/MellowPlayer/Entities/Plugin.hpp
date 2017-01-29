#pragma once

#include <MellowPlayer/Macros.hpp>
#include <QtCore/QString>
#include <QtGui/QImage>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

/**
 * @brief The plugin structure holds the data of a streaming service integration plugin.
 */
struct Plugin {
    /**
     * @brief Name of the plugin's author.
     */
    QString author;

    /**
     * @brief Url of the plugin's author's website.
     */
    QString authorWebsite;

    /**
     * @brief Color of the plugin (affects the color of the application toolbar).
     *
     * @remarks Leave empty to use the default toolbar color.
     */
    QString color;

    /**
     * @brief Logo of the plugin/service.
     */
    QImage logo;

    /**
     * @brief The name of the plugin.
     */
    QString name;

    /**
     * @brief The url of the streaming service
     */
    QString url;

    /**
     * @brief The javascript code of the plugin.
     */
    QString script;

    /**
     * @brief The version of the plugin.
     */
    QString version;

    Plugin()
        : author(""),
          authorWebsite(""),
          color(""),
          logo(),
          name(""),
          url(""),
          script(""),
          version("") {

    }
};

using PluginList = QList<MellowPlayer::Entities::Plugin>;

END_MELLOWPLAYER_NAMESPACE

