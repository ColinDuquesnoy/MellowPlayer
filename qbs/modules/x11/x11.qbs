import qbs 1.0
import qbs.Probes

Module {
    Depends { name: "cpp" }

    Probes.PkgConfigProbe {
        id: probe
        name: "x11"
    }
    cpp.cxxFlags: base.concat(probe.cflags)
    cpp.libraryPaths: base.concat(probe.libraryPaths)
    cpp.dynamicLibraries: base.concat(probe.libraries)

    property bool found: (qbs.targetOS.contains("linux") || qbs.targetOS.contains("bsd")) && probe.found
    onFoundChanged: console.warn("found x11: " + found)
}
