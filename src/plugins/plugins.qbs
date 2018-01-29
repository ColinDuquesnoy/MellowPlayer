import qbs

Product {
    name: "MellowPlayer.Plugins"

    Group {
        name: "Web Plugins"
        files: ["web/**/*"]

        qbs.install: true
        qbs.installSourceBase: "web"
        qbs.installDir: "share/mellowplayer/plugins"
    }
}
