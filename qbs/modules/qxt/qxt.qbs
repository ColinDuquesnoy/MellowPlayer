import qbs 1.0
import qbs.Probes

Module {
    Depends { name: "cpp" }

    Probes.PkgConfigProbe {
        id: probe
        name: "qxtglobalshortcut"
    }
    cpp.cxxFlags: found ? base.concat(probe.cflags) : base
    cpp.libraryPaths: found ? base.concat(probe.libraryPaths) : base
    cpp.dynamicLibraries: found ? base.concat(probe.libraries) : base

    property bool found: (qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")) && probe.found
    onFoundChanged: console.warn("found qxtglobalshortcut: " + found)
}
