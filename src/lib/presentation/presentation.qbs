import qbs
import qbs.Probes
import qbs.TextFile
import Settings

Product {
    id: product

    name: "MellowPlayer.Presentation"
    type: platform.libraryType

    cpp.includePaths: [ product.sourceDirectory + "/include" ]
    cpp.cxxLanguageVersion: platform.cxxLanguageVersion

    property bool hasLibnotify: product.libnotify !== undefined && product.libnotify.found

    Group {
        name: "Imports"
        files: "imports/imports.qrc"
    }

    Group {
        name: "Source Files"
        files: [
            "src/*.cpp",
            "src/*/*.cpp",
            "src/Notifications/Presenters/*.cpp",
            "src/ViewModels/*/*.cpp",
            "src/ViewModels/*/*/*.cpp",
        ]

        Group {
            name: "MPRIS Source Files"
            files: [
                "src/Mpris/Linux/*.cpp"
            ]
            condition: product.platform.unix
        }

        Group {
            name: "Libnotify Presenter Source Files"
            files: [
                "src/Notifications/Presenters/Linux/*.cpp"
            ]
            condition: product.hasLibnotify
        }
    }

    Group {
        name: "Header Files"
        files: [
            "include/MellowPlayer/Presentation/*.hpp",
            "include/MellowPlayer/Presentation/*/*.hpp",
            "include/MellowPlayer/Presentation/Notifications/Presenters/*.hpp",
            "include/MellowPlayer/Presentation/ViewModels/*/*.hpp",
            "include/MellowPlayer/Presentation/ViewModels/*/*/*.hpp",
        ]

        Group {
            name: "MPRIS Header Files"
            files: [
                "include/MellowPlayer/Presentation/Mpris/Linux/*.hpp"
            ]
            condition: product.platform.unix
        }

        Group {
            name: "Libnotify Presenter Header Files"
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

    Group {
        name: "Library"
        fileTagsFilter: "dynamiclibrary"
        qbs.install: true
        qbs.installDir: project.libDir
    }

    Depends { name: 'cpp' }
    Depends { name: "platform"}
    Depends { name: "Qt.core" }
    Depends { name: "Qt.concurrent" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.network" }
    Depends { name: "Qt.webengine" }
    Depends { name: "Qt.sql" }
    Depends { name: "Qt.dbus"; condition: platform.unix }
    Depends { name: 'MellowPlayer.Domain' }
    Depends { name: 'MellowPlayer.Infrastructure' }
    Depends { name: 'qxtglobalshortcut' }
    Depends { name: "settings_translator" }
    Depends { name: "libnotify"; condition: platform.unix }

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.concurrent" }
        Depends { name: "Qt.widgets" }
        Depends { name: "Qt.network" }
        Depends { name: "Qt.webengine" }
        Depends { name: "Qt.webenginewidgets" }
        Depends { name: "Qt.sql" }
        Depends { name: "Qt.dbus"; condition: product.platform.unix }
        Depends { name: 'MellowPlayer.Domain' }
        Depends { name: 'MellowPlayer.Infrastructure' }
        Depends { name: 'qxtglobalshortcut' }
        Depends { name: "settings_translator" }

        cpp.includePaths: product.cpp.includePaths
    }
}
