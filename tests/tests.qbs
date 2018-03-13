import qbs

Project {
    property string main: sourceDirectory + "/tests/main.cpp"
    property var includePaths: [
        sourceDirectory + "/3rdparty",
        sourceDirectory + "/tests",
        sourceDirectory + "/tests/Lib"
    ]

    condition: project.buildTests
    name: "Tests"
    references: [
        "Lib/TestLib.qbs",
        "UnitTests/unittests.qbs",
        "IntegrationTests/integrationtests.qbs"
    ]

    AutotestRunner {
        name: "tests"
        limitToSubProject: true

        Depends { name: "Qt.core" }

        environment: {
            var env = base;
            env.push("QBS_INSTALL_ROOT=" + qbs.installRoot);
            if (qbs.hostOS.contains("windows") && qbs.targetOS.contains("windows")) {
                var path = "";
                for (var i = 0; i < env.length; ++i) {
                    if (env[i].startsWith("PATH=")) {
                        path = env[i].substring(5);
                        break;
                    }
                }
                path = Qt.core.binPath + ";" + path;
                var arrayElem = "PATH=" + path;
                if (i < env.length)
                    env[i] = arrayElem;
                else
                    env.push(arrayElem);
            }
            if (qbs.hostOS.contains("darwin") && qbs.targetOS.contains("darwin")) {
                env.push("DYLD_FRAMEWORK_PATH=" + Qt.core.libPath);
                env.push("DYLD_LIBRARY_PATH=" + Qt.core.libPath);
            }
            return env;
        }
    }
}
