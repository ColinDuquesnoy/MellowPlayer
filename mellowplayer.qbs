import qbs
import qbs.Environment

Project {
    // Build options
    property string defaultTheme: "Adaptive"
    property string libDir: "lib"
    property bool buildTests: false
    property bool enableCoverage: false

    // set this to true when building an appimage
    property bool staticLibCpp: false

    // Version info
    property int versionMajor: 3
    property int versionMinor: 4
    property int versionPatch: 0
    property int buildNumber: {
        var ciBuildNumber = Environment.getEnv("TRAVIS_BUILD_NUMBER");
        if (!ciBuildNumber) {
            ciBuildNumber = Environment.getEnv("APPVEYOR_BUILD_NUMBER");
            if (!ciBuildNumber)
                ciBuildNumber = "0";
        }
        return parseInt(ciBuildNumber);
    }
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
    property string version: versionMajor + "." + versionMinor + "." + versionPatch

    // Utils
    property string thridPartyIncludePath: sourceDirectory + "/3rdparty"

    name: "MellowPlayer"
    qbsSearchPaths: "qbs"
    references: [
        "3rdparty/3rdparty.qbs",
        "docs/docs.qbs",
        "src/src.qbs",
        "tests/tests.qbs",
        "scripts/packaging/packaging.qbs"
    ]
}