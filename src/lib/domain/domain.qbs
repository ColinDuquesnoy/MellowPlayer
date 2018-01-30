import qbs
import qbs.TextFile
import Settings

Product {
    id: product

    name: "MellowPlayer.Domain"
    type: platform.libraryType

    cpp.includePaths: [product.sourceDirectory + "/include", product.buildDirectory]
    cpp.cxxLanguageVersion: platform.cxxLanguageVersion

    Group {
        name: "Sources"
        files: [
            "src/*.cpp",
            "src/*/*.cpp",
            "src/*/*/*.cpp",
        ]
    }

    Group {
        name: "Headers"
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
        qbs.installDir: project.libDir
    }

    Depends { name: 'cpp' }
    Depends { name: "platform" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
    Depends { name: "Qt.qml" }

    Group {
        name: "SettingKey Header"
        files: ["include/MellowPlayer/Domain/Settings/SettingKey.hpp.in"]
        fileTags: ["hpp.in"]
    }

    Rule {
        inputs: ["hpp.in"]
        multiplex: true
        Artifact {
            filePath: "MellowPlayer/Domain/Settings/SettingKey.hpp"
            fileTags: "hpp"
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generating SettingKey.hpp";
            cmd.highlight = "codegen";
            cmd.onWindows = product.platform.windows
            cmd.sourceCode = function() {
                var inFile = new TextFile(input.filePath);
                var keys = Settings.getKeys(Settings.getSchema())
                var values = Settings.getEnumValues(keys);
                var names = Settings.getEnumNames(keys);
                var content = inFile.readAll();
                content = content.replace('%(enum_values)s', values);
                content = content.replace('%(enum_names)s', names);
                file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();
            }
            return cmd;
        }
    }

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.gui" }
        Depends { name: "Qt.qml" }

        cpp.includePaths: product.cpp.includePaths
    }
}
