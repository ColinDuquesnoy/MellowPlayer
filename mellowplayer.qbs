import qbs 1.0

Project {
    id: project

    name: "MellowPlayer"

    property int versionMajor: 3
    property int versionMinor: 3
    property int versionPatch: 50
    property int versionTweak: 0
    property string version: versionMajor + "." + versionMinor + "." + versionPatch + "." + versionTweak
    property string thridPartyIncludePath: sourceDirectory + "/3rdparty"
    property string buildDate: {
        var d = new Date();
        return d.getFullYear() + "-" + (d.getMonth() + 1) + "-" + d.getDate();
    }

    references: [
        "3rdparty/libqxt/libqxt.qbs",
        "lib/domain/domain.qbs",
        "lib/infrastructure/infrastructure.qbs",
        "lib/presentation/presentation.qbs",
        "src/main.qbs",
    ]
}
