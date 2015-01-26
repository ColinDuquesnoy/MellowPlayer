#!/usr/bin/env python
"""
This is a small interactive helper script for the MellowPlayer developers and
contributors that automates some boring administration tasks such as:

  - adding a new plugin to the project
  - adding a new translation to the project
  - updating existing translation

Usage::

    python devtool.py

.. note:: this script will work with both python2 or python3, you don't need
          any additional package.

"""
import os
import shutil
import sys
import webbrowser


# --- Menu functions
def add_service_plugin():
    """ Adds a new music streaming service integration plugin to the project """
    name, classname = query_plugin_infos()
    gen_files(name, classname, sv_pro, sv_inc, sv_src, qrc=sv_qrc)
    register_plugin(name, classname)
    print('Plugin added... You may now rebuild the application in QtCreator.')


def add_extension_plugin():
    """ Adds a new extension plugin to the project """
    name, classname = query_plugin_infos()
    gen_files(name, classname, ext_pro, ext_inc, ext_src)
    register_plugin(name, classname)
    print('Plugin added... You may now rebuild the application in QtCreator.')


def add_translation():
    """ Adds a new translation to the project. """
    code = ''
    while not code:
        code = read_input('Please indicate the language code of the new '
                          'translation (e.g. en, fr, es and so on...): ')
    print('')
    translation_entry = 'app/translations/mellowplayer_%s.ts' % code
    print('Adding new translation: %s' % translation_entry)

    # Add entry to mellow player
    with open('MellowPlayer.pro', 'r') as fin:
        content = '\n'.join(fin.read().splitlines())
    content += '\nTRANSLATIONS +=%s\n' % translation_entry
    with open('MellowPlayer.pro', 'w') as fout:
        fout.write(content)

    # Add entry to app/mellowplayer.qrc
    qrc_entry = '        <file>translations/mellowplayer_%s.qm</file>\n' % code
    with open('app/mellowplayer.qrc', 'r') as fin:
        lines = fin.read().splitlines(True)
    lines.insert(2, qrc_entry)
    with open('app/mellowplayer.qrc', 'w') as fout:
        fout.write(''.join(lines))

    # update translations
    update_translations()

    # tell user to open qt linguist.
    print('')
    print('The new translation has been added.')
    print('You may now use Qt linguist to translate the application strings.')
    print("Once you're done, you will need "
          'to run qmake and rebuild the application (from Qt Creator)')


def update_translations():
    """ Updates existing translations (run lupdate and lrelease). """
    os.system('lupdate MellowPlayer.pro -no-obsolete')
    os.system('lrelease MellowPlayer.pro')


def make_win32_release():
    """
    Make a full release on Windows
    """
    def get_env_vars():
        try:
            # load from cache
            with open('envvars.usr', 'r') as f:
                exe, qmake = f.read().splitlines()
        except (OSError, IOError):
            # get build dir to get the full exe path
            exe = ''
            while not exe and not os.path.exists(exe):
                build_dir = read_input('Please indicate the release build directory: ').strip()
                exe = os.path.join(build_dir, 'app', 'release', 'MellowPlayer.exe')
            # get qmake path
            qmake = ''
            while not qmake and not os.path.exists(qmake):
                qmake = read_input('Please the full path to qmake: ')
            # cache it!
            with open('envvars.usr', 'w') as f:
                f.write('\n'.join([exe, qmake]))
        return exe, qmake

    def make_dist_dir():
        dist_dir = 'bin'
        if os.path.exists(dist_dir):
            shutil.rmtree(dist_dir)
        os.mkdir(dist_dir)
        return dist_dir

    exe, qmake = get_env_vars()
    dist = make_dist_dir()
    bin_dir = os.path.dirname(qmake)

    files = [
        exe,
        os.path.join(bin_dir, 'QtGui4.dll'),
        os.path.join(bin_dir, 'QtCore4.dll'),
        os.path.join(bin_dir, 'QtSvg4.dll'),
        os.path.join(bin_dir, 'QtNetwork4.dll'),
        os.path.join(bin_dir, 'QtWebKit4.dll'),
        'c:\\Windows\\System32\\msvcr100.dll',
        'c:\\Windows\\System32\\msvcp100.dll',
    ]

    for f in files:
        print('copying %s to %s' % (f, dist))
        shutil.copy(f, dist)

    plugins_dir = os.path.abspath(os.path.join(bin_dir, '..', 'plugins'))

    plugins = []
    for subdir in ['imageformats', 'iconengines']:
        root = os.path.join(plugins_dir, subdir)
        for f in os.listdir(root):
            if f.endswith('.dll') and not f.endswith('d4.dll'):
                plugins.append((os.path.join(root, f), subdir))

    for f, dest_dir in plugins:
        dst = os.path.join(dist, dest_dir)
        if not os.path.exists(dst):
            os.makedirs(dst)
        print('copying %s to %s' % (f, dst))
        shutil.copy(f, dst)

    # configure innosetup
    version = read_input('Version string: ')
    with open('setup.iss.in', 'r') as src, open('setup.iss', 'w') as dst:
        lines = src.readlines()
        data = []
        for l in lines:
            l = l.replace('@VERSION@', version)
            data.append(l)
        dst.writelines(data)

    os.environ['PATH'] += ';C:\Program Files (x86)\Inno Setup 5'
    os.system('iscc %s' % os.path.join(os.getcwd(), 'setup.iss'))



