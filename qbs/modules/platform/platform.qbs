import qbs

Module {
    // shortcuts
    property bool unix: (qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")) && !qbs.targetOS.contains("macos")
    property bool macOs: qbs.targetOS.contains("macos")
    property bool windows: qbs.targetOS.contains("windows")

    // platform specific library link options
    property string libraryType: "staticlibrary"
    property bool isBundle: macOs
    property string cxxLanguageVersion: unix ? "c++17" : "c++1z"
}
