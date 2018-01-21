import qbs 1.0

DynamicLibrary {
    id: product

    name: "MellowPlayer.Domain"

    cpp.includePaths: [product.sourceDirectory + "/include"]
    cpp.cxxLanguageVersion: "c++17"

    Group {
        name: "Source Files"
        files: [
            "src/*.cpp",
            "src/*/*.cpp",
            "src/*/*/*.cpp",
        ]
    }

    Group {
        name: "Header Files"
        files: [
            "include/MellowPlayer/Domain/*.hpp",
            "include/MellowPlayer/Domain/*/*.hpp",
            "include/MellowPlayer/Domain/*/*/*.hpp"
        ]
    }

    Group {
        name: "Library"
        fileTagsFilter: "dynamiclibrary"
        qbs.install: true
        qbs.installDir: "lib"
    }

    Depends { name: 'cpp' }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
    Depends { name: "Qt.qml" }

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.gui" }
        Depends { name: "Qt.qml" }

        cpp.cxxLanguageVersion: product.cpp.cxxLanguageVersion
        cpp.includePaths: product.cpp.includePaths
    }
}
