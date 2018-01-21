import qbs 1.0
import qbs.Probes

Product {
    id: product

    type: "application"
    name: "MellowPlayer"

    Depends { name: "cpp" }
    Depends { name: "Qt.webengine" }
    Depends { name: "Qt.quickcontrols2" }
    Depends { name: "MellowPlayer.Domain" }
    Depends { name: "MellowPlayer.Infrastructure" }
    Depends { name: "MellowPlayer.Presentation" }

    Group {
        name: "Application"
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Group {
        name: "Source Files"
        files: [ "*.cpp" ]
    }
    Group {
        name: "Header Files"
        files: [ "*.hpp" ]
    }
    Group {
        name: "QML"
        files: ["qml.qrc", "main.qml"]
    }
    Group {
        name: "Resources"
        files: ["mellowplayer.ico", "MellowPlayer.rc"]
    }

    Group {
        name: "Share"

        files: [
            "share/applications/mellowplayer.desktop",
            "share/icons/hicolor/scalable/apps/mellowplayer.svg",
            "share/metainfo/mellowplayer.appdata.xml"
        ]

        qbs.install: true
        qbs.installSourceBase: "share"
        qbs.installDir: "share"
    }
}
