import qbs
import qbs.Probes

Project {
    name: "Documentation"

    Product {
        id: product

        property string sphinxBuildPath: sphinxBuild.filePath

        condition: sphinxBuild.found
        builtByDefault: false
        name: "Sphinx Documentation"
        type: "html"

        Probes.BinaryProbe {
            id: sphinxBuild

            names: ["sphinx-build"]
        }

        Group {
            name: "User Documentation"
            files: "users/*.rst"
            fileTags: ["rst"]
        }

        Group {
            name: "Developer Documentation"
            files: "developers/*.rst"
            fileTags: ["rst"]
        }

        Group {
            name: "Resources"
            files: "_static/*"
            fileTags: ["rst"]
        }

        Rule {
            multiplex: true
            inputs: ["rst"]

            Artifact {
                filePath: "index.html"
                fileTags: ["html"]
            }

            prepare: {
                var cmd = new Command(product.sphinxBuildPath, ["-b", "html", product.sourceDirectory, product.buildDirectory])
                cmd.description = "building sphinx documentation";
                cmd.highlight = "filegen";
                return cmd;
            }
        }
    }
}
