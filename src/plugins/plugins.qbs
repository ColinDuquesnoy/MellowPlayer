import qbs

Project {
    name: "Plugins"

    Product {
        name: "Web"

        Depends { name: "platform" }

        Group {
            name: "Sources"
            files: ["web/**/*"]

            qbs.install: true
            qbs.installSourceBase: "web"
            qbs.installDir: platform.windows ? "bin/plugins" : "share/mellowplayer/plugins"
        }
    }
}
