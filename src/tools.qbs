import qbs

Project {
    name: "Tools"

    references: [
        "main/languages/update_translations.qbs",
        "lib/presentation/imports/MellowPlayer/update_settings_translator.qbs",
        "lib/presentation/imports/MellowPlayer/update_qmldir.qbs",
    ]
}
