This directory contains some templates for adding 
a plugin to the application. The templates are configured
to integrate the application build procedure, not as external
plugins.

To create a new plugin (service or extension), just drop the
sub-folder in the plugins directory of the root source directory.
Rename the folder and every files with your own name. Rename the plugin
class and the metadata file (json). Add your subdir name to plugins.pro and
compile. This should compile out of the box.