def make_osx_release():
    def get_build_dir():
        try:
            # load from cache
            with open('envvars.usr', 'r') as f:
                build_dir = f.read()
        except (OSError, IOError):
            # get build dir
            build_dir = ''
            while not build_dir and not os.path.exists(build_dir):
                build_dir = read_input('Build directory: ')
            # cache it!
            with open('envvars.usr', 'w') as f:
                f.write(build_dir)
        return build_dir

    os.chdir(os.path.join(get_build_dir(), 'app'))
    os.system('/Applications/macdeployqt.app/Contents/MacOS/macdeployqt MellowPlayer.app -dmg')


def make_docs():
    os.system('doxygen docs/Doxyfile')

    answer = read_input("Open documentation [Y/n]?").lower()
    if answer != 'n':
        path = 'file://' + os.path.realpath(os.path.join(
            os.getcwd(), 'docs', '_build', 'html', 'index.html'))
        print(path, webbrowser.open_new_tab(path))


# --- Menu definition
#: The menu dict associate the menu text entry and its associated function.
MENU = {
    '1. Add a new music streaming service plugin': add_service_plugin,
    '2. Add a new extension plugin': add_extension_plugin,
    '3. Add a new translation': add_translation,
    '4. Update translations': update_translations,
    '5. Make windows release': make_win32_release,
    '6. Make OSX release': make_osx_release,
    '7. Make documentation': make_docs,
    '8. Exit': lambda: sys.exit(0)
}


# --- Helper functions
def query_plugin_infos():
    """ Ask the user to fill in the plugin name.

    :return: name, classname
    """
    print('')
    name = ''
    while not name:
        name = read_input('Please, enter the new plugin name: ').lower()
    classname = '%sPlugin' % name.capitalize()
    return name, classname


def gen_files(name, classname, pro, header, src, qrc=None):
    """
    Generates the plugin files.

    :param name: Name of the plugin
    :param classname: Name of the class of the plugin
    :param pro: plugin pro template (str)
    :param header: plugin pro header template (str)
    :param src: plugin pro source template (str)
    :param qrc: plugin qrc template (str)
    """
    directory = os.path.join('plugins', name)
    try:
        os.mkdir(directory)
    except OSError:
        if not os.path.exists(directory):
            print('failed to create the plugin directory')
            sys.exit(1)
    # pro file
    with open(os.path.join(directory, '%s.pro' % name), 'w') as f:
        f.write(pro % {'name': name})
    # header
    with open(os.path.join(directory, '%s.h' % name), 'w') as f:
        f.write(header % {'name': name, 'classname': classname})
    # src
    with open(os.path.join(directory, '%s.cpp' % name), 'w') as f:
        f.write(src % {
            'name': name,
            'name_cap': name.capitalize(),
            'classname': classname
        })
    # plugins metadata.
    with open(os.path.join(directory, '%s.json' % name), 'w') as f:
        f.write('{}')
    # optional resources file (create only for streaming services).
    if qrc is not None:
        with open(os.path.join(directory, '%s.qrc' % name), 'w') as f:
            f.write(qrc % {'name': name})


