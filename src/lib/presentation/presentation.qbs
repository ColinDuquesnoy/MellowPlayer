import qbs 1.0
import qbs.Probes
import qbs.TextFile
import Settings

DynamicLibrary {
    id: product

    name: "MellowPlayer.Presentation"

    type: ["dynamiclibrary", "js"]
    cpp.includePaths: [ product.sourceDirectory + "/include" ]
    cpp.cxxLanguageVersion: "c++17"

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
            condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")
        }

        Group {
            name: "Libnotify Presenter Source Files"
            files: [
                "src/Notifications/Presenters/Linux/*.cpp"
            ]
            condition: libnotify.found
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
            condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")
        }

        Group {
            name: "Libnotify Presenter Header Files"
            files: [
                "include/MellowPlayer/Presentation/Notifications/Presenters/Linux/*.hpp"
            ]
            condition: product.libnotify.found
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
    Depends { name: "Qt.core" }
    Depends { name: "Qt.concurrent" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.network" }
    Depends { name: "Qt.webengine" }
    Depends { name: "Qt.sql" }
    Depends { name: "Qt.dbus"; condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd") }
    Depends { name: 'MellowPlayer.Domain' }
    Depends { name: 'MellowPlayer.Infrastructure' }
    Depends { name: 'qxtglobalshortcut' }
    Depends { name: "settings_translator" }
    Depends { name: "libnotify"}

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.concurrent" }
        Depends { name: "Qt.widgets" }
        Depends { name: "Qt.network" }
        Depends { name: "Qt.webengine" }
        Depends { name: "Qt.webenginewidgets" }
        Depends { name: "Qt.sql" }
        Depends { name: "Qt.dbus"; condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd") }
        Depends { name: 'MellowPlayer.Domain' }
        Depends { name: 'MellowPlayer.Infrastructure' }
        Depends { name: 'qxtglobalshortcut' }
        Depends { name: "settings_translator" }

        cpp.cxxLanguageVersion: product.cpp.cxxLanguageVersion
        cpp.includePaths: product.cpp.includePaths
    }
}
