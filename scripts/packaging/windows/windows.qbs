import qbs

InnoSetup {
    name: "MellowPlayer_Setup"
    files: ["setup.iss"]

    innosetup.defines: ["MyAppVersion=" + project.version]
    innosetup.verboseOutput: false

    Group {
        name: "InnoSetup Installer"
        fileTagsFilter: ["innosetup.exe"]
        qbs.installDir: "dist"
        qbs.install: true
    }
}
