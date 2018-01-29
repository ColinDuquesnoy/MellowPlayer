import qbs
import qbs.Probes

Product {
    id: product

    type: "application"
    name: "MellowPlayer"

    bundle.isBundle: platform.isBundle

    Depends { name: "cpp" }
    Depends { name: "bundle" }
    Depends { name: "platform" }
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
