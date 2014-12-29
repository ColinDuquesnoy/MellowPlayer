TEMPLATE        = subdirs
SUBDIRS         = app \
                  lib \
                  plugins
app.depends     = lib
plugins.depends = lib
