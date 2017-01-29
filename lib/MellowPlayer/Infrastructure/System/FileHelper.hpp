#pragma once

#include <string>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class FileHelper {
public:
    static std::string createLogDirectory();
    static std::string appDataDirectory();
    static std::string logDirectory();
};

END_MELLOWPLAYER_NAMESPACE