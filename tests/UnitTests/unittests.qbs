import qbs

Project {
    name: "Unit Tests"
    references: [
        "Domain/domain.qbs",
        "Infrastructure/infrastructure.qbs",
        "Presentation/presentation.qbs"
    ]

    AutotestRunner {
        name: "unit-tests"
        limitToSubProject: true
    }
}
