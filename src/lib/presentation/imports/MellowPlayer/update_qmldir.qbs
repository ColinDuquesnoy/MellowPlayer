import qbs
import qbs.File
import qbs.TextFile
import qbs.Process
import qbs.FileInfo
import Settings

Product {
    type: "genqmldir"
    name: "update_qmldir"
    builtByDefault: false

    Group {
        name: "qmldir"
        files: ["qmldir"]
        fileTags: ["qmldir"]
    }

    Rule {
        inputs: ["qmldir"]
        alwaysRun: true

        Artifact {
            filePath: "qmldir"
            fileTags: "genqmldir"
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generating qmldir";
            cmd.highlight = "codegen";
            cmd.onWindows = product.platform.windows
            cmd.sourceCode = function() {
                // todo write it in python!!!
                var sourceDir = product.sourceDirectory
                var p = new Process();
                p.start("find", [sourceDir])
                p.waitForFinished();
                var lines = String(p.readStdOut()).split("\n").sort();
                var importLines = []
                for(var i = 0; i < lines.length; i++) {
                    var line = lines[i];
                    if ((line.endsWith('.qml') || line.endsWith('.js') )&& !line.endsWith("MaterialIcons.qml")) {
                        var path = FileInfo.relativePath(sourceDir, line)
                        var baseName = FileInfo.baseName(path);
                        importLines.push(baseName + " 3.0 " + path);
                    }
                }

                var content = "module MellowPlayer\n\nsingleton MaterialIcons 3.0 MaterialIcons.qml\n\n" + importLines.join("\n");

                var file = new TextFile(input.filePath, TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();
            }
            return cmd;
        }
    }

    Depends { name: "platform" }
}
