import qbs
import qbs.Probes

Module {
    id: module

    Depends { name: "cpp" }

    Probes.PkgConfigProbe {
        id: probe
        name: "qxtglobalshortcut"
    }
    cpp.cxxFlags: found ? base.concat(probe.cflags) : base
    cpp.libraryPaths: found ? base.concat(probe.libraryPaths) : base
    cpp.dynamicLibraries: found ? base.concat(probe.libraries) : base

    property bool found: probe.found
}
