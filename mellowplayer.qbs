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
    property string buildDate: {
        function zeroPad(number, size) {
            var s = String(number)
            while (s.length < (size || 2))
            {
                s = "0" + s;
            }
            return s;
        }
        var d = new Date();
        return d.getFullYear() + "-" + zeroPad(d.getMonth() + 1) + "-" + zeroPad(d.getDate());

    }

    // Utils
    property string thridPartyIncludePath: sourceDirectory + "/3rdparty"

    name: "MellowPlayer"
    qbsSearchPaths: "qbs"
    references: [
        "3rdparty/libqxt/libqxt.qbs",
        "src/src.qbs",
        "tests/tests.qbs",
    ]
}
