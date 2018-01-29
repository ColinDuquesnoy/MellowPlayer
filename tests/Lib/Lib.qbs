import qbs

StaticLibrary {
    name: "MellowPlayer.TestLib"
    files: ["**"]

    Depends { name: 'cpp' }
    Depends { name: 'Qt.core' }
    Depends { name: 'MellowPlayer.Domain' }
    Depends { name: 'MellowPlayer.Infrastructure' }
    Depends { name: 'MellowPlayer.Presentation' }
    Depends { name: 'platform' }

    cpp.includePaths: base.concat(project.includePaths)
    cpp.cxxLanguageVersion: platform.cxxLanguageVersion
}
