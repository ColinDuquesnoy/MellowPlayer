import qbs

Project {
    name: "Plugins"

    Product {
        name: "Web"

        Group {
            name: "Sources"
            files: ["web/**/*"]

            qbs.install: true
            qbs.installSourceBase: "web"
            qbs.installDir: "share/mellowplayer/plugins"
        }
    }
}
