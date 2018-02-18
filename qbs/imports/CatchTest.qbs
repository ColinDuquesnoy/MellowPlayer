import qbs

Product {
    property string layer: ""
    property string kind: "UnitTests"
    
    files: ["**", project.main]
    name: "MellowPlayer." + layer + "." + kind
    type: ["application", "autotest"]
    consoleApplication: platform.windows

    cpp.includePaths: base.concat(project.includePaths)
    cpp.cxxLanguageVersion: platform.cxxLanguageVersion
    cpp.defines: ['PLUGINS_DIR="' + project.sourceDirectory + 'src/plugins/web"']
    cpp.warningLevel: undefined
    cpp.cxxFlags: platform.testCxxFlags
    cpp.linkerFlags: platform.linkerFlags
    cpp.treatWarningsAsErrors: false
    cpp.staticLibraries: layer == "Presentation" && platform.windows ? base.concat(["user32"]) : base
    cpp.dynamicLibraries: platform.isGcc && project.enableCoverage ? base.concat(["gcov"]) : base

    Group {
        name: "Application"
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "tests"
        condition: platform.windows
    }

    Depends { name: 'cpp' }
    Depends { name: 'platform' }
    Depends { name: 'Qt.core' }
    Depends { name: 'Qt.gui' }
    Depends { name: 'Qt.test' }
    Depends { name: 'MellowPlayer.Domain' }
    Depends { name: 'MellowPlayer.Infrastructure' }
    Depends { name: 'MellowPlayer.Presentation' }
    Depends { name: 'MellowPlayer.TestLib' }
}
