#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Domain
{
    struct StreamingServiceMetadata
    {
        QString author;
        QString authorWebsite;
        QString logoPath;
        QString name;
        QString url;
        QString script;
        QString scriptPath;
        QString pluginDirectory;
        QString version;

        StreamingServiceMetadata() = default;

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
