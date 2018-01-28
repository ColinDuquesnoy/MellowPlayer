import qbs 1.0

Project {
    id: project

    property int versionMajor: 3
    property int versionMinor: 3
    property int versionPatch: 50
    property int buildNumber: 0
    property string thridPartyIncludePath: project.sourceDirectory + "/3rdparty"
    property string buildDate: {
        var d = new Date();
        return d.getFullYear() + "-" + (d.getMonth() + 1) + "-" + d.getDate();
    }

    // Build options
    property string defaultTheme: "Adaptive"
    property string libDir: "lib"

    name: "mellowplayer"
    qbsSearchPaths: "qbs"
    references: [
        "3rdparty/libqxt/libqxt.qbs",
        "src/lib/domain/domain.qbs",
        "src/lib/infrastructure/infrastructure.qbs",
        "src/lib/presentation/imports/settings_translator.qbs",
        "src/lib/presentation/presentation.qbs",
        "src/main/main.qbs",
    ]
}
