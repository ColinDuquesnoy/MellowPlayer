import qbs
import qbs.TextFile
import Settings

Product {
    type: "js"
    name: "SettingsTranslator.js"

    Group {
        name: "SettingsTranslator.js.in"
        files: ["MellowPlayer/SettingsTranslator.js.in"]
        fileTags: ["js.in"]
    }

    Rule {
        inputs: ["js.in"]

        Artifact {
            filePath: "SettingsTranslator.js"
            fileTags: "js"
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generating SettingsTranslator.js";
            cmd.highlight = "codegen";
            cmd.onWindows = product.platform.windows
            cmd.sourceCode = function() {
                var inFile = new TextFile(input.filePath);
                var schema = Settings.getSchema();
                var keys = Settings.getKeys(schema)
                var values = Settings.getEnumValues(keys);
                var names = Settings.getEnumNames(keys);
                var content = inFile.readAll();
                content = content.replace("%(names)s", Settings.getNames(schema));
                content = content.replace("%(tooltips)s", Settings.getTooltips(schema));
                content = content.replace("%(categories)s", Settings.getCategories(schema));
                file = new TextFile(input.filePath.replace(".in", ""), TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();

                // to force update of imports.qrc
                file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();
            }
            return cmd;
        }
    }

    Depends { name: "platform" }
}
