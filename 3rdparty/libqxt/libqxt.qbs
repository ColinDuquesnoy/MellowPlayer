import qbs 1.0
import qbs.Probes

StaticLibrary {
    id: product

    name: "qxtglobalshortcut"
    condition: !qxt.found

    cpp.cxxLanguageVersion: "c++17"
    cpp.includePaths: [
        product.sourceDirectory + "/src/core",
        product.sourceDirectory + "/src/widgets",
    ]

    Group {
        name: "Source Files"
        files: [
            "src/core/*.cpp",
            "src/widgets/*.cpp",
        ]
    }

    Group {
        name: "Header Files"
        files: [
            "src/core/*.h",
            "src/widgets/*.h",
        ]
    }

    Group {
        name: "Windows"
        files: "src/widgets/win/qxtglobalshortcut_win.cpp"
        condition: qbs.targetOS.contains("windows")
    }

    Group {
        name: "X11"
        files: "src/widgets/x11/qxtglobalshortcut_x11.cpp"
        condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")
    }

    Group {
        name: "MacOS"
        files: "src/widgets/mac/qxtglobalshortcut_mac.cpp"
        condition: qbs.targetOS.contains("macos")
    }

    Depends { name: 'cpp' }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.core-private" }
    Depends { name: "Qt.gui-private" }
    Depends { name: "Qt.widgets" }
    Depends { name: "qxt" }
    Depends { name: "x11"; condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd") }

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.core-private" }
        Depends { name: "Qt.gui-private" }
        Depends { name: "Qt.widgets" }

        cpp.cxxLanguageVersion: product.cpp.cxxLanguageVersion
        cpp.includePaths: product.cpp.includePaths
        cpp.cxxFlags: product.cxxFlags
        cpp.linkerFlags: product.cxxFlags
    }
}
