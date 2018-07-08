import qbs

Project {
    name: "TestLib"

    StaticLibrary {
        name: "MellowPlayer.TestLib"
        files: ["**"]
        cpp.cxxFlags: platform.testCxxFlags

        Depends { name: 'cpp' }
        Depends { name: 'platform' }
        Depends { name: 'Qt.core' }
        Depends { name: 'MellowPlayer.Domain' }
        Depends { name: 'MellowPlayer.Infrastructure' }
        Depends { name: 'MellowPlayer.Presentation' }
        Depends { name: 'platform' }

        cpp.includePaths: base.concat(project.includePaths)
        cpp.cxxLanguageVersion: platform.cxxLanguageVersion
    }
}
