import qbs

Project {
    name: "Unit Tests"
    references: [
        "Domain/domain.qbs",
        "Infrastructure/infrastructure.qbs"
    ]

    AutotestRunner {
        builtByDefault: project.buildTests
        limitToSubProject: true
    }
}
