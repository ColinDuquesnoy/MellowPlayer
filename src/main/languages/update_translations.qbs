import qbs
import qbs.Process

Product {
    type: "ts"
    name: "update_translations"

    Group {
        name: "Translation source"
        files: "MellowPlayer_en.ts"
        fileTags: ["_en.ts"]
    }

    Depends { name: "platform" }

    Rule {
        inputs: ["_en.ts"]

        Artifact {
            filePath: "MellowPlayer_en.ts"
            fileTags: "ts"
        }

        prepare: {
            var cmd = new Command("lupdate-qt5", [
                    project.sourceDirectory + '/src/lib',
                    "-ts", project.sourceDirectory + "/src/main/languages/MellowPlayer_en.ts",
                    "-I", project.sourceDirectory + "/src/lib/presentation/include"
            ]);
            cmd.description = "updating translation";
            cmd.highlight = "codegen";
            cmd.onWindows = product.platform.windows
            return cmd;
        }
    }
}
