import qbs

Module {
    id: platform

    // shortcuts
    property bool unix: (qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")) && !qbs.targetOS.contains("macos")
    property bool macOs: qbs.targetOS.contains("macos")
    property bool windows: qbs.targetOS.contains("windows")
    property var cxxFlags: {
        if (platform.unix) {
            return [
                "-W",
                "-Wall",
                "-Wextra",
                "-Winvalid-pch",
                "-Wnon-virtual-dtor",
                "-Wno-class-memaccess",
                "-Wno-deprecated-declarations",
                "-Wdelete-non-virtual-dtor",
            ]
        }
        else if (platform.macOs)
            return ["-Weverything"]
        else if (platform.windows)
            return ["/W4"]
    }

    property var testCxxFlags: {
        if (platform.unix) {
            return [
                "-W",
                "-Wall",
                "-Wextra",
                "-Winvalid-pch",
                "-Wno-class-memaccess",
                "-Wno-deprecated-declarations",
                "-Wno-cast-function-type"
            ]
        }
        else if (platform.macOs)
            return ["-Weverything"]
        else if (platform.windows)
            return ["/W4"]
    }

    // platform specific library link options
    property string libraryType: "staticlibrary"
    property bool isBundle: macOs
    property string cxxLanguageVersion: unix ? "c++17" : "c++1z"
}
