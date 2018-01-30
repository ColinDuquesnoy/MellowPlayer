import qbs

Project {
    name: "Libraries"
    references: [
        "domain/domain.qbs",
        "infrastructure/infrastructure.qbs",
        "presentation/imports/settings_translator.qbs",
        "presentation/presentation.qbs",
    ]
}

 