def register_plugin(name, classname):
    """
    Registers the plugin (add it to the pro files and import it in main.cpp)

    :param name: Name of the plugin
    :param classname: Class name of the plugin
    """
    lib_name = 'mpp_%s' % name
    lib_fullname_unix = 'libmpp_%s.a' % name
    lib_fullname_win32 = 'mpp_%s.lib' % name


    # plugins.pro
    with open('plugins/plugins.pro', 'r') as fin:
        content = '\n'.join(fin.read().splitlines())
    content += '\nSUBDIRS += %s\n' % name
    with open('plugins/plugins.pro', 'w') as fout:
        fout.write(content)

    # app.pro
    with open('app/app.pro', 'r') as fin:
        lines = fin.read().splitlines(True)
    insert_index = -1
    # LIBS
    for i, line in enumerate(lines):
        if line.strip() == 'LIBS += -L.':
            insert_index = i + 1
            break
    lines.insert(insert_index, 'LIBS += -l%s\n' % lib_name)
    # PRE_TARGETDEPS
    # win32
    insert_index = -1
    for i, line in enumerate(lines):
        if line.strip() == 'win32 { # force relink app when a static lib changed.':
            insert_index = i + 1
            break
    lines.insert(insert_index, '    PRE_TARGETDEPS += %s\n' % lib_fullname_win32)
    # unix
    insert_index = -1
    for i, line in enumerate(lines):
        if line.strip() == 'else { # force relink app when a static lib changed.':
            insert_index = i + 1
            break
    lines.insert(insert_index, '    PRE_TARGETDEPS += %s\n' % lib_fullname_unix)

    # write results
    with open('app/app.pro', 'w') as fout:
        fout.write(''.join(lines))

    # main.cpp

    with open('app/main.cpp', 'r') as fin:
        lines = fin.read().splitlines(True)
    insert_index = -1
    for i, line in enumerate(lines):
        if 'Q_IMPORT_PLUGIN' in line:
            insert_index = i
            break
    lines.insert(insert_index, 'Q_IMPORT_PLUGIN(%s)\n' % classname)
    with open('app/main.cpp', 'w') as fout:
        fout.write(''.join(lines))


def read_input(prompt=''):
    """
    Python intepreter independant input function. Reads a string from the
    standard input.

    :param prompt: Optional prompt text.
    :return: The user input (str)
    """
    if sys.version_info[0] == 2:
        return raw_input(prompt)
    else:
        return input(prompt)


def display_menu():
    """ Display the main menu and handle user choice.

    :return: Choice value or None if the choice was invalid.
    """
    print('')
    print('MENU')
    print('----')
    print('')
    for key in sorted(MENU.keys()):
        print(key)
    print('')
    txt = read_input('Choose an option (from 1 to %d): ' % len(MENU))
    try:
        choice = int(txt)
    except ValueError:
        return None
    else:
        if choice not in range(1, len(MENU) + 1):
            return None
        return choice - 1


# --- Extension plugin templates
ext_pro = '''#----------------------------------------------------------
#
# This file is part of MellowPlayer.
#
# MellowPlayer is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MellowPlayer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
#
#----------------------------------------------------------

# This extension is built on GNU/Linux only!
TEMPLATE      = lib
TARGET        = mpp_%(name)s
CONFIG       += plugin static
QT           += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
HEADERS       = %(name)s.h
SOURCES       = %(name)s.cpp
INCLUDEPATH  += ../../lib/include
LIBS         += -L../../lib -lmellowplayer
DESTDIR       = ../../app

'''

ext_inc = '''//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include <QObject>
#include <mellowplayer.h>


class %(classname)s :
        public QObject,
        public IExtension
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID IExtension_iid
                      FILE "%(name)s.json")
#endif
    Q_INTERFACES(IExtension)

public:
    explicit %(classname)s(QObject* parent=NULL);

    void setup();
    const PluginMetaData& metaData() const;
};
'''

