import qbs

Project {
    name: "Integration Tests"
    references: [
        "Infrastructure/infrastructure.qbs",
        "Presentation/presentation.qbs",
        "Mpris/mpristests.qbs"
    ]

    AutotestRunner {
        name: "integration-tests"
        limitToSubProject: true
    }
}
