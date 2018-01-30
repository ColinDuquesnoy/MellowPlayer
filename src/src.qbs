import qbs

Project {
    name: "Sources"
    references: [
        "lib/lib.qbs",
        "plugins/plugins.qbs",
        "main/main.qbs",
    ]
}

