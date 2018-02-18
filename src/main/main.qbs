import qbs
import qbs.Probes
import qbs.Xml

Project {
    name: "Application"

    Product {
        id: product

        type: "application"
        name: "MellowPlayer"
        consoleApplication: false

        bundle.isBundle: platform.isBundle
        cpp.cxxLanguageVersion: platform.cxxLanguageVersion
        cpp.cxxFlags: platform.cxxFlags
        cpp.linkerFlags: platform.linkerFlags
        cpp.warningLevel: undefined
        cpp.treatWarningsAsErrors: false
        cpp.dynamicLibraries: platform.isGcc && project.enableCoverage ? base.concat(["gcov"]) : base

        Qt.core.resourcePrefix: "/MellowPlayer/Translations"
        Qt.core.resourceSourceBase: undefined
        Qt.core.resourceFileBaseName: "languages"

        Depends { name: "cpp" }
        Depends { name: "bundle" }
        Depends { name: "platform" }
        Depends { name: "Qt.webengine" }
        Depends { name: "Qt.quickcontrols2" }
        Depends { name: "MellowPlayer.Domain" }
        Depends { name: "MellowPlayer.Infrastructure" }
        Depends { name: "MellowPlayer.Presentation" }

        Group {
            name: "Application"
            fileTagsFilter: "application"
            qbs.install: true
            qbs.installDir: "bin"
        }

        Group {
            name: "Sources"
            files: [ "*.cpp" ]
        }
        Group {
            name: "Headers"
            files: [ "DI.hpp", "Program.hpp" ]
        }

        Group {
            name: "Precompiled headers"
            files: ["stdafx.hpp"]
            fileTags: ["cpp_pch_src"]
        }

        Group {
            name: "Imports"
            files: ["qml.qrc", "main.qml"]
        }
        Group {
            name: "Resources"
            files: ["mellowplayer.ico", "MellowPlayer.rc"]
        }

        Group {
            name: "Language files"
            files: ["**/*.ts"]
        }

        Rule {
            multiplex: true
            inputs: ["qm"]

            Artifact {
                filePath: product.Qt.core.resourceFileBaseName + ".qrc"
                fileTags: ["qrc"]
            }

            prepare: {
                // take from qt.core.resource_data rule
                var cmd = new JavaScriptCommand();
                cmd.description = "generating " + output.fileName;
                cmd.sourceCode = function() {
                    var doc = new Xml.DomDocument("RCC");

                    var rccNode = doc.createElement("RCC");
                    rccNode.setAttribute("version", "1.0");
                    doc.appendChild(rccNode);

                    var inputsByPrefix = {}
                    for (var i = 0; i < inputs["qm"].length; ++i) {
                        var inp = inputs["qm"][i];
                        var prefix = inp.Qt.core.resourcePrefix;
                        var inputsList = inputsByPrefix[prefix] || [];
                        inputsList.push(inp);
                        inputsByPrefix[prefix] = inputsList;
                    }

                    for (var prefix in inputsByPrefix) {
                        var qresourceNode = doc.createElement("qresource");
                        qresourceNode.setAttribute("prefix", prefix);
                        rccNode.appendChild(qresourceNode);

                        for (var i = 0; i < inputsByPrefix[prefix].length; ++i) {
                            var inp = inputsByPrefix[prefix][i];
                            var fullResPath = inp.filePath;
                            var baseDir = inp.Qt.core.resourceSourceBase;
                            var resAlias = baseDir
                                ? FileInfo.relativePath(baseDir, fullResPath) : inp.fileName;

                            var fileNode = doc.createElement("file");
                            fileNode.setAttribute("alias", resAlias);
                            qresourceNode.appendChild(fileNode);

                            var fileTextNode = doc.createTextNode(fullResPath);
                            fileNode.appendChild(fileTextNode);
                        }
                    }

                    doc.save(output.filePath, 4);
                };
                return [cmd];
            }
        }

        Group {
            name: "Share"

            files: [
                "share/applications/mellowplayer.desktop",
                "share/icons/hicolor/scalable/apps/mellowplayer.svg",
                "share/metainfo/mellowplayer.appdata.xml"
            ]

            qbs.install: true
            qbs.installSourceBase: "share"
            qbs.installDir: "share"
        }
    }
}
