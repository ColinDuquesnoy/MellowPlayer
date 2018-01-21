import qbs 1.0

DynamicLibrary {
    id: product

    name: "MellowPlayer.Infrastructure"

    cpp.includePaths: [
        product.sourceDirectory + "/include",
        project.thridPartyIncludePath,
        project.thridPartyIncludePath + "/spdlog-0.11.0/include/"
    ]
    cpp.cxxLanguageVersion: "c++17"
    cpp.defines: [
        'MELLOWPLAYER_VERSION_MAJOR=' + project.versionMajor,
        'MELLOWPLAYER_VERSION_MINOR=' + project.versionMinor,
        'MELLOWPLAYER_VERSION_PATCH=' + project.versionPatch,
        'MELLOWPLAYER_VERSION_TWEAK=' + project.versionTweak,
        'MELLOWPLAYER_VERSION_STR="' + project.version + '"',
        'MELLOWPLAYER_SOURCE_DIR="' + project.sourceDir + '"',
        'MELLOWPLAYER_BUILD_DATE="' + project.buildDate + '"'
    ]

    Group {
        name: "Source Files"
        files: [
            "src/*.cpp",
            "src/*/*.cpp",
            "src/Updater/Github/*.cpp"
        ]

        Group {
            name: "Windows Source Files"
            files: [
                "src/Updater/Windows/*.cpp"
            ]
            condition: qbs.targetOS.contains("windows")
        }

        Group {
            name: "Linux/BSD Source Files"
            files: [
                "src/Updater/Linux/*.cpp"
            ]
            condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")
        }

        Group {
            name: "MacOS Source Files"
            files: [
                "src/Updater/OSX/*.cpp"
            ]
            condition: qbs.targetOS.contains("macos")
        }
    }

    Group {
        name: "Header Files"
        files: [
            "include/MellowPlayer/Infrastructure/*.hpp",
            "include/MellowPlayer/Infrastructure/*/*.hpp",
            "include/MellowPlayer/Infrastructure/Updater/Github/*.hpp"
        ]

        Group {
            name: "Windows Header Files"
            files: [
                "include/MellowPlayer/Infrastructure/Updater/Windows/*.hpp"
            ]
            condition: qbs.targetOS.contains("windows")
        }

        Group {
            name: "Linux/BSD Header Files"
            files: [
                "include/MellowPlayer/Infrastructure/Updater/Linux/*.hpp"
            ]
            condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")
        }

        Group {
            name: "MacOS Header Files"
            files: [
                "include/MellowPlayer/Infrastructure/Updater/OSX/*.hpp"
            ]
            condition: qbs.targetOS.contains("macos")
        }
    }

    Group {
        name: "Resources"
        files: "resources/infrastructure.qrc"
    }

    Group {
        name: "Library"
        fileTagsFilter: "dynamiclibrary"
        qbs.install: true
        qbs.installDir: "lib"
    }

    Depends { name: 'cpp' }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.concurrent" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.network" }
    Depends { name: "Qt.sql" }
    Depends { name: 'MellowPlayer.Domain' }

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.concurrent" }
        Depends { name: "Qt.widgets" }
        Depends { name: "Qt.network" }
        Depends { name: "Qt.sql" }
//        Depends { name: 'qxtglobalshortcut' }
        Depends { name: 'MellowPlayer.Domain' }

        cpp.cxxLanguageVersion: product.cpp.cxxLanguageVersion
        cpp.includePaths: product.cpp.includePaths
    }
}
 
