#pragma once

#include <QString>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class FileHelper {
public:
    static QString createLogDirectory();
    static QString appDataDirectory();
    static QString logDirectory();
};

END_MELLOWPLAYER_NAMESPACE