ext_src = '''//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include <QWidget>
#include <mellowplayer.h>
#include "%(name)s.h"

//---------------------------------------------------------
%(classname)s::%(classname)s(QObject *parent):
    QObject(parent)
{
}

//---------------------------------------------------------
void %(classname)s::setup()
{
    // setup your extension here
}

//---------------------------------------------------------
const PluginMetaData &%(classname)s::metaData() const
{
    static PluginMetaData meta;
    meta.name = "%(name_cap)s";
    meta.author = "YOUR NAME";
    meta.author_website = "YOUR GITHUB PROFILE";
    meta.version = "1.0";
    meta.description =tr("Plugin description");
    return meta;
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2( %(classname)s, %(classname)s )
#endif

'''

# --- Music Streaming Service integration plugin templates
sv_pro = '''#----------------------------------------------------------
#
# This file is part of MellowPlayer.
#
# MellowPlayer is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MellowPlayer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
#
#----------------------------------------------------------

TEMPLATE      = lib
QT           += core gui widgets webkit network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
TARGET        = mpp_%(name)s
CONFIG       += plugin static
HEADERS       = %(name)s.h
SOURCES       = %(name)s.cpp
RESOURCES    += %(name)s.qrc
DESTDIR       = ../../app
INCLUDEPATH  += ../../lib/include

'''

sv_inc = '''//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include <QtCore>
#include <mellowplayer.h>

class %(classname)s:
        public QObject,
        public IStreamingService
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID IStreamingService_iid
                      FILE "%(name)s.json")
#endif
    Q_INTERFACES(IStreamingService)

public:
    %(classname)s();
    virtual const PluginMetaData& metaData() const;

    //! Returns the %(classname)s URL
    virtual QUrl url() const;
    //! Plays the current song
    void play();
    //! Pauses the current song
    void pause();
    //! Stops the current song
    void stop();
    //! Skips to the next song
    void next();
    //! Skips to the previous song
    void previous();
    //! Seeks to the indicated position
    void seekToPosition(int position);
    //! Gets the current song info
    SongInfo currentSongInfo();
    float volume();
    void setVolume(float volume);
};

'''

sv_src = '''//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include "%(name)s.h"

//---------------------------------------------------------
%(classname)s::%(classname)s()
{
    Q_INIT_RESOURCE(%(name)s);
}

//---------------------------------------------------------
const PluginMetaData &%(classname)s::metaData() const
{
    static PluginMetaData meta;
    meta.name = "%(name_cap)s";
    meta.author = "YOUR NAME";
    meta.author_website = "YOUR GITHUB PROFILE URL";
    meta.version = "1.0";
    meta.icon = QIcon("YOUR ICON PATH");
    meta.description =tr("Music streaming service description");
    return meta;
}

//---------------------------------------------------------
QUrl %(classname)s::url() const
{
    return QUrl("YOUR SERVICE URL");
}

//---------------------------------------------------------
void %(classname)s::play()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::pause()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::stop()
{
    this->pause();
}

//---------------------------------------------------------
void %(classname)s::next()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::previous()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::seekToPosition(int position)
{
    this->runJavaScript("");
}

//---------------------------------------------------------
SongInfo %(classname)s::currentSongInfo()
{
    SongInfo retVal;
    return retVal;
}

//---------------------------------------------------------
float %(classname)s::volume()
{
    return 1.f;
}

//---------------------------------------------------------
void %(classname)s::setVolume(float volume)
{
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( %(classname)s, %(classname)s )
#endif

'''

sv_qrc = '''<RCC>
  <qresource prefix="/%(name)s">
  </qresource>
</RCC>
'''


# --- Application entry point
if __name__ == '__main__':
    choice = None
    while choice is None:
        choice = display_menu()
        print('')
        if choice is None:
            print('Invalid choice, please choose a number between 1 and %d' %
                  len(MENU))
        else:
            MENU[sorted(MENU.keys())[choice]]()
    print('')
