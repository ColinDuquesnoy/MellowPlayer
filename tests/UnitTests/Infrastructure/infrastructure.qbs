import qbs

Product {
    files: ["**", project.main]
    name: "MellowPlayer.Infrastructure.UnitTests"
    type: ["application", "autotest"]

    cpp.includePaths: base.concat(project.includePaths)
    cpp.cxxLanguageVersion: platform.cxxLanguageVersion
    cpp.defines: ['PLUGINS_DIR="' + project.sourceDirectory + 'src/plugins/web"']

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
