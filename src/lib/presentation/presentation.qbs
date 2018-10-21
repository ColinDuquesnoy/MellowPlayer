import qbs
import qbs.Probes
import qbs.TextFile
import Settings
import MellowPlayerLib

MellowPlayerLib {
    id: product

    layer: "Presentation"

    Qt.core.resourcePrefix: "/MellowPlayer"
    Qt.core.resourceSourceBase: sourceDirectory
    Qt.core.resourceFileBaseName: "imports"

    property bool hasLibnotify: product.libnotify !== undefined && product.libnotify.found

    Group {
        name: "Imports"
        files: ["**/*.qml", "**/*.js", "**/qmldir"]
        fileTags: "qt.core.resource_data"
    }

    Group {
        name: "Sources"
        files: [
            "src/*.cpp",
            "src/*/*.cpp",
            "src/Notifications/Presenters/*.cpp",
            "src/ViewModels/*/*.cpp",
            "src/ViewModels/*/*/*.cpp",
        ]

        Group {
            name: "MPRIS Sources"
            files: [
                "src/Mpris/Linux/*.cpp"
            ]
            condition: product.platform.unix
        }

        Group {
            name: "Libnotify Presenter Sources"
            files: [
                "src/Notifications/Presenters/Linux/*.cpp"
            ]
            condition: product.hasLibnotify
        }
    }

    Group {
        name: "Headers"
        files: [
            "include/MellowPlayer/Presentation/*.hpp",
            "include/MellowPlayer/Presentation/*/*.hpp",
            "include/MellowPlayer/Presentation/Notifications/Presenters/*.hpp",
            "include/MellowPlayer/Presentation/ViewModels/*/*.hpp",
            "include/MellowPlayer/Presentation/ViewModels/*/*/*.hpp",
        ]

        Group {
            name: "MPRIS Headers"
            files: [
                "include/MellowPlayer/Presentation/Mpris/Linux/*.hpp"
            ]
            condition: product.platform.unix
        }

        Group {
            name: "Libnotify Presenter Headers"
            files: [
                "include/MellowPlayer/Presentation/Notifications/Presenters/Linux/*.hpp"
            ]
            condition: product.hasLibnotify
        }
    }

    Group {
        name: "Resources"
        files: "resources/presentation.qrc"
    }

    Depends { name: "Qt.concurrent" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.network" }
    Depends { name: "Qt.webengine" }
    Depends { name: "Qt.webenginewidgets" }
    Depends { name: "Qt.sql" }
    Depends { name: "Qt.dbus"; condition: platform.unix }
    Depends { name: 'MellowPlayer.Domain' }
    Depends { name: 'MellowPlayer.Infrastructure' }
    Depends { name: "qxt" }
    Depends { name: "qxtglobalshortcut"; condition: !qxt.found; required: false }
    Depends { name: "libnotify"; condition: platform.unix }

    Export {
        Depends { name: "platform"}
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.concurrent" }
        Depends { name: "Qt.widgets" }
        Depends { name: "Qt.network" }
        Depends { name: "Qt.sql" }
        Depends { name: "Qt.dbus"; condition: platform.unix }
        Depends { name: "MellowPlayer.Domain" }
        Depends { name: "MellowPlayer.Infrastructure" }
        Depends { name: "qxt" }
        Depends { name: "qxtglobalshortcut"; condition: !qxt.found; required: false }

        cpp.includePaths: product.cpp.includePaths
    }
}
