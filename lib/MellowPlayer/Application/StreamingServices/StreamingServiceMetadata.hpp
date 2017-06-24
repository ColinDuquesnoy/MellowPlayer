#pragma once

#include <MellowPlayer/Macros.hpp>
#include <QtCore/QString>

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

struct StreamingServiceMetadata {
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
    QString logoPath;

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
     * @brief Path to the plugin script.
     */
    QString scriptPath;

    /**
     * @brief The version of the plugin.
     */
    QString version;

    StreamingServiceMetadata()
        : author(""),
          authorWebsite(""),
          color(""),
          logoPath(""),
          name(""),
          url(""),
          script(""),
          scriptPath(""),
          version("") {

    }

    bool isValid() const {
        return !name.isEmpty() && !url.isEmpty() && !script.isEmpty();
    }

    bool operator==(const StreamingServiceMetadata& rhs) const {
        return name == rhs.name && url == rhs.url;
    }

    bool operator!=(const StreamingServiceMetadata& rhs) const {
        return !operator==(rhs);
    }
};

END_MELLOWPLAYER_NAMESPACE
