import qbs
import qbs.Probes

StaticLibrary {
    id: product

    name: "qxtglobalshortcut"
    condition: product.qxt === undefined || !product.qxt.found

    cpp.cxxLanguageVersion: platform.cxxLanguageVersion
    cpp.includePaths: [
        product.sourceDirectory + "/src/core",
        product.sourceDirectory + "/src/widgets",
    ]
    cpp.frameworks: platform.macOs ? base.concat(["Carbon", "Cocoa"]) : base

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
        condition: { return product.platform.windows; }
    }

    Group {
        name: "Unix"
        files: "src/widgets/x11/qxtglobalshortcut_x11.cpp"
        condition: product.platform.unix
    }

    Group {
        name: "MacOS"
        files: "src/widgets/mac/qxtglobalshortcut_mac.cpp"
        condition: product.platform.macOs
    }

    Depends { name: 'cpp' }
    Depends { name: "platform" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.core-private" }
    Depends { name: "Qt.gui-private" }
    Depends { name: "Qt.widgets" }
    Depends { name: "qxt"; condition: platform.unix }
    Depends { name: "x11"; condition: platform.unix }

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.core-private" }
        Depends { name: "Qt.gui-private" }
        Depends { name: "Qt.widgets" }

        cpp.cxxLanguageVersion: platform.cxxLanguageVersion
        cpp.includePaths: product.cpp.includePaths
        cpp.cxxFlags: product.cxxFlags
        cpp.linkerFlags: product.cxxFlags
    }
}
