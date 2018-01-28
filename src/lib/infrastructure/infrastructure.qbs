import qbs 1.0
import qbs.TextFile

Product {
    id: product

    name: "MellowPlayer.Infrastructure"
    type: platform.libraryType

    cpp.includePaths: [
        product.sourceDirectory + "/include",
        project.thridPartyIncludePath,
        project.thridPartyIncludePath + "/spdlog-0.11.0/include/"
    ]
    cpp.cxxLanguageVersion: platform.cxxLanguageVersion

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
            condition: platform.windows
        }

        Group {
            name: "Linux/BSD Source Files"
            files: [
                "src/Updater/Linux/*.cpp"
            ]
            condition: platform.unix
        }

        Group {
            name: "MacOS Source Files"
            files: [
                "src/Updater/OSX/*.cpp"
            ]
            condition: platform.macOs
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
            condition: product.platform.windows
        }

        Group {
            name: "Linux/BSD Header Files"
            files: [
                "include/MellowPlayer/Infrastructure/Updater/Linux/*.hpp"
            ]
            condition: product.platform.unix
        }

        Group {
            name: "MacOS Header Files"
            files: [
                "include/MellowPlayer/Infrastructure/Updater/OSX/*.hpp"
            ]
            condition: product.platform.macOs
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
        qbs.installDir: project.libDir
    }

    Group {
        name: "BuildConfig"
        files: ["src/BuildConfig.cpp.in"]
        fileTags: ["cpp.in"]
    }

    Rule {
        inputs: ["cpp.in"]
        Artifact {
            filePath: "src/BuildConfig.cpp"
            fileTags: "cpp"
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generating BuildConfig.cpp";
            cmd.highlight = "codegen";
            cmd.onWindows = product.platform.windows
            cmd.sourceCode = function() {
                var file = new TextFile(input.filePath);
                var content = file.readAll();
                content = content.replace(/@VERSION_MAJOR@/g, project.versionMajor);
                content = content.replace(/@VERSION_MINOR@/g, project.versionMinor);
                content = content.replace(/@VERSION_PATCH@/g, project.versionPatch);
                content = content.replace(/@VERSION_TWEAK@/g, project.buildNumber);
                content = content.replace("@BUILD_DATE@", project.buildDate);
                content = content.replace("@SOURCE_DIR@", project.sourceDirectory);
                content = content.replace("@DEFAULT_THEME@", project.defaultTheme);
                file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.write(content);
                file.close();
            }
            return cmd;
        }
    }

    Depends { name: 'cpp' }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.concurrent" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.network" }
    Depends { name: "Qt.sql" }
    Depends { name: 'MellowPlayer.Domain' }
    Depends { name: 'platform' }

    Export {
        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.concurrent" }
        Depends { name: "Qt.widgets" }
        Depends { name: "Qt.network" }
        Depends { name: "Qt.sql" }
        Depends { name: 'MellowPlayer.Domain' }

        cpp.cxxLanguageVersion: platform.cxxLanguageVersion
        cpp.includePaths: product.cpp.includePaths
    }
}
