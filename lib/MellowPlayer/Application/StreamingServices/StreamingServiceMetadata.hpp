#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Application
{
    struct StreamingServiceMetadata
    {
        /**
         * @brief Name of the plugin's author.
         */
        QString author;

        /**
         * @brief Url of the plugin's author's website.
         */
        QString authorWebsite;

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

        QString pluginDirectory;

        /**
         * @brief The version of the plugin.
         */
        QString version;

        StreamingServiceMetadata() : author(""), authorWebsite(""), logoPath(""), name(""), url(""), script(""), scriptPath(""), version("")
        {
        }

        bool isValid() const
        {
            return !name.isEmpty() && !url.isEmpty() && !script.isEmpty();
        }

        bool operator==(const StreamingServiceMetadata& rhs) const
        {
            return name == rhs.name && url == rhs.url;
        }

        bool operator!=(const StreamingServiceMetadata& rhs) const
        {
            return !operator==(rhs);
        }
    };
}
