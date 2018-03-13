import qbs
import qbs.Probes

Module {
    Depends { name: "cpp" }

    Probes.PkgConfigProbe {
        id: probe
        name: "x11"
    }
    cpp.cxxFlags: found ? base.concat(probe.cflags) : base
    cpp.libraryPaths: found ? base.concat(probe.libraryPaths) : base
    cpp.dynamicLibraries: found ? base.concat(probe.libraries) : base

    property bool found: {
        if (probe.found)
            console.info("found x11")
        else
            console.info("could not find x11")
        return probe.found;
    }
}
