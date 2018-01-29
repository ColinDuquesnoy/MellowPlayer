import qbs

Project {
    // Build options
    property string defaultTheme: "Adaptive"
    property string libDir: "lib"
    property bool buildTests: true

    // Version info
    property int versionMajor: 3
    property int versionMinor: 3
    property int versionPatch: 50
    property int buildNumber: 0
    property string buildDate: { var d = new Date(); return d.getFullYear() + "-" + (d.getMonth() + 1) + "-" + d.getDate(); }

    // Utils
    property string thridPartyIncludePath: sourceDirectory + "/3rdparty"

    name: "MellowPlayer"
    qbsSearchPaths: "qbs"
    references: [
        "3rdparty/libqxt/libqxt.qbs",
        "src/lib/domain/domain.qbs",
        "src/lib/infrastructure/infrastructure.qbs",
        "src/lib/presentation/imports/settings_translator.qbs",
        "src/lib/presentation/presentation.qbs",
        "src/plugins/plugins.qbs",
        "src/main/main.qbs",
        "tests/tests.qbs",
    ]
}
