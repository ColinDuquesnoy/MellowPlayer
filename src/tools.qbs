import qbs

Project {
    name: "Tools"

    references: [
        "main/languages/update_translations.qbs",
        "lib/presentation/imports/settings_translator.qbs",
    ]
}
