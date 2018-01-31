import qbs

Project {
    name: "Unit Tests"
    references: [
        "Domain/domain.qbs",
        "Infrastructure/infrastructure.qbs"
    ]

    AutotestRunner {
        limitToSubProject: true
    }
}
