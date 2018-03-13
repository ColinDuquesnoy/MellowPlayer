import qbs

Project {
    name: "Sources"
    references: [
        "tools.qbs",
        "lib/lib.qbs",
        "plugins/plugins.qbs",
        "main/main.qbs",
    ]
}